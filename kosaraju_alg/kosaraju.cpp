#include <vector>
#include <iostream>
#include <stack>
#include <fstream>
#include <cstring>
using namespace std;

void dfs1(vector<vector<int>> & adj, vector<bool> &visited, int s0, stack<int> &order)
{
    visited[s0] = true;
    for(int v : adj[s0])
    {
        if(!visited[v])
        {
            dfs1(adj, visited, v, order);
        }
    }
    order.push(s0);
}

void dfs2(vector<vector<int>> & trans, vector<bool> &visited, int s0, vector<int> & comp)
{
    visited[s0] = true;
    comp.push_back(s0);
    for(int v : trans[s0])
    {
        if(!visited[v])
        {
            dfs2(trans, visited, v, comp);
        }
    }
}

vector<vector<int>> kosaraju(vector<vector<int>> & adj, vector<vector<int>> & trans, int n)
{
    vector<vector<int>> cfcs;
    stack<int> order;
    vector<bool> visited(n, false);

    for(int i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            dfs1(adj, visited, i, order);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while(!order.empty())
    {
        int v = order.top();
        order.pop();
        if(!visited[v])
        {
            vector<int> comp;
            dfs2(trans, visited, v, comp);
            cfcs.push_back(comp);
        }
    }

    return cfcs;
}

void print_help()
{
    cout << "Uso: ./kosaraju -f <arquivo> [-o <arquivo>] [-h]\n";
    cout << "-h              : mostra essa mensagem de ajuda\n";
    cout << "-f <arquivo>    : arquivo de entrada com o grafo\n";
    cout << "-o <arquivo>    : redireciona a saida para o arquivo\n";
}

int main(int argc, char* argv[])
{
    string input_file = "";
    string output_file = "";

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
    }

    if(input_file == "")
    {
        cerr << "Erro: arquivo de entrada nao especificado com -f\n";
        return 1;
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

    int n, m;
    fin >> n >> m;
    vector<vector<int>> adj(n), trans(n), cfcs;
    for(int i = 0; i < m; i++)
    {
        int v, u;
        fin >> v >> u;
        u--, v--;
        adj[v].push_back(u);
        trans[u].push_back(v);
    }

    cfcs = kosaraju(adj, trans, n);

    for(auto &cfc : cfcs)
{
    for(size_t i = 0; i < cfc.size(); i++)
    {
        *out << cfc[i] + 1;
        if(i != cfc.size() - 1) cout << " ";
    }
    *out << "\n";
}
}