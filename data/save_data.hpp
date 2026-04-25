#include <fstream>

template <typename T>
void save_data_array(const std::string& path, T* arr, int size) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad" << path << std::endl;
        return;
    }

    file << size << "\n"; 

    for (int i = 0; i < size; ++i) {
        file << arr[i] << "\n";
    }
    
    file.close();
}

template <typename T>
void save_data_single(const std::string& path, SingleNode<T>* head) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad " << path << std::endl;
        return;
    }

    int count = 0;
    SingleNode<T>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    file << count << "\n";

 
    temp = head;
    while (temp != nullptr) {
        file << temp->data << "\n";
        temp = temp->next;
    }

    file.close();
}

template <typename T>
void save_data_double(const std::string& path, DoubleNode<T>* head) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad" << path << std::endl;
        return;
    }

    int count = 0;
    DoubleNode<T>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    file << count << "\n";

    temp = head;
    while (temp != nullptr) {
        file << temp->data << "\n";
        temp = temp->next;
    }

    file.close();
}