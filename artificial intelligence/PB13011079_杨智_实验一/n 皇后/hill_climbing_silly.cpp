#include <cstdio>
#include <set>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

// ALGO 1 for hill_climb; 
// ALGO 2 for simulated_annealing;
#define ALGO 1
// INITSOLUTION 1 for totally randomized initiation;
// INITSOLUTION 2 for math solution;
// INITSOLUTION 3 for reasonable initiation;
#define INITSOLUTION 1
#define RESTART_TIME 100000000
#define LEFT 20
#define INPUT_PATH "./input.txt"

using namespace std;

int shuffle_func(int i)
{
    return rand() % i;
}

int stuck = 0;

class Board
{
public:
    int N;
    int obs_n;
    int obs_p;
    int *solution;
    int *con_row;
    int *con_updiag;
    int *con_downdiag;
    vector<set<int> > queen_row;
    vector<set<int> > queen_updiag;
    vector<set<int> > queen_downdiag;
    int conflicts;
    int* con_candidate;
    set<int> con_candidate_set;
    
    void conflict_candidate()
    {
        for (int i = 0; i < N; i++)
            if (queen_row[i].size() > 1)
                con_candidate_set.insert(queen_row[i].begin(), queen_row[i].end());
        for (int i = 0; i < 2 * N - 1; i++)
            if (queen_updiag[i].size() > 1)
                con_candidate_set.insert(queen_updiag[i].begin(), queen_updiag[i].end());
        for (int i = 0; i < 2 * N - 1; i++)
            if (queen_downdiag[i].size() > 1)
                con_candidate_set.insert(queen_downdiag[i].begin(), queen_downdiag[i].end());
        con_candidate = (int*)malloc(sizeof(int) * (con_candidate_set.size() + 1));
        int i = 1;
        for (set<int>::iterator iter = con_candidate_set.begin(); iter != con_candidate_set.end(); iter++)
            con_candidate[i++] = *(iter);
        con_candidate[0] = (int)con_candidate_set.size();
    }
    
    void consider_all()
    {
        for (int i = 0; i < N; i++)
            queen_row[solution[i]].insert(i);
        for (int i = 0; i < N; i++)
            queen_updiag[N - 1 - solution[i] + i].insert(i);
        for (int i = 0; i < N; i++)
            queen_downdiag[solution[i] + i].insert(i);
    }
    
    void conflict_all()
    {
        for (int i = 0; i < N; i++)
            con_row[i] = (int)queen_row[i].size();
        for (int i = 0; i < 2 * N - 1; i++)
            con_updiag[i] = (int)queen_updiag[i].size();
        for (int i = 0; i < 2 * N - 1; i++)
            con_downdiag[i] = (int)queen_downdiag[i].size();
    }

    int sum_of_con()
    {
        int i;
        int result = 0;
        for (i = 0; i < N; i++)
            result += (con_row[i] > 1);
        for (i = 0; i < 2 * N - 1; i++)
            result += (con_updiag[i] > 1) + (con_downdiag[i] > 1);
        return result;
    }
    
    Board()
    {}
    
    void init_Board()
    {
        freopen(INPUT_PATH, "r", stdin);
        scanf("%d", &N);
        scanf("%d %d", &obs_n, &obs_p);
        solution = (int*)malloc(sizeof(int) * N);
        con_row = (int*)malloc(sizeof(int) * (N));
        con_updiag = (int*)malloc(sizeof(int) * (2 * N - 1));
        con_downdiag = (int*)malloc(sizeof(int) * (2 * N - 1));
        if (INITSOLUTION == 1)
        {
            int i;
            for (i = 0; i < N; i++)
                solution[i] = i;
            random_shuffle(solution, solution + N, shuffle_func);
        }
        else if (INITSOLUTION == 2)
        {
            if ((N % 6) != 2 && (N % 6) != 3)
            {
                if ((N % 2) == 0)
                {
                    int i;
                    for (i = 0; i < N / 2; i++)
                    {
                        solution[i] = 2 * i + 1;
                    }
                    for (int j = i; i < N; i++)
                    {
                        solution[i] = (i - j) * 2;
                    }
                }
                else
                {
                    int i;
                    for (i = 0; i < N / 2; i++)
                    {
                        solution[i] = 2 * i + 1;
                    }
                    for (int j = i; i < N; i++)
                    {
                        solution[i] = (i - j) * 2;
                    }
                }
            }
            else
            {
                int k;
                if ((N % 2) == 0)
                    k = N / 2;
                else
                    k = (N - 1) / 2;
                if ((N % 2) == 0 && (k % 2) == 0)
                {
                    int i = 0;
                    for (int j = k; j <= N; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 2; j <= k - 2; j += 2)
                        solution[i++] = j - 1;
                    for (int j = k + 3; j <= N - 1; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 1; j <= k + 1; j += 2)
                        solution[i++] = j - 1;
                }
                else if ((N % 2) == 1 && (k % 2) == 0)
                {
                    int i = 0;
                    for (int j = k; j <= N - 1; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 2; j <= k - 2; j += 2)
                        solution[i++] = j - 1;
                    for (int j = k + 3; j <= N - 2; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 1; j <= k + 1; j += 2)
                        solution[i++] = j - 1;
                    solution[i++] = N - 1;
                }
                else if ((N % 2) == 0 && (k % 2) == 1)
                {
                    int i = 0;
                    for (int j = k; j <= N - 1; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 1; j <= k - 2; j += 2)
                        solution[i++] = j - 1;
                    for (int j = k + 3; j <= N; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 2; j <= k + 1; j += 2)
                        solution[i++] = j - 1;
                }
                else
                {
                    int i = 0;
                    for (int j = k; j <= N - 2; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 1; j <= k - 2; j += 2)
                        solution[i++] = j - 1;
                    for (int j = k + 3; j <= N - 1; j += 2)
                        solution[i++] = j - 1;
                    for (int j = 2; j <= k + 1; j += 2)
                        solution[i++] = j - 1;
                    solution[i++] = N - 1;
                }
            }
        }
        else if(INITSOLUTION == 3)
        {
            int retry_times = 100 * N;
            int t;
            for (int i = 0; i < N; i++)
                con_row[i] = 0;
            for (int i = 0; i < 2 * N - 1; i++)
                con_updiag[i] = 0;
            for (int i = 0; i < 2 * N - 1; i++)
                con_downdiag[i] = 0;
            for (int i = 0; i < N - LEFT; i++)
            {
                int times = 0;
                t = rand() % N;
                do {
                    t = rand() % N;
                    times++;
                    if (times == retry_times)
                    {
                        times = 0;
                        for (int i = 0; i < N; i++)
                            con_row[i] = 0;
                        for (int i = 0; i < 2 * N - 1; i++)
                            con_updiag[i] = 0;
                        for (int i = 0; i < 2 * N - 1; i++)
                            con_downdiag[i] = 0;
                        i = 0;
                        printf("retry\n");
                        continue;
                    }
                }
                while (!(con_row[t] == 0 && con_updiag[N - 1 - t + i] == 0 && con_downdiag[t + i] == 0));
                con_row[t] = 1;
                con_updiag[N - 1 - t + i] = 1;
                con_downdiag[t + i] = 1;
                solution[i] = t;
            }
            int i;
            if (N - LEFT < 0)
                i = 0;
            else
                i = N - LEFT;
            for ( ; i < N; i++)
                solution[i] = rand() % N;
        }
        if (solution[obs_p] == obs_n)
            solution[obs_p] = (solution[obs_p] + 1) % N;
        init_vector();
        consider_all();
        conflict_all();
        conflicts = sum_of_con();
        conflict_candidate();
    }
    
    void init_vector()
    {
        queen_downdiag.clear();
        queen_updiag.clear();
        queen_row.clear();
        for (int i = 0; i < N; i++)
        {
            set<int> temp;
            queen_row.push_back(temp);
        }
        for (int i = 0; i < 2 * N - 1; i++)
        {
            set<int> temp;
            queen_updiag.push_back(temp);
            set<int> tempp;
            queen_downdiag.push_back(tempp);
        }
    }
    
    
    void display()
    {
        if (N < 15)
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < solution[i]; j++)
                {
                    if (i == obs_p && j == obs_n)
                        printf("@ ");
                    else
                        printf("- ");
                }
                printf("* ");
                for (int j = solution[i] + 1; j < N; j++)
                {
                    if (i == obs_p && j == obs_n)
                        printf("@ ");
                    else
                        printf("- ");
                }
                printf("\n");
            }
    }

    void print_solution()
    {
        for (int i = 0; i < N; i++)
            printf("%d\n", solution[i]);
    }
    
    int num_conflicts(int qn, int qp)
    {
        int cost;
        if (qp < 0)
            qp = solution[qn];
        cost = con_row[qp] + con_updiag[N - 1 - qp + qn] + con_downdiag[qp + qn];
        if (qp == solution[qn])
            cost -= 3;
        return cost;
    }
    
    int max_con_queen()
    {
        vector<int> maxlist;
        maxlist.push_back(0);
        int maxconflicts = num_conflicts(0, -1);
        for (int i = 1; i < N; i++)
        {
            int curconflicts = num_conflicts(i, -1);
            if (curconflicts > maxconflicts)
            {
                maxlist.clear();
                maxlist.push_back(i);
                maxconflicts = curconflicts;
            }
            else if (curconflicts == maxconflicts)
                maxlist.push_back(i);
        }
        return maxlist[rand() % maxlist.size()];
    }
    
    int min_con_queen(int qn)
    {
        vector<int> minlist;
        minlist.push_back(0);
        int minconflicts = num_conflicts(qn, 0);
        for (int i = 1; i < N; i++)
        {
            int curconflicts = num_conflicts(qn, i);
            if (curconflicts < minconflicts)
            {
                minlist.clear();
                minlist.push_back(i);
                minconflicts = curconflicts;
            }
            else if (curconflicts == minconflicts)
                minlist.push_back(i);
        }
        int temp = minlist[rand() % minlist.size()];
        if (qn == obs_p && temp == obs_n && minlist.size() == 1)
        {
            stuck = 1;
            return 0;
        }
        while (1)
        {
            if (qn == obs_p && temp == obs_n)
                temp = minlist[rand() % minlist.size()];
            else
                return temp;
        }
    }
    
    int rand_queen()
    {
        while (con_candidate[0] != 0)
        {
            int ind = rand() % (con_candidate[0]) + 1;
            int qu = con_candidate[ind];
            if (num_conflicts(qu, -1) > 0)
                return qu;
            else
            {
                con_candidate_set.erase(qu);
                con_candidate[ind] = con_candidate[con_candidate[0]--];
            }
        }
        printf("something went wrong\n");
        return -1;
    }
    
    int rand_move(int qn)
    {
        while (1)
        {
            int i = rand() % N;
            if (i != solution[qn] && (qn != obs_p || i != obs_n))
                return i;
        }
    }
    
    void move(int qn, int qp)
    {
        // qn to line qp
        int old_row = solution[qn];
        int old_updiag = N - 1 - old_row + qn;
        int old_downdiag = old_row + qn;
        queen_row[old_row].erase(qn);
        con_row[old_row]--;
        if (con_row[old_row] == 1)
            conflicts--;
        queen_updiag[old_updiag].erase(qn);
        con_updiag[old_updiag]--;
        if (con_updiag[old_updiag] == 1)
            conflicts--;
        queen_downdiag[old_downdiag].erase(qn);
        con_downdiag[old_downdiag]--;
        if (con_downdiag[old_downdiag] == 1)
            conflicts--;
        
        solution[qn] = qp;
        
        int new_updiag = N - 1 - qp + qn;
        int new_downdiag = qn + qp;
        set<int> new_con_candidate_set;
        queen_row[qp].insert(qn);
        con_row[qp] += 1;
        if (con_row[qp] == 2)
        {
            conflicts ++;
            new_con_candidate_set.insert(queen_row[qp].begin(), queen_row[qp].end());
        }
        queen_updiag[new_updiag].insert(qn);
        con_updiag[new_updiag]++;
        if (con_updiag[new_updiag] == 2)
        {
            conflicts ++;
            new_con_candidate_set.insert(queen_updiag[new_updiag].begin(), queen_updiag[new_updiag].end());
        }
        queen_downdiag[new_downdiag].insert(qn);
        con_downdiag[new_downdiag]++;
        if (con_downdiag[new_downdiag] == 2)
        {
            conflicts ++;
            new_con_candidate_set.insert(queen_downdiag[new_downdiag].begin(), queen_downdiag[new_downdiag].end());
        }
        if (!new_con_candidate_set.empty() && ALGO == 2)
        {
            vector<int> temp(new_con_candidate_set.size());
            set_difference(new_con_candidate_set.begin(), new_con_candidate_set.end(), con_candidate_set.begin(), con_candidate_set.end(), temp.begin());
            con_candidate_set.insert(temp.begin(), temp.end());
            con_candidate = (int*)malloc(sizeof(int) * (con_candidate_set.size() + 1));
            int i = 1;
            for (set<int>::iterator iter = con_candidate_set.begin(); iter != con_candidate_set.end(); iter++)
                con_candidate[i++] = *(iter);
            con_candidate[0] = (int)con_candidate_set.size();
        }
    }
    
    int found_solution()
    {
        return conflicts == 0;
    }
    
    void reverse()
    {
        int temp;
        for (int i = 0; i < N / 2; i++)
        {
            temp = solution[i];
            solution[i] = solution[N - 1 - i];
            solution[N - 1 - i] = solution[i];
        }
    }
};

Board board;

void hill_climb()
{
    if (board.found_solution())
        return;
    else if (INITSOLUTION == 2)
    {
        board.reverse();
        return;
    }
    int high;
    int low;
    int step = 0;
    while (1)
    {
        high = board.max_con_queen();
        low = board.min_con_queen(high);
        if (stuck == 1)
        {
            stuck = 0;
            return;
        }
        if (low == board.solution[high])
            // local minumum
            break;
        else
            board.move(high, low);
        step++;
    }
}

int try_this_move(int cost, int next_cost, double measure)
{
    if (next_cost < cost)
        return 1;
    if (((double)rand() / RAND_MAX) <= (exp((cost - next_cost) * measure)))
        return 1;
    else
        return 0;
}

void simulated_annealing()
{
    int measure = 0;
    double delta = 0.005;
    while (1)
    {
        int q = board.rand_queen();
        int cost = board.num_conflicts(q, -1);
        int move = board.rand_move(q);
        int next_cost = board.num_conflicts(q, move);
        if (INITSOLUTION == 3)
        {
            if (try_this_move(cost, next_cost, measure * (delta * ((cost > (board.N - LEFT)) + 5))))
            {
                board.move(q, move);
                if (board.found_solution())
                    return;
            }
        }
        else
            if (try_this_move(cost, next_cost, measure * delta))
            {
                board.move(q, move);
                if (board.found_solution())
                    return;
            }
        measure++;
    }
}

int n_queens()
{
    board.init_Board();
    for (int i = 0; i < RESTART_TIME; i++)
    {
        switch(ALGO){
            case 1:
                hill_climb();
                break;
            case 2:
                simulated_annealing();
                break;
            default:
                exit(0);
        }
        if (board.found_solution())
        {
            //board.display();
            return 1;
        }
        else
            board.init_Board();
    }
    return 0;
}

int main()
{
    int N;
    std::srand (unsigned(time(0)));
    
    clock_t start, finish;
    double totaltime;
    start = clock();
    
    if (n_queens() == 1)
        printf("success");
    else
        printf("fail");
    
    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    printf("%lf\n", totaltime);


    char OUTPUT_PATH[100];
    if (ALGO == 1)
        sprintf(OUTPUT_PATH, "./output_hill_climbing.txt");
    else if(ALGO == 2)
        sprintf(OUTPUT_PATH, "./output_simulated_annealing.txt");
    freopen(OUTPUT_PATH, "w", stdout);
    board.print_solution();
    printf("%lf", totaltime);
    return 0;
}

