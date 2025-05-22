#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#define INFINITE 100000
using namespace std;

void printHelp() 
{
    cout << "Uso: ./djikstra [opções]" << endl;
    cout << "Opções:" << endl;
    cout << "  -h : mostra o help" << endl;
    cout << "  -o <arquivo> : redireciona a saida para o arquivo" << endl;
    cout << "  -f <arquivo> : indica o arquivo que contém o grafo de entrada" << endl;
    cout << "  -i <vértice> : vértice inicial" << endl;
}

void djikstraAlgorithm(vector<vector<pair<int, int>>> &adj, int source, vector<bool> &visited, 
                      vector<int> &minPath, vector<int> &prev) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Inicializar com o vértice fonte
    pq.push({0, source});
    minPath[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        // Se já visitamos este vértice ou encontramos um caminho melhor, pular
        if (visited[u] || dist > minPath[u]) continue;
        visited[u] = true;

        // Verificar todos os vizinhos
        for (auto &neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // Se encontramos um caminho melhor
            if (minPath[u] + weight < minPath[v]) {
                minPath[v] = minPath[u] + weight;
                prev[v] = u;
                pq.push({minPath[v], v});
            }
        }
    }
}

void printResults(vector<int> &minPath, int source) {
    cout << source << ":0";
    for (int i = 1; i < minPath.size(); i++) {
        if (i != source) {
            cout << " " << i << ":";
            if (minPath[i] == INFINITE) {
                cout << "-1";
            } else {
                cout << minPath[i];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    string inputFile, outputFile;
    int sourceVertex = 1;  // Definir vértice inicial como 1 por padrão
    
    // Processar argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-h") {
            printHelp();
            return 0;
        } else if (arg == "-f" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (arg == "-i" && i + 1 < argc) {
            sourceVertex = stoi(argv[++i]);
        }
    }

    // Verificar parâmetros obrigatórios
    if (inputFile.empty() || sourceVertex == -1) {
        cout << "Erro: Parâmetros obrigatórios não fornecidos" << endl;
        printHelp();
        return 1;
    }

    // Redirecionar saída se necessário
    if (!outputFile.empty()) {
        freopen(outputFile.c_str(), "w", stdout);
    }

    // Abrir arquivo de entrada
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cout << "Erro ao abrir arquivo de entrada" << endl;
        return 1;
    }

    //reading the graph
    int numVertex, numEdges;
    inFile >> numVertex >> numEdges;

    // Ajustar para 1-based indexing
    numVertex++; // Incrementar para acomodar o índice 1-based

    // distance of vertice origin to the others initialized with infinite
    vector<int> edgeMinPath(numVertex, INFINITE);
    // vector of visited or not
    vector<bool> visited(numVertex, false);
    // vector of previous vertex initialized with -1
    vector<int> previousVertex(numVertex, -1);
    //creating adjacence matrix with empty space
    vector<vector<pair<int, int>>> adj(numVertex);
    
    int v, w, h;
    for (int i=0; i<numEdges; i++) {
        inFile >> v >> w >> h;
        // Não precisamos ajustar os índices aqui pois já estamos usando 1-based
        adj[v].push_back({w, h});
        adj[w].push_back({v, h});
    }

    // Inicializar o algoritmo
    edgeMinPath[sourceVertex] = 0;
    djikstraAlgorithm(adj, sourceVertex, visited, edgeMinPath, previousVertex);
    
    // Imprimir resultados no formato especificado
    printResults(edgeMinPath, sourceVertex);

    return 0;
}
