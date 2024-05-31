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
    std::list<Node>* array_values; //������� ������ ����� (����� ������� � ������ ��������)
    int table_size;

    int hash_function(int key) {
        return key % table_size;
    }
    int lcg() { //���������� � ��������� ������-��������� �����
        static size_t x = 0;
        x = (1021 * x + 24631) % 116640;
        return x;
    }

public:
    HashTable(int size) : table_size(size) {
        array_values = new std::list<Node>[size];
    }

    HashTable(int size, int collisions) : table_size(size) { //�����������, ����������� ��� ������� ���������� ���������� (� ���������� ��� ��� � ��������� ������������� �� ���-��)
        array_values = new std::list<Node>[size];
        /*int n = 1;
        for (int i = 0; i < size; i++) {
            if (collisions) n += lcg() % collisions; //max ���-�� ��������
            for (int j = 0; j < n; j++) {
                int key = size * lcg() - size + i;
                int value = lcg();
                array_values[i].push_back(Node(key, value));
            }
            
        }*/
        for (int i = 0; i < size; i++) {
            if (!collisions) { //��� ��������
                int key = size * rand() - size + i;
                int value = rand();
                array_values[i].push_back(Node(key, value));
            }
            else {
                int n = 1 + rand() % collisions; //max ���-�� ��������
                for (int j = 0; j < n; j++) {
                    int key = size * rand() - size + i;
                    int value = rand();
                    array_values[i].push_back(Node(key, value));
                }
            }
        }
    }

    HashTable(const HashTable& other) { //����������� �����������
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
            std::cout << "Index h(k) = " << i << ": ";

            for (auto& node : array_values[i]) { //������� ���� ��� ��������
                std::cout << "(" << node.key << ", " << node.value << ") ";
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    HashTable& operator=(const HashTable& other) {
        if (this == &other) {
            return *this;
        }

        delete[] array_values;

        table_size = other.table_size;
        array_values = new std::list<Node>[table_size];

        for (int i = 0; i < table_size; i++) {
            array_values[i] = other.array_values[i];
        }

        return *this;
    }
    
    void insert(int key, int value) {
        int index = hash_function(key);
        if (array_values[index].empty()) {
            array_values[index] = std::list<Node>{ Node(key, value) };
        }
        else {
            array_values[index].push_back(Node(key, value));
        }
    }

    void insert_or_assign(int key, int value) {
        int index = hash_function(key);
      
        if (array_values[index].empty()) {
            array_values[index] = std::list<Node>{ Node(key, value) };
        }
        else {
            bool found = false;
            for (auto& node : array_values[index]) {
                if (node.key == key) {
                    node.value = value;//��������� �������� � ������� �����
                    found = true;
                    break;
                }
            }

            if (!found) { //���� ����� ��� - ��������, ��������� � ����� �������
                array_values[index].push_back(Node(key, value));
            }
        }
    }

    bool contains(int value) {
        for (int i = 0; i < table_size; i++) {
            for (auto& node : array_values[i]) {
                if (node.value == value) {
                    return true;
                }
            }
        }

        return false;
    }

    
    bool erase(int key) {
        int index = hash_function(key);

        if (array_values[index].empty()) {
            return false;
            std::cout << "Uncorrect key" << "(" << key << ")" << std::endl;
        }

        for (auto it = array_values[index].begin(); it != array_values[index].end(); ++it) {
            if (it->key == key) {
                array_values[index].erase(it);
                return true;
            }
        }

        return false;
    }

    int count(int key) {
        int count = 0;

        for (int i = 0; i < table_size; i++) {
            for (auto& node : array_values[i]) {
                if (node.key == key) {
                    count++;
                }
            }
        }

        return count;
    }
};
int main(){
    HashTable hash_table1(20,2);//with
    hash_table1.print();
    HashTable hash_table2(20,0);//without
    hash_table2.print();
    hash_table2.insert_or_assign(203456, 134676);
    hash_table2.print();
    if (hash_table2.contains(134676)) std::cout << "Exist" << std::endl;
    /*HashTable hash_table3(hash_table1);
    hash_table3.print();
    HashTable hash_table4(5);
    hash_table4.print();*/
    //hash_table1 = hash_table2;
    //hash_table1.print();
    HashTable hash_table5(2);
    hash_table5.insert_or_assign(203456, 134676);
    hash_table5.print();
    hash_table5.insert(203456, 134677);
    std::cout << hash_table5.count(203456)<< std::endl;
    //hash_table5.erase(203456);
    hash_table5.print();
    return 0;
}