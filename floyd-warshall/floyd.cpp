#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

void floyd(vector<vector<int>> &dist)
{
    int n = dist.size();
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void print_help()
{
    cout << "Uso: ./floyd -f <arquivo> [-i <vertice>] [-o <arquivo>] [-h]\n";
    cout << "-h              : mostra essa mensagem de ajuda\n";
    cout << "-f <arquivo>    : arquivo de entrada com o grafo\n";
    cout << "-i <vertice>    : vértice inicial para imprimir distâncias\n";
    cout << "-o <arquivo>    : redireciona a saída para o arquivo\n";
}

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    int start_vertex = -1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            print_help();
            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            input_file = argv[++i];
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            output_file = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            start_vertex = atoi(argv[++i]) - 1;
        }
    }

    if (input_file == "")
    {
        cerr << "Erro: parametro -f (arquivo de entrada) obrigatorio.\n";
        return 1;
    }

    ifstream fin(input_file);
    if (!fin.is_open())
    {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    ofstream fout;
    ostream *out = &cout;
    if (output_file != "")
    {
        fout.open(output_file);
        if (!fout.is_open())
        {
            cerr << "Erro ao abrir o arquivo de saida.\n";
            return 1;
        }
        out = &fout;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        fin >> u >> v >> w;
        u--, v--;
        dist[u][v] = w;
    }

    for (int i = 0; i < n; i++)
        dist[i][i] = 0;

    floyd(dist);

    if (start_vertex >= 0 && start_vertex < n)
    {
        // Imprime distâncias do vértice inicial para todos
        for (int j = 0; j < n; j++)
        {
            if (dist[start_vertex][j] == INT_MAX)
                *out << (j + 1) << ":-1 ";
            else
                *out << (j + 1) << ":" << dist[start_vertex][j] << " ";
        }
        *out << endl;
    }
    else
    {
        // Imprime matriz completa
        *out << "Matriz de distancias minimas entre os vertices:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] == INT_MAX)
                    *out << "INF ";
                else
                    *out << dist[i][j] << "   ";
            }
            *out << endl;
        }
    }
}