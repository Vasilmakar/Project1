CXX = g++

# -I. wyszukuje pliki .hpp, od korzenia
CXXFLAGS = -Wall -std=c++17 -I. -Wl,--allow-multiple-definition

# nazwa pliku wykonywalnego
TARGET = sort_analyzer

# pliki do kompilacji
FILES = algorithms/main.cpp \
	AiZO-P1-sortingAlgorithms/Parameters.cpp \
	algorithms/quick_sort.cpp \
       data/get_data.cpp \
	   algorithms/benchmark.cpp


$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(FILES)
	@echo "Build success! Run program: ./$(TARGET)"


clean:
	rm -f $(TARGET)
	@echo "Cleaned."
