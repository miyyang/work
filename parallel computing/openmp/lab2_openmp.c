#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define NUM_THREAD 1

int** create_world(int length, int if_init)
{
    int i, j;
    int** world = (int**)malloc((length + 2) * sizeof(int*));
    if (world == NULL)
    {
        printf("\nmalloc error!\n");
        exit(0);
    }
    for (i = 0; i < length + 2; i++)
    {
        world[i] = (int*)malloc((length + 2) * sizeof(int));
        if (world[i] == NULL)
        {   
            printf("\nmalloc error!\n");
            exit(0);
        }
    }
    for (int k = 0; k < length + 2; k++)
    {
        world[0][k] = world[length + 1][k]
            = world[k][0] = world[k][length + 1] = 0;
    }
    for (int k = 0; k < length + 2; k++)
    {
        world[k] = world[k] + 1;
    }
    world = &(world[1]);
    if (if_init == 1)
    {
        srand(time(0));
        for (i = 0; i < length; i++)
            for (j = 0; j < length; j++)
                world[i][j] = rand() % 2;
    }
    else if (if_init == 2)
    {
        char temp;
        freopen("debug.txt", "r", stdin);
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < length; j++)
            {
                temp = getchar();
                world[i][j] = (temp == '*');
            }
            getchar();
        }
    }
    printf("ok");
    return world;
}

int get_alive_neighbors(int** world, int length, int row, int column)
{
    int rowLeft      = row - 1;
    int rowRight     = row + 1;
    int columnUp     = column - 1;
    int columnBottom = column + 1;
  
    return world[rowLeft][columnUp] + 
        world[rowLeft][column] + 
        world[rowLeft][columnBottom] + 
        world[row][columnUp] + 
        world[row][columnBottom] + 
        world[rowRight][columnUp] + 
        world[rowRight][column] + 
        world[rowRight][columnBottom]; 
}

void display_world(int **world, int length)
{
    int i, j;
    putchar('\n');
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            if (world[i][j] == 0)
                putchar('-');
            else 
                putchar('*');
        }
        putchar('\n');
    }
    putchar('\n');
}

int main(int argc, char* arg[])
{
    int i;
    int j;
    double wtime;
    int iter = atoi(arg[1]);
    int length = atoi(arg[2]);
    int** world = create_world(length, 1);
    int** next_world = create_world(length, 0);
    int** temp_world;
    
    wtime = omp_get_wtime();
    // debug
    // display_world(world, length);
    for (int k = 0; k < iter; k++)
    {
        #pragma omp parallel for private(i, j) num_threads(NUM_THREAD)
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < length; j++)
            {
                int neighbors = get_alive_neighbors(world, length, i, j);
                // debug
                // printf("%d %d %d\n", i + 1, j + 1, neighbors);
                if(world[i][j] == 0) 
                    next_world[i][j] = neighbors == 3 ? 1 : 0;
                else if(world[i][j] == 1) 
                    next_world[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            }
        }
        // debug
        // display_world(next_world, length);
        temp_world = next_world;
        next_world = world;
        world = temp_world;
    }
    wtime = omp_get_wtime() - wtime;

    printf("time: %lf s\n", wtime);

    return 0;
}