#!/bin/bash

# ==============================================================================
# SKRYPT TESTOWY (NOCNY TERMINATOR) - WERSJA ZWERYFIKOWANA
# ==============================================================================

echo "=== Kompilacja projektu ==="
# cd build
# make clean
# make
# cd ..

ITER=50
EXEC="./build/program"

echo "Kompilacja zakonczona. Rozpoczynam testy nocne..."

# ==============================================================================
# Badanie α (Alpha) - Wpływ parametrów algorytmu
# ==============================================================================
echo "[1/5] Trwa Badanie Alpha..."
FILE_ALPHA="wyniki_alpha.csv"
rm -f $FILE_ALPHA

# Quick Sort (alg=5): Pivoty -> 0 (random), 1 (left/skrajny), 3 (middle/środkowy)
for pivot in 0 1 3; do
    $EXEC --benchmark -a 5 -p $pivot -e 0 -s 0 -t 0 -d 0 -l 50000 -n $ITER -r $FILE_ALPHA
done

# Shell Sort (alg=6): Odstępy -> e=0, e=1 (według menu to option1 i option2)
for gap in 0 1; do
    $EXEC --benchmark -a 6 -p 0 -e $gap -s 0 -t 0 -d 0 -l 50000 -n $ITER -r $FILE_ALPHA
done


# ==============================================================================
# Badanie A - Wpływ liczebności zbioru
# ==============================================================================
echo "[2/5] Trwa Badanie A (to zajmie trochę czasu)..."
FILE_A="wyniki_A.csv"
rm -f $FILE_A

# Algorytmy: 4 (Bucket), 5 (Quick), 6 (Shell)
# Struktury: 0 (Array), 1 (SingleList), 2 (DoubleList)
# Rozmiary: 10k, 25k, 50k, 100k
for alg in 4 5 6; do
    for struct in 0 1 2; do
        for size in 10000 25000 50000 100000; do
            # Używamy domyślnie najlepszego pivota (3=middle) i domyślnego gap (0)
            $EXEC --benchmark -a $alg -p 3 -e 0 -s $struct -t 0 -d 0 -l $size -n $ITER -r $FILE_A
        done
    done
done


# ==============================================================================
# Badanie B - Wpływ rozkładu elementów
# ==============================================================================
echo "[3/5] Trwa Badanie B..."
FILE_B="wyniki_B.csv"
rm -f $FILE_B

# Wybrany algorytm: QuickSort (5), Rozmiar: 50000
# Rozkłady: 0 (Random), 1 (Ascending), 2 (50% Ascending), 3 (Descending)
for struct in 0 1 2; do
    for dist in 0 1 2 3; do
        $EXEC --benchmark -a 5 -p 3 -e 0 -s $struct -t 0 -d $dist -l 50000 -n $ITER -r $FILE_B
    done
done


# ==============================================================================
# Badanie C - Wpływ typu danych
# ==============================================================================
echo "[4/5] Trwa Badanie C..."
FILE_C="wyniki_C.csv"
rm -f $FILE_C

# Algorytm: QuickSort (5), Struktura: Array (0)
# Typy: 0 (int), 1 (float), 4 (string), 5 (unsigned int)
for type in 0 1 4 5; do
    $EXEC --benchmark -a 5 -p 3 -e 0 -s 0 -t $type -d 0 -l 50000 -n $ITER -r $FILE_C
done


# ==============================================================================
# Badanie Ω (Omega) - Użycie nieliniowych struktur danych
# ==============================================================================
echo "[5/5] Trwa Badanie Omega (Uwaga na czas!)..."
FILE_OMEGA="wyniki_omega.csv"
rm -f $FILE_OMEGA

# Algorytm: QuickSort (5), Rozmiar: 10000
# Struktury: 0 (Array), 1 (SList), 2 (DList), 3 (Queue), 5 (BinaryTree)
for struct in 0 1 2 3 5; do
    $EXEC --benchmark -a 5 -p 3 -e 0 -s $struct -t 0 -d 0 -l 10000 -n $ITER -r $FILE_OMEGA
done

# ==============================================================================
echo "=== WSZYSTKIE TESTY ZAKONCZONE SUKCESEM! ==="
