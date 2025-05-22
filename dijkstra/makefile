# Compilador
CXX = g++
# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11
# Nome do executável
TARGET = djikstra.bin
# Arquivos fonte
SRCS = dijkstra.cpp
# Arquivos objeto (gerados automaticamente)
OBJS = $(SRCS:.cpp=.o)

# Regra padrão (compila o programa)
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar cada arquivo .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos objeto e executável
clean:
	rm -f $(OBJS) $(TARGET)

# Executar o programa (opcional)
run: $(TARGET)
	./$(TARGET) -f input.txt -i 1  # Exemplo de uso

# Ajuda (mostra como usar o Makefile)
help:
	@echo "Uso:"
	@echo "  make       : Compila o programa"
	@echo "  make clean : Remove arquivos gerados"
	@echo "  make run   : Executa o programa (exemplo)"
	@echo "  make help  : Mostra esta ajuda"
