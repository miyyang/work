#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <cstring>

#include <unordered_set>
#include <queue>
#include <vector>

#define OFFSET 2

using namespace std;

typedef struct Node {
    struct Node *parent;
    char move;
    
    int f;
    int g;
    
    char state[28];
} State;

const int cube_size = 3 * 3 * 3 * sizeof(char);
const int StateSize = sizeof(State);

State start;
State goal;

char procedure[100];

// the position of digit '0'
char space_x;
char space_y;
char space_z;

// priority_queue compare
struct pq_cmp{
    bool operator() (State* a, State* b)
    {
        return a->f > b->f;
    }
};

// hash function
class SetHash
{
public:
    size_t operator()(State* s) const
    {
        char* str = s->state;
        unsigned int hash = 1315423911;
        while (*str){
            hash ^= ((hash << 5) + (*str++) + (hash >> 2));
        }
        return (hash & 0x7FFFFFFF);
    }
};

// unordered_set compare
class SetCompare
{
public:
    bool operator()(State* a, State* b) const
    {
        return 0 == strcmp(a->state, b->state);
    }
};

// basic data structure
typedef priority_queue<State*, vector<State*>, pq_cmp> OpenQueue;
typedef unordered_set<State*, SetHash, SetCompare>  CheckSet;

OpenQueue openqueue;
CheckSet checkset;

std::vector<State*> Successors;

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

void try_all_move(State* s)
{
    char* current = s->state;
    find_space(current);
    
    // Up
    if ((space_z <= 1) && (current[(space_x * 3 + space_y) * 3 + space_z + 1] > OFFSET))
    {
        State* temp;
        temp = (State*)malloc(StateSize);
        temp->move = 'U';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        swap(temp->state + (space_x * 3 + space_y) * 3 + space_z, temp->state + (space_x * 3 + space_y) * 3 + space_z + 1);
        Successors.push_back(temp);
    }
    // Down
    if ((space_z > 0) && (current[(space_x * 3 + space_y) * 3 + space_z - 1] > OFFSET))
    {
        State* temp;
        temp = (State*)malloc(sizeof(State));
        temp->move = 'D';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        swap(temp->state + (space_x * 3 + space_y) * 3 + space_z, temp->state + (space_x * 3 + space_y) * 3 + space_z - 1);
        Successors.push_back(temp);
    }
    // Left
    if ((space_y > 0) && (current[(space_x * 3 + space_y - 1) * 3 + space_z] > OFFSET))
    {
        State* temp;
        temp = (State*)malloc(sizeof(State));
        temp->move = 'L';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        swap(temp->state + (space_x * 3 + space_y) * 3 + space_z, temp->state + (space_x * 3 + space_y - 1) * 3 + space_z);
        Successors.push_back(temp);
    }
    // Right
    if ((space_y <= 1) && (current[(space_x * 3 + space_y + 1) * 3 + space_z] > OFFSET))
    {
        State* temp;
        temp = (State*)malloc(sizeof(State));
        temp->move = 'R';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        swap(temp->state + (space_x * 3 + space_y) * 3 + space_z, temp->state + (space_x * 3 + space_y + 1) * 3 + space_z);
        Successors.push_back(temp);
    }
    // Front
    if ((space_x <= 1) && (current[(space_x * 3 + 3 + space_y) * 3 + space_z] > OFFSET))
    {
        State* temp;
        temp = (State*)malloc(sizeof(State));
        temp->move = 'F';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        swap(temp->state + (space_x * 3 + space_y) * 3 + space_z, temp->state + (space_x * 3 + 3 + space_y) * 3 + space_z);
        Successors.push_back(temp);
    }
    // Back
    if ((space_x > 0) && (current[(space_x * 3 - 3 + space_y) * 3 + space_z] > OFFSET))
    {
        State* temp;
        temp = (State*)malloc(sizeof(State));
        temp->move = 'B';
        temp->state[27] = '\0';
        temp->parent = s;
        memcpy(temp->state, current, cube_size);
        swap(temp->state + (space_x * 3 + space_y) * 3 + space_z, temp->state + (space_x * 3 - 3 + space_y) * 3 + space_z);
        Successors.push_back(temp);
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

int Astar()
{
    char *gstate = goal.state;
    find_space(start.state);
    start.g = 0;
    start.f = Compute_H(&start);
    openqueue.push(&start);
    checkset.insert(&start);
    
    while (!openqueue.empty())
    {
        State* now_state = openqueue.top();
        openqueue.pop();
        
        if (0 == strcmp(gstate, now_state->state))
        {
            // find a solution
            int i = now_state->g;
            procedure[i] = '\0';
            while(i > 0)
            {
                procedure[--i] = now_state->move;
                now_state = now_state->parent;
            }
            return 1;
        }
        
        Successors.clear();
        try_all_move(now_state);
        for (std::vector<State*>::iterator new_state = Successors.begin(); new_state != Successors.end() ; new_state++)
        {
            // check if it's already considered
            if (checkset.insert(*new_state).second)
            {
                int new_g = (*new_state)->parent->g + 1;
                int new_f = new_g + Compute_H(*new_state);
                (*new_state)->g = new_g;
                (*new_state)->f = new_f;
                openqueue.push(*new_state);
            }
        }
    }
    // no solution
    return 0;
}

int main()
{
    int i, j, k;
    int cc;
    start.state[27] = '\0';
    goal.state[27] = '\0';
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
            }
    
    // run A* algorithm with h1 and track
    clock_t start_time,finish_time;
    double total_time;
    start_time = clock();
    if(Astar())
    {
        printf("success\n");
    }
    finish_time = clock();
    total_time = (double)(finish_time - start_time) / CLOCKS_PER_SEC * 1000;
    
    // 输出
    freopen("./output_Ah1.txt", "w", stdout);
    printf("%lf\n", total_time);
    printf("%s\n", procedure);
    
    return 0;
}

