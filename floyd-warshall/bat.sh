#!/bin/bash

EXEC=./floyd.bin             # seu executável
INPUT_DIR=testes              # pasta com os arquivos .dat
OUTPUT_DIR=saidas_geradas     # pasta para os arquivos de saida gerados pelo seu programa
EXPECTED_DIR=gabaritos        # pasta com os arquivos de gabarito (respostas corretas)
START_VERTICES=start_vertex.txt

# Cria o diretório de saída se ele não existir
mkdir -p "$OUTPUT_DIR"

# Verifica se o diretório de gabaritos existe
if [ ! -d "$EXPECTED_DIR" ]; then
    echo "AVISO: Diretório de gabaritos '$EXPECTED_DIR' não encontrado."
    echo "Por favor, crie este diretório e coloque os arquivos de resposta esperada nele."
    echo "Os arquivos de gabarito devem ter o mesmo nome que os arquivos de saída gerados (ex: saida_grafo1_v0.txt)."
    echo "A comparação de resultados será pulada se os arquivos de gabarito não forem encontrados."
fi

count=1
while IFS= read -r start_vertex || [ -n "$start_vertex" ]
do
    input_file="$INPUT_DIR/grafo${count}.dat"
    # Nome base do arquivo de saída/gabarito
    output_filename="saida_grafo${count}_v${start_vertex}.txt"
    
    # Caminho completo para o arquivo de saída gerado pelo seu programa
    generated_output_filepath="$OUTPUT_DIR/$output_filename"
    # Caminho completo para o arquivo de gabarito esperado
    expected_answer_filepath="$EXPECTED_DIR/$output_filename"
    
    echo "Processando grafo${count}.dat com vértice inicial $start_vertex..."
    # Executa o programa e salva a saída
    $EXEC -f "$input_file" -i "$start_vertex" > "$generated_output_filepath"
    echo "  Saída gerada em: $generated_output_filepath"

    # Verifica se o arquivo de gabarito existe para comparação
    if [ ! -f "$expected_answer_filepath" ]; then
        echo "  AVISO: Arquivo de gabarito NÃO ENCONTRADO: $expected_answer_filepath"
        echo "  Pulando comparação para este caso."
    # Compara a saída gerada com o gabarito
    elif diff -q "$generated_output_filepath" "$expected_answer_filepath" > /dev/null 2>&1; then
        echo "  Resultado: OK"
    else
        echo "  Resultado: ERRO"
        # Opcional: se quiser ver as diferenças quando há um ERRO, descomente a linha abaixo
        # echo "  Diferenças:" && diff "$generated_output_filepath" "$expected_answer_filepath"
    fi
    echo "------------------------------------------"
    
    count=$((count+1))
done < "$START_VERTICES"

echo "Verificação concluída."
