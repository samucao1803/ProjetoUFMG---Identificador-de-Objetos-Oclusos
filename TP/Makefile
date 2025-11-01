# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Iinclude

# Estrutura de diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos
TARGET = $(BIN_DIR)/tp1.out
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Regra principal
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Garantir criação dos diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
