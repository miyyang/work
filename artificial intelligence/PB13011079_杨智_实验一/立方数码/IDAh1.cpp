#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#define OFFSET 2
#define MAXNODE 999999999

using namespace std;

typedef struct Node {
    struct Node *parent;
    char move;
    
    int f;
    int h;
    
    char state[28];
} State;

char goal_place[24][3];

const int cube_size = 3 * 3 * 3 * sizeof(char);
const int StateSize = sizeof(State);

State start;
State goal;

char procedure[1000];

bool succ_cmp(State *a, State* b)
{
    return a->h < b->h;
}

// free and malloc
unsigned long ma = 0;
State** nodes;//[MAXNODE];

State* my_malloc(int size)
{
    if (ma > 0)
        return nodes[--ma];
    else
        return (State*)malloc(StateSize);
}

void free_one(State* s)
{
    if (ma < MAXNODE)
        nodes[ma++] = s;
    else
        free(s);
}

// the position of digit '0'
char space_x;
char space_y;
char space_z;

typedef queue<State*> OpenQueue;

typedef std::vector<State*> Successors;

int find_space(char a[])
{
    int i;
    int j;
    int k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                if (a[((i * 3 + j) * 3 + k)] == OFFSET)
                {
                    space_x = i; space_y = j; space_z = k;
                    return 0;
                }
    return 0;
}

void swap(char* x, char* y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void try_all_move(State* s, Successors* succ)
{
    char* current = s->state;
    find_space(current);
    
    State* temp;
    // Up ok
    if ((space_z <= 1) && (current[(space_x * 3 + space_y) * 3 + space_z + 1] > OFFSET) &&  (s->move != 'D'))
    {
        temp = my_malloc(StateSize);
        temp->move = 'U';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        char* val = temp->state + (space_x * 3 + space_y) * 3 + space_z;
        swap(val, val + 1);
        (*succ).push_back(temp);
    }
    // Down
    if ((space_z > 0) && (current[(space_x * 3 + space_y) * 3 + space_z - 1] > OFFSET) &&  (s->move != 'U'))
    {
        temp = my_malloc(StateSize);
        temp->move = 'D';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        char* val = temp->state + (space_x * 3 + space_y) * 3 + space_z;
        swap(val, val - 1);
        (*succ).push_back(temp);
    }
    // Left ok
    if ((space_y > 0) && (current[(space_x * 3 + space_y - 1) * 3 + space_z] > OFFSET) &&   (s->move != 'R'))
    {
        temp = my_malloc(StateSize);
        temp->move = 'L';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        char* val = temp->state + (space_x * 3 + space_y) * 3 + space_z;
        swap(val, val - 3);
        (*succ).push_back(temp);
    }
    // Right ok
    if ((space_y <= 1) && (current[(space_x * 3 + space_y + 1) * 3 + space_z] > OFFSET) &&  (s->move != 'L'))
    {
        temp = my_malloc(StateSize);
        temp->move = 'R';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        char* val = temp->state + (space_x * 3 + space_y) * 3 + space_z;
        swap(val, val + 3);
        (*succ).push_back(temp);
    }
    // Front
    if ((space_x <= 1) && (current[(space_x * 3 + 3 + space_y) * 3 + space_z] > OFFSET) &&  (s->move != 'B'))    {
        temp = my_malloc(StateSize);
        temp->move = 'F';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        char* val = temp->state + (space_x * 3 + space_y) * 3 + space_z;
        swap(val, val + 9);
        (*succ).push_back(temp);
    }
    // Back
    if ((space_x > 0) && (current[(space_x * 3 - 3 + space_y) * 3 + space_z] > OFFSET) &&  (s->move != 'F'))
    {
        temp = my_malloc(StateSize);
        temp->move = 'B';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        char* val = temp->state + (space_x * 3 + space_y) * 3 + space_z;
        swap(val, val - 9);
        (*succ).push_back(temp);
    }
}

int Compute_H(State* s)
{
    char* a = s->state;
    char* b = goal.state;
    int result = 0;
    for (int i = 0; i < 27; i++)
        if (b[i] > OFFSET)
            result += (b[i] != a[i]);
    return result;
}

int equal_state(State* a, State* b)
{
    return 0 == strcmp(a->state, b->state);
}

int idastar_search(State* s, int g, int bound)
{
    procedure[g] = s->move;
    s->h = Compute_H(s);
    s->f = g + s->h;
    if (s->f > bound)
    {
        free_one(s);
        return s->f;
    }
    if (s->h == 0)
    {
        procedure[g+1] = '\0';
        //printf("%s\n%d\n", procedure + 1, g);
        return -1;
    }
    int min = 9999;
    Successors succ;
    try_all_move(s, &succ);
    //sort(succ.begin(), succ.end(), succ_cmp);
    for (int i = 0; i < succ.size(); i++)
    {
        State* temp = succ[i];
        int t = idastar_search(temp, g + 1, bound);
        if (t == -1)
            return -1;
        if (t < min)
            min  = t;
    }
    if (g != 0)
        free_one(s);
    return min;
}

int idastar()
{
    find_space(start.state);
    int bound = Compute_H(&start);
    start.f = start.h = bound;
    
    while (1)
    {
        int t = idastar_search(&start, 0, bound);
        if (t == -1)
            return 1;
        bound = t;
    }
    return 0;
}

int main()
{
    int i, j, k;
    int cc;
    nodes = (State**)malloc(MAXNODE * StateSize);
    start.state[27] = '\0';
    goal.state[27] = '\0';
    start.move = 'S';
    start.parent = &goal;
    goal.move = 'G';
    goal.f = 0;
    // input
    freopen("./source.txt", "r", stdin);
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
            {
                scanf("%d", &cc);
                start.state[((2 - i) * 3 + k) * 3 + 2 - j] = cc + OFFSET;
            }
    freopen("./target.txt", "r", stdin);
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
            {
                scanf("%d", &cc);
                goal.state[((2 - i) * 3 + k) * 3 + 2 - j]  = cc + OFFSET;
                if (cc > 0)
                {
                    goal_place[cc][0] = 2 - i;
                    goal_place[cc][1] = k;
                    goal_place[cc][2] = 2 - j;
                }
            }
    
    // run A* algorithm with h1 and track
    clock_t start_time,finish_time;
    double total_time;
    start_time = clock();
    if(idastar())
    {
        printf("success\n");
    }
    finish_time = clock();
    total_time = (double)(finish_time - start_time) / CLOCKS_PER_SEC * 1000;
    
    // 输出
    freopen("./output_IDAh1.txt", "w", stdout);
    printf("%lf\n", total_time);
    printf("%s\n", procedure + 1);
    
    return 0;
}

