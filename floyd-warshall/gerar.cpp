#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>

using namespace std;

void gerarGrafoAleatorio(const string& nomeArquivo, int minV, int maxV, int maxArestasPermitidas)
{
    int n = minV + rand() % (maxV - minV + 1);

    int maxArestasTeorico = n * (n - 1); // sem laços

    int maxArestas = maxArestasPermitidas;
    if (maxArestas > maxArestasTeorico)
        maxArestas = maxArestasTeorico;

    int m = n - 1 + rand() % (maxArestas - (n - 1) + 1);

    ofstream fout(nomeArquivo);
    if (!fout.is_open())
    {
        cerr << "Erro ao abrir arquivo " << nomeArquivo << endl;
        return;
    }

    fout << n << " " << m << "\n";

    set<pair<int,int>> arestas;

    for (int i = 1; i < n; i++)
    {
        int u = i;
        int v = i + 1;
        int w = 1 + rand() % 20;
        arestas.insert({u, v});
        fout << u << " " << v << " " << w << "\n";
    }

    while ((int)arestas.size() < m)
    {
        int u = 1 + rand() % n;
        int v = 1 + rand() % n;
        if (u == v) continue;
        if (arestas.count({u,v}) > 0) continue;

        int w = 1 + rand() % 20;
        arestas.insert({u,v});
        fout << u << " " << v << " " << w << "\n";
    }

    fout.close();
}

int main()
{
    srand(time(NULL));

    int minVertices = 5;
    int maxVertices = 200;
    int maxArestasPermitidas = 20000;

    for(int i = 1; i <= 20; i++)
    {
        string nomeArquivo = "grafo" + to_string(i) + ".dat";
        gerarGrafoAleatorio(nomeArquivo, minVertices, maxVertices, maxArestasPermitidas);
        cout << "Gerado arquivo: " << nomeArquivo << endl;
    }

    cout << "Geração concluída.\n";
    return 0;
}
