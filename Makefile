# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./src/headers

# Директории
SRC_DIR := ./src/sources
BUILD_DIR := ./build
BIN_DIR := .

SOURCES := main.cpp \
           $(SRC_DIR)/DataManager.cpp \
           $(SRC_DIR)/Backpack.cpp

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET := $(BIN_DIR)/genalg

# Имя исполняемого файла
TARGET := $(BIN_DIR)/genalg

# Основная цель
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Правило для объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean