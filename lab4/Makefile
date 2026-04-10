CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp Station.cpp Robot.cpp IntegratorRobot.cpp KeeperRobot.cpp LocalCalculatorRobot.cpp Module.cpp ArchiveModule.cpp ControlCenterModule.cpp HousingModule.cpp GeneratorModule.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = ark_station

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
