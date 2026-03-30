# Вказуємо компілятор
CXX = g++

# Прапорці компіляції: 
# -Wall показує всі попередження
# -std=c++17 використовує сучасний стандарт
# -I. каже компілятору шукати заголовні файли (.hpp), починаючи з поточної папки (кореня)
CXXFLAGS = -Wall -std=c++17 -I. -Wl,--allow-multiple-definition

# Назва готового файлу програми
TARGET = sort_analyzer

# Перелічуємо всі .cpp файли, які треба скомпілювати разом
SRCS = algorithms/main.cpp \
	AiZO-P1-sortingAlgorithms/Parameters.cpp \
	algorithms/quick_sort.cpp \
       data/get_data.cpp \
       data_generator/generate_random.cpp


$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build success! Run program: ./$(TARGET)"


clean:
	rm -f $(TARGET)
	@echo "Cleaned."
