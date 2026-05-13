CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = build

# Ищем все исходники
SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
# Формируем пути для объектных файлов в папке build
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

EXEC = ark_station

all: $(EXEC)

# Линковка исполняемого файла
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Универсальное правило для компиляции .cpp в .o внутри папки build
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка всего мусора
clean:
	rm -rf $(OBJ_DIR) $(EXEC)
	rm -f *.o src/*.o
