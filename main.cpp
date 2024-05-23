#include <iostream>
using namespace std;
const int hashSize = 1000;
void menu() {
    cout << "(0) shutdown program" << endl;
    cout << "(1) add" << endl;
    cout << "(2) remove" << endl;
    cout << "(3) clear" << endl;
    cout << "(4) contains" << endl;
    cout << "(5) count" << endl;
    cout << "(6) ToArray and cout" << endl;
}

struct HashTree {
    struct Tree {
        struct Node {
            Node* left = nullptr;
            Node* right = nullptr;
            int value = 0;
        };
        int size = 0;
        Node* root = nullptr;
        Node* goTo(int value) {
            Node* current = root;
            while (current != nullptr) {
                if (value == current->value) {
                    return current;
                }
                else if (value < current->value) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            return nullptr;
        }
        void add(int value) {
            Node* newNode = new Node;
            newNode->value = value;
            size++;
            if (size == 1) {
                root = newNode;
                return;
            }
            Node* current = root;
            while (true) {
                if (value < current->value) {
                    if (current->left != nullptr) {
                        current = current->left;
                    }
                    else {
                        current->left = newNode;
                        return;
                    }
                }
                else if (value > current->value) {
                    if (current->right != nullptr) {
                        current = current->right;
                    }
                    else {
                        current->right = newNode;
                        return;
                    }
                }
                else if (value == current->value) {
                    delete newNode;
                    size--;
                    return;
                }
            }
        }
        void remove(int value) {
            Node* parent = nullptr;
            Node* current = root;
            while (current != nullptr) {
                if (value == current->value) {
                    break;
                }
                parent = current;
                if (value < current->value) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            if (current == nullptr) return;
            if ((current->right != nullptr) && (current->left != nullptr)) {
                parent = current;
                Node* min = current->right;
                while (min->left != nullptr) {
                    parent = min;
                    min = min->left;
                }
                current->value = min->value;
                current = min;
            }
            Node* child = nullptr;
            if (current->left != nullptr) {
                child = current->left;
            }
            else {
                child = current->right;
            }
            if (current != root) {
                if (parent->left == current) {
                    parent->left = child;
                }
                else if (parent->right == current) {
                    parent->right = child;
                }
            }
            else {
                root = child;
            }
            delete current;
            size--;
        }
        void clear(Node* current) {
            if (current == nullptr) return;
            clear(current->left);
            clear(current->right);
            delete current;
            size--;
        }
        void clear() {
            clear(root);
            root = nullptr;
        }
        bool contains(int value) {
            if (goTo(value) != nullptr) {
                return true;
            }
            else {
                return false;
            }
        }
        int count() {
            return size;
        }
        void req(int* array, int& index, Node* current) {
            if (current == nullptr) return;
            req(array, index, current->left);
            array[index] = current->value;
            index++;
            req(array, index, current->right);
        }
        int* ToArray() {
            int* array = new int[count()];
            int index = 0;
            req(array, index, root);
            return array;
        }
    };
    Tree* table[hashSize];
    int size;   
    HashTree() {
        size = 0;
        for (int i = 0; i < hashSize; i++) {
            table[i] = nullptr;
        }
    }
    int hashFunc(int value) {
        return abs(value) % hashSize;
    }
    void add(int value) {
        if (contains(value)) return;
        int index = hashFunc(value);
        if (table[index] == nullptr) {
            table[index] = new Tree;
        }
        table[index]->add(value);
        size++;
    }
    void remove(int value) {
        if (!contains(value)) return;
        int index = hashFunc(value);
        if (table[index] == nullptr) return;
        table[index]->remove(value);
        size--;
        }
    void clear() {
        for (int i = 0; i < hashSize; i++) {
            if (table[i] == nullptr) continue;
            table[i]->clear(); 
        }
        size = 0;
    }
    bool contains(int value) {
        int index = hashFunc(value);
        if (table[index] == nullptr) return false;
        if (table[index]->contains(value)) {
            return true;
        }
        else {
            return false;
        }
    }
    int count() {
        return size;
    }
    int* ToArray() {
        int* arr = new int[size];
        int index = 0;
        for (int i = 0; i < hashSize; i++) {
            if (table[i] == nullptr) continue;
            int* treeArr = table[i]->ToArray();
            for (int t = 0; t < table[i]->count(); t++) {
                arr[index] = treeArr[t];
                index++;
            }
        }
        return arr;
    }
};
int main() {
    HashTree hashtree;
    int switch_on;
    int input;
    int* arr;
    while (true) {
        system("cls");
        menu();
        cout << endl;
        cout << "Choice: ";
        cin >> switch_on;
        switch (switch_on) {
        case 0:
            return 0;
        case 1:
            cout << "Value to add: ";
            cin >> input;
            hashtree.add(input);
            cout << "Value is added!";
            break;
        case 2:
            cout << "Value to remove: ";
            cin >> input;
            hashtree.remove(input);
            cout << "Value is removed!";
            break;
        case 3:
            hashtree.clear();
            cout << "Hash tree is cleared!";
            break;
        case 4:
            cout << "Value to search: ";
            cin >> input;
            if (hashtree.contains(input)) {
                cout << "This Value IS IN hash tree!";
            }
            else {
                cout << "This Value IS NOT IN hash tree!";
            }
            break;
        case 5:
            cout << "Hash tree size: " << hashtree.count();
            break;
        case 6:
            arr = hashtree.ToArray();
            for (int i = 0; i < hashtree.count(); i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        default:
            cout << "Unknown command, try again";
            break;
        }
        cout << endl;
        system("pause");
    }
}