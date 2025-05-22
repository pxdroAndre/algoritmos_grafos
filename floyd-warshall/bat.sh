#!/bin/bash

EXEC=./floyd               # seu executável
INPUT_DIR=testes       # pasta com os arquivos .dat
START_VERTICES=start_vertex.txt

count=1
while IFS= read -r start_vertex || [ -n "$start_vertex" ]
do
    input_file="$INPUT_DIR/grafo${count}.dat"
    
    echo "Saída para grafo${count} com vértice inicial $start_vertex:"
    $EXEC -f "$input_file" -i "$start_vertex"
    echo "------------------------------------------"
    
    count=$((count+1))
done < "$START_VERTICES"