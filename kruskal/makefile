# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11

# Nome do executável
TARGET = kruskal.bin

# Arquivo fonte
SRC = kruskal.cpp

# Arquivo objeto
OBJ = $(SRC:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar o arquivo objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)

# Ajuda
help:
	@echo "Uso:"
	@echo "  make       : Compila o programa"
	@echo "  make clean : Remove arquivos gerados"
	@echo "  make help  : Mostra esta ajuda" 