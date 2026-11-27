# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -Iinclude

# Estrutura de diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos
TARGET = $(BIN_DIR)/tp1.out
INTERATIVO = $(BIN_DIR)/interativo.out
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
LIB_OBJECTS = $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))

# Regra principal
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Versão interativa (lê do teclado até "FIM")
interativo: $(INTERATIVO)

$(INTERATIVO): tools/main_interativo.cpp $(LIB_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Garantir criação dos diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Roda os exemplos de examples/ e compara com a saída esperada
test: $(TARGET)
	@for entrada in examples/*.in; do \
		esperado=$${entrada%.in}.out; \
		if $(TARGET) < $$entrada | diff -q - $$esperado > /dev/null; then \
			echo "ok    $$entrada"; \
		else \
			echo "FALHA $$entrada"; exit 1; \
		fi; \
	done

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all interativo test clean
