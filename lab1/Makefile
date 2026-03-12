CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp Calculator.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = metro_calc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)