#pragma once


// Struktura węzła drzewa
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};


// Drzewo poszukiwań binarnych
template <typename T>
class BinaryTree {
public:
    TreeNode<T>* root;

    BinaryTree() : root(nullptr) {}

    // Wstawianie iteracyjne zamiast rekurancji dla biezpieczeństwa w przypadkach, 
    // gdy mamy do sortowania dane już posortowane, czyli tych najgorszych pryzpadków
    void insert(T val) {
       // Jeśli drzewo jest puste, tworzymy jego korzeń
        if (root == nullptr) {
            root = new TreeNode<T>(val);
            return;
        }

        TreeNode<T>* current = root;
        while (true) {
            // mniejsze wartości trafiają do lewego poddrzewa
            if (val < current->data) {
                if (current->left == nullptr) {
                    current->left = new TreeNode<T>(val);
                    break; // Po udanym wstawieniu opuszczamy pętlę
                }
                current = current->left;
            } 
            // większe lub równe wartości trafiają do prawego poddrzewa
            else {
                if (current->right == nullptr) {
                    current->right = new TreeNode<T>(val);
                    break; 
                }
                current = current->right;
            }
        }
    }


    // Odczyt danych metodą in-order, rekurencyjnie przesyła elementy do tablicy
    void inOrderToArray(TreeNode<T>* node, T* arr, int& index) {
        if (node == nullptr) return;
        inOrderToArray(node->left, arr, index);
        arr[index++] = node->data; 
        inOrderToArray(node->right, arr, index);
    }

    // Zwiedzamy całe drzewo od dołu do góry (Post-Order), usuwając najpierw liście, 
    // aby bezpiecznie uwolnić dynamicznie zaalokowaną pamięć bez wycieków
    void destroyTree(TreeNode<T>* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Destruktor drzewa
    ~BinaryTree() {
        destroyTree(root);
    }
};