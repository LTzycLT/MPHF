#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#define MP(a, b) make_pair(a, b)
using namespace std;

const int N = 120000, M = 200000;

int h[N][3];
char key[N][30];

int n, m, node_degree[N];
vector<int> a[M];
map<int, int> mp;
set<int> edge[M], degree[N + 1];
vector<int> delete_order;
bool visited[M];
char g[M];

int h0(char *s, int mod)
{
    int ans = 0;
    for(; *s; s++)
    {
        ans = (ans * 31 + *s) % mod; 
    }
    return ans;
}
int h1(char *s, int mod)
{
    int ans = 0;
    for(; *s; s++)
    {
        ans = (ans * 131 + *s) % mod; 
    }
    return ans + mod;
}
int h2(char *s, int mod)
{
    int ans = 0;
    for(; *s; s++)
    {
        ans = (ans * 1313 + *s) % mod; 
    }
    return ans + 2 * mod;
}
void reduce_degree(int u, int e)
{
    int tmp_degree = node_degree[u];
    degree[tmp_degree].erase(degree[tmp_degree].find(u));
    tmp_degree = node_degree[u] = tmp_degree - 1;
    degree[tmp_degree].insert(u);

    edge[u].erase(edge[u].find(e));

}
void delete_edge(int e)
{
    reduce_degree(h[e][0], e);
    reduce_degree(h[e][1], e);
    reduce_degree(h[e][2], e);
}
bool hypergraph_generate()
{
    for(int i = 0; i < n; i++)
    {
        edge[h[i][0]].insert(i);
        edge[h[i][1]].insert(i);
        edge[h[i][2]].insert(i);
        node_degree[h[i][0]]++;
        node_degree[h[i][1]]++;
        node_degree[h[i][2]]++;
    }
    for(int i = 0; i < m; i++)
    {
        degree[node_degree[i]].insert(i);
    }
    for(int i = 0; i < n; i++){
        int u;
        set<int>::iterator it = degree[1].begin();
        if(it != degree[1].end())
        {
            u = *it;
        }
        else
        {
            return 0;
        }
        int e = *edge[u].begin();
        delete_edge(e);
        delete_order.push_back(e);
    }
    for(int i = 0; i < m; i++)
    {
        visited[i] = false;
        g[i] = 3;
    }
    for(int i = n - 1; i >= 0; i--)
    {
        int u = delete_order[i];
        int choice = 0;
        for(int j = 0; j < 3; j++)
        {
            if(!visited[h[u][j]])
            {
                choice = j;
                break;
            }
        }
        int hash_sum = 0;
        for(int j = 0; j < 3; j++)
        {
            hash_sum += g[h[u][j]];
        }
        g[h[u][choice]] = ((choice - hash_sum) % 3 + 3) % 3; 
        visited[h[u][choice]] = true;
    }
    for(int i = 0; i < n; i++)
    {
        printf("%d %s\n", h[i][(g[h[i][0]] + g[h[i][1]] + g[h[i][2]]) % 3], key[i]);
    }

    return 1;
}
int input()
{
    n = 0;
    while(scanf("%s", key[n++]) != EOF);
    m = 1.23 * n;
    set<int> st;
    set<pair<int, pair<int, int> > > hole; 
    for(int i = 0; i < n; i++)
    {
        h[i][0] = h0(key[i], m / 3);
        h[i][1] = h1(key[i], m / 3);
        h[i][2] = h2(key[i], m / 3);

        if(hole.find(MP(h[i][0], MP(h[i][1], h[i][2]))) != hole.end())
        {
            return i;
        }
        else
        {
            hole.insert(MP(h[i][0], MP(h[i][1], h[i][2])));
        }

    }
    return -1;
}
int validate()
{   
    return 1;
}
int main()
{
    freopen("pinyin.txt", "r", stdin);
    freopen("out", "w", stdout);
    fprintf(stderr, "%d\n", input());
    fprintf(stderr, "%d\n", hypergraph_generate()); 
    fprintf(stderr, "%d\n", validate());
    return 0;
}
