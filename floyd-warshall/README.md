# Floyd-Warshall - Algoritmo de Caminhos Mínimos


## Descrição

Este programa implementa o algoritmo de Floyd-Warshall para encontrar as distâncias mínimas entre todos os pares de vértices em um grafo direcionado ponderado.
Uso

O programa recebe um arquivo de entrada que representa o grafo e pode receber parâmetros para controlar a saída.
Parâmetros

    -h : Exibe a mensagem de ajuda.

    -f <arquivo> : Indica o arquivo de entrada contendo o grafo (obrigatório).

    -i <vértice> : (Opcional) Exibe apenas as distâncias a partir do vértice inicial indicado.

    -o <arquivo> : (Opcional) Redireciona a saída para o arquivo especificado.


# As entradas foram geradas de forma aleatória com no máximo 200 vértices e 20000 arestas, pode ser visualizado no arquivo gerar.cpp


Testes Automatizados (Bat)

Para facilitar a execução dos testes da bateria Bat, foi criado o script bat.sh que:

    Executa o programa para os 20 arquivos de entrada da pasta bat_inputs/.

    Compara as saídas com as saídas dos testes presentes na pasta gabaritos/.

    Usa o arquivo start_vertices.txt para definir o vértice inicial para cada arquivo.

    Guarda as saídas em uma pasta chamada saidas_geradas/

# Como usar o bat.sh

    Coloque os arquivos .dat dos grafos na pasta testes/, nomeados como grafo1.dat, grafo2.dat, ..., grafo20.dat.

    Crie o arquivo start_vertex.txt com 20 linhas, cada linha com o vértice inicial para o respectivo arquivo.

    Certifique-se de que bat.sh esteja na mesma pasta que floyd.bin, gabaritos/, testes/ e start_vertex.txt

    Dê permissão para o script:

chmod +x bat.sh  

Execute o script:

    ./bat.sh  

O script vai rodar o programa para cada entrada de teste e comparar com as saídas presentes em gabaritos/ mostrando OK no terminal se estiverem corretas.
