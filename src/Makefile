# Указываем компилятор
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Папки
SRC_DIR = .
BUILD_DIR = ../build

# Файлы
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/dbms

# Сборка проекта
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Правило сборки объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка сборки
clean:
	rm -f $(BUILD_DIR)/*

# Тесты
test: $(TARGET)
	@echo "Запуск тестов"
