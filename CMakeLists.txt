# # 1. Podstawowe ustawienia
# cmake_minimum_required(VERSION 3.10)
# project(AiZOSortProject CXX)

# # Ustawienie standardu C++17 (odpowiednik flagi -std=c++17)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Włączenie dodatkowych ostrzeżeń kompilatora (odpowiednik -Wall -Wextra)
# add_compile_options(-Wall -Wextra)

# # =========================================================
# # 2. BIBLIOTEKA DYNAMICZNA (libparameters.so)
# # =========================================================
# # CMake automatycznie doda flagi -shared oraz -fPIC
# add_library(parameters SHARED IMPORTED)

# # Wskazanie ścieżki do skompilowanego pliku .so
# set_target_properties(parameters PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libparameters.so)

# # =========================================================
# # 3. GŁÓWNY PROGRAM (target: program)
# # =========================================================
# add_executable(program
#     main/main.cpp
#     modes/singleMode.cpp
#     modes/benchmark.cpp
#     data/saveBenchmarkResult.cpp
# )

# # =========================================================
# # 4. KONFIGURACJA ŚCIEŻEK NAGŁÓWKÓW (Zastępuje INCLUDES = -I...)
# # =========================================================
# # Dzięki temu można używać ścieżek względem głównego folderu, 
# # np. #include "algorithms/quick_sort.hpp" z dowolnego pliku!
# target_include_directories(program PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}/algorithms
#     ${CMAKE_CURRENT_SOURCE_DIR}/data
#     ${CMAKE_CURRENT_SOURCE_DIR}/data_generator
#     ${CMAKE_CURRENT_SOURCE_DIR}/dispatchers
#     ${CMAKE_CURRENT_SOURCE_DIR}/modes
#     ${CMAKE_CURRENT_SOURCE_DIR}/Structures
#     ${CMAKE_CURRENT_SOURCE_DIR}/Tests
# )

# # =========================================================
# # 5. LINKOWANIE (Zastępuje -L. -lparameters -Wl,-rpath=.)
# # =========================================================
# # Dołączenie dynamicznej biblioteki do głównego programu
# target_link_libraries(program PRIVATE parameters)


# =========================================================
# 1. Podstawowe ustawienia projektu
# =========================================================
cmake_minimum_required(VERSION 3.10)
project(AiZOSortProject CXX)

# Ustawienie standardu C++17 (odpowiednik flagi -std=c++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Włączenie dodatkowych ostrzeżeń kompilatora
add_compile_options(-Wall -Wextra)

# =========================================================
# 2. KONFIGURACJA BIBLIOTEKI DYNAMICZNEJ (libparameters.so)
# =========================================================
# Tworzymy "zaimportowany" cel (target) reprezentujący naszą gotową bibliotekę .so
add_library(parameters SHARED IMPORTED)

# Wskazanie dokładnej ścieżki do skompilowanego pliku .so.
# (Zakładamy, że libparameters.so leży w tym samym folderze co CMakeLists.txt)
set_target_properties(parameters PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libparameters.so"
)

# =========================================================
# 3. GŁÓWNY PROGRAM WYZYKONAWCZY
# =========================================================
# Dodajemy wszystkie pliki źródłowe (.cpp), ale BEZ Parameters.cpp!
add_executable(program
    main/main.cpp
    modes/singleMode.cpp
    modes/benchmark.cpp
    data/saveBenchmarkResult.cpp
)

# =========================================================
# 4. ŚCIEŻKI DO PLIKÓW NAGŁÓWKOWYCH (.hpp / .h)
# =========================================================
# Pozwala to kompilatorowi znaleźć pliki .hpp niezależnie od tego,
# z jakiego pliku je inkludujemy.
target_include_directories(program PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/data_generator
    ${CMAKE_CURRENT_SOURCE_DIR}/dispatchers
    ${CMAKE_CURRENT_SOURCE_DIR}/modes
    ${CMAKE_CURRENT_SOURCE_DIR}/Structures
    ${CMAKE_CURRENT_SOURCE_DIR}/Tests
)

# =========================================================
# 5. LINKOWANIE I RPATH (Ścieżki uruchomieniowe)
# =========================================================
# Linkujemy naszą bibliotekę 'parameters' z głównym programem
target_link_libraries(program PRIVATE parameters)

# BARDZO WAŻNE: Konfiguracja RPATH (Run-time search path)
# Dzięki temu system (Linux) będzie wiedział, żeby szukać pliku libparameters.so
# w folderze z aplikacją ($ORIGIN), a nie tylko w systemowych (/usr/lib).
# Zapobiega to błędowi: "cannot open shared object file".
set_target_properties(program PROPERTIES 
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN"
)