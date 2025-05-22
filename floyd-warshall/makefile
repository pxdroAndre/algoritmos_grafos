# Nome do compilador
CXX = g++

# Flags de compilação (modifique se quiser otimizações ou warnings)
CXXFLAGS = -std=c++17 -Wall -O2

# Nome do executável 
TARGET = floyd.bin

# Arquivo fonte
SRC = floyd.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
