CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp Robot.cpp Module.cpp Station.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = ark_station

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)