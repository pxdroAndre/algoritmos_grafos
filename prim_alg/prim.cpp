#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

int prim(vector<vector<pair<int, int>>> & adj, vector<vector<int>> & tree, int s0)
{
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    vector<int> visited(adj.size(), 0);
    vector<int> key(adj.size(), INT_MAX);

    key[s0] = 0;
    pq.push({0, -1, s0});

    for(auto [n, w] : adj[s0])
    {
        pq.push({w, s0, n});
        key[n] = w;
    }

    int weight = 0;

    while(!pq.empty())
    {
        auto [w, u, n] = pq.top();
        pq.pop();

        if(visited[n]) continue;

        visited[n] = true;
        if(u != -1) tree.push_back({u + 1, n + 1});
        weight += w;

        for(auto [v, w_edge] : adj[n])
        {
            if(!visited[v] && w_edge < key[v])
            {
                key[v] = w_edge;
                pq.push({w_edge, n, v});
            }
        }
    }

    return weight;
}

void print_help()
{
    cout << "Uso: ./prim -f <arquivo> -i <vértice> [-s] [-o <arquivo>] [-h]\n";
    cout << "-h              : mostra essa mensagem de ajuda\n";
    cout << "-f <arquivo>    : arquivo de entrada com o grafo\n";
    cout << "-i <vértice>    : vértice inicial\n";
    cout << "-s              : mostra a AGM (arestas)\n";
    cout << "-o <arquivo>    : redireciona a saída para o arquivo\n";
}

int main(int argc, char* argv[])
{
    string input_file = "";
    string output_file = "";
    int s0 = 0;
    bool show_solution = false;

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-h") == 0)
        {
            print_help();
            return 0;
        }
        else if(strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            input_file = argv[++i];
        }
        else if(strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            output_file = argv[++i];
        }
        else if(strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            s0 = atoi(argv[++i]) - 1;
        }
        else if(strcmp(argv[i], "-s") == 0)
        {
            show_solution = true;
        }
    }

    ifstream fin(input_file);
    if(!fin.is_open())
    {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    ofstream fout;
    ostream* out = &cout;
    if(output_file != "")
    {
        fout.open(output_file);
        if(!fout.is_open())
        {
            cerr << "Erro ao abrir o arquivo de saida.\n";
            return 1;
        }
        out = &fout;
    }

    int n, m, primresult;
    fin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);

    for(int i = 0; i < m; i++)
    {
        int u, v, p;
        fin >> u >> v >> p;
        u--, v--;
        adj[u].push_back({v, p});
        adj[v].push_back({u, p});
    }

    vector<vector<int>> tree;

    primresult = prim(adj, tree, s0);

    if(show_solution)
    {
    for(auto &edge : tree)
    {
        if(edge[0] > edge[1]) swap(edge[0], edge[1]);
        *out << "(" << edge[0] << "," << edge[1] << ") ";
    }
    *out << '\n';
    }
    else
    {
        *out << primresult << '\n';
    }
}