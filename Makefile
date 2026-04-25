CXX = g++

# Підказуємо компілятору, де лежать файли .hpp
INCLUDES = -I. -Ialgorithms -Idata -Imodes -IStructures -ITests

CXXFLAGS = -std=c++17 -Wall -Wextra  $(INCLUDES)

# Werror - do flag powyzej, ale potem


TARGET = program
LIB = libparameters.so

SOURCES = main/main.cpp \
          modes/singleMode.cpp 
		  

all: $(LIB) $(TARGET)

$(LIB): Parameters.cpp Parameters.h
	$(CXX) $(CXXFLAGS) -shared -fPIC Parameters.cpp -o $(LIB)

$(TARGET): $(SOURCES) $(LIB)
	$(CXX) $(CXXFLAGS) $(SOURCES) -L. -lparameters -Wl,-rpath=. -o $(TARGET)

clean:
	rm -f $(TARGET) $(LIB)
