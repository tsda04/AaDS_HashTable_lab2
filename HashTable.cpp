#include <cstdlib>
#include <iostream>
#include <list>
#include <cmath>

struct Node {
    int key;
    int value;
    Node(int key, int value) : key(key), value(value) {}
};

class HashTable {
private:
    std::list<Node>* array_values; //связный список узлов (метод цепочек в случае коллизий)
    int table_size;

    int hash_function(int key) {
        return key % table_size;
    }

public:
    HashTable(int table_size) : table_size(table_size) {
        array_values = new std::list<Node>[table_size];
    }
    
    HashTable(int size, int range, bool with_collisions) : table_size(size) { //конструктор, заполняющий хэш таблицу случайными значениями (1 - с коллизиями, 0 - без)
        array_values = new std::list<Node>[size];
        if (!with_collisions) { //без коллизий
            for (int i = 0; i < size; i++) {
                int key = size * rand() + i;
                int value = rand() % range;

                array_values[i].push_back(Node(key, value));
            }
        }
        else {
            for (int i = 0; i < size; i++) {
                int key = rand();
                int index = hash_function(key);
                int value = rand() % range;

                array_values[index].push_back(Node(key, value));
            }
        }
    }
    HashTable(const HashTable& other) { //конструктор копирования
        table_size = other.table_size;
        array_values = new std::list<Node>[table_size];

        for (int i = 0; i < table_size; i++) {
            array_values[i] = other.array_values[i];
        }
    }

    ~HashTable() {
        delete[] array_values;
    }
    void print() {
        for (int i = 0; i < table_size; i++) {
            std::cout << "Index HT " << i << ": ";

            for (auto& node : array_values[i]) { //перебор всех пар значений
                std::cout << "(" << node.key << ", " << node.value << ") ";
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};
int main(){
    HashTable hash_table1(20, 3,1);
    hash_table1.print();
    HashTable hash_table2(20, 3, 0);
    hash_table2.print();
    HashTable hash_table3(hash_table1);
    hash_table3.print();
    HashTable hash_table4(5);
    hash_table4.print();
    return 0;
}