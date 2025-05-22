#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino, peso;
    
    Aresta(int o, int d, int p) : origem(o), destino(d), peso(p) {}
};

// Estrutura para Union-Find
class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if(px == py) return;
        
        if(rank[px] < rank[py])
            parent[px] = py;
        else if(rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

// Função para ler o grafo do arquivo
vector<Aresta> lerGrafo(const string& arquivo) {
    ifstream in(arquivo);
    int n, m;
    in >> n >> m;
    
    vector<Aresta> arestas;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        in >> u >> v >> w;
        arestas.push_back(Aresta(u-1, v-1, w));
    }
    
    return arestas;
}

// Função para imprimir ajuda
void mostrarAjuda() {
    cout << "Uso: ./kruskal [opções]\n"
         << "Opções:\n"
         << "  -h : mostra esta ajuda\n"
         << "  -o <arquivo> : redireciona a saída para o arquivo\n"
         << "  -f <arquivo> : indica o arquivo que contém o grafo de entrada\n"
         << "  -s : mostra a solução\n"
         << "  -i : vértice inicial (não utilizado no Kruskal)\n";
}

int main(int argc, char* argv[]) {
    string arquivoEntrada;
    string arquivoSaida;
    bool mostrarSolucao = false;
    
    // Processar argumentos da linha de comando
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-h") == 0) {
            mostrarAjuda();
            return 0;
        }
        else if(strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            arquivoEntrada = argv[++i];
        }
        else if(strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            arquivoSaida = argv[++i];
        }
        else if(strcmp(argv[i], "-s") == 0) {
            mostrarSolucao = true;
        }
        // Ignoramos o parâmetro -i pois não é usado no Kruskal
    }
    
    if(arquivoEntrada.empty()) {
        cerr << "Erro: arquivo de entrada não especificado\n";
        return 1;
    }
    
    // Redirecionar saída se necessário
    if(!arquivoSaida.empty()) {
        freopen(arquivoSaida.c_str(), "w", stdout);
    }
    
    // Ler grafo
    vector<Aresta> arestas = lerGrafo(arquivoEntrada);
    int n = 0;
    for(const Aresta& a : arestas) {
        n = max(n, max(a.origem, a.destino) + 1);
    }
    
    // Ordenar arestas por peso
    sort(arestas.begin(), arestas.end(), 
         [](const Aresta& a, const Aresta& b) { return a.peso < b.peso; });
    
    // Algoritmo de Kruskal
    UnionFind uf(n);
    int custoTotal = 0;
    vector<Aresta> agm;
    
    for(const Aresta& a : arestas) {
        if(uf.find(a.origem) != uf.find(a.destino)) {
            uf.unite(a.origem, a.destino);
            custoTotal += a.peso;
            agm.push_back(a);
        }
    }
    
    // Imprimir resultado
    if(mostrarSolucao) {
        for(const Aresta& a : agm) {
            cout << "(" << a.origem + 1 << "," << a.destino + 1 << ") ";
        }
        cout << endl;
    } else {
        cout << custoTotal << endl;
    }
    
    return 0;
}
