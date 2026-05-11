#pragma once


// Struktura węyła kolejki
template <typename T>
struct QueueNode {
    T data;
    QueueNode* next;
    QueueNode(T val) : data(val), next(nullptr) {}
};


// Zaimplementowana struktura działająca na zasadzie FIFO
template <typename T>
class CustomQueue {
public:
    QueueNode<T>* head; // Wskaźnik na początek kolejki
    QueueNode<T>* tail; // Wskaźnik na koniec kolejki
    int size;

    CustomQueue() : head(nullptr), tail(nullptr), size(0) {}

    // funkcja dodawanie do kolejki
    // Nowy element zawsze trafia na sam koniec
    // Dzięki śledzeniu wskaźnika 'tail' operacja wstawiania odbywa się 
    // w czasie stałym O(1), bez konieczności iterowania przez wszystkie węzły.
    void push(T val) {
        QueueNode<T>* newNode = new QueueNode<T>(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // pobieranie elementu z kolejki
    // Pobiera pierwszy element z brzegu , przesuwa początek kolejki dalej 
    // i bezpiecznie zwalnia pamięć po usuniętym węźle.
    T pop() {
        if (head == nullptr) return T();
        QueueNode<T>* temp = head;
        T val = temp->data;
        // Przesuwamy głowę na kolejny węzeł w kolejce
        head = head->next;

        //jeśli po usunięciu kolejka stała się pusta, 
        // musimy wyzerować wskaźnik ogona, aby uniknąć błędów przy kolejnym dodawaniu.
        if (head == nullptr) tail = nullptr;
        delete temp;
        size--;
        return val;
    }
    
    
    // Destruktor klejki
    ~CustomQueue() {
        while (head != nullptr) pop();
    }
};