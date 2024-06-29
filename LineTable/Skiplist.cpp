#include <iostream>
#include <cstdlib> // for rand()

const int MAX_LEVEL = 16; // Maximum level of the skip list

struct Node {
    int data;
    Node** forward; // Array to hold pointers to next nodes at each level
    Node(int data, int level) : data(data) {
        forward = new Node*[level + 1];
        std::fill_n(forward, level + 1, nullptr); // Initialize all levels to nullptr
    }
    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    Node* header;
    int level;
public:
    SkipList() {
        header = new Node(-1, MAX_LEVEL); // Create header node with minimum possible value
        level = 0;
    }

    ~SkipList() {
        delete header;
    }

    // Function to generate random level for a new node
    int randomLevel() {
        int lvl = 0;
        while (rand() < RAND_MAX / 2 && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    // Function to insert a value into the skip list
    void insert(int data) {
        Node* current = header;
        Node* update[MAX_LEVEL + 1]; // Array to hold update pointers
        std::fill_n(update, MAX_LEVEL + 1, nullptr); // Initialize update array

        // Traverse levels and find appropriate nodes
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->data < data)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];

        // If data is not present, insert it
        if (current == nullptr || current->data != data) {
            int newLevel = randomLevel();

            // If random level is greater than current level, update update array
            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++)
                    update[i] = header;
                level = newLevel;
            }

            // Create new node with random level generated
            Node* newNode = new Node(data, newLevel);

            // Insert node by rearranging pointers
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            std::cout << "Inserted " << data << std::endl;
        }
    }

    // Function to search for a value in the skip list
    bool search(int data) {
        Node* current = header;

        // Traverse levels and find node with given value
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->data < data)
                current = current->forward[i];
        }

        current = current->forward[0];

        // If node with given value is found, return true
        if (current != nullptr && current->data == data) {
            std::cout << data << " found in skip list" << std::endl;
            return true;
        }

        std::cout << data << " not found in skip list" << std::endl;
        return false;
    }

    // Function to delete a value from the skip list
    void erase(int data) {
        Node* current = header;
        Node* update[MAX_LEVEL + 1]; // Array to hold update pointers
        std::fill_n(update, MAX_LEVEL + 1, nullptr); // Initialize update array

        // Traverse levels and find node to delete
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->data < data)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];

        // If node with given value is found, delete it
        if (current != nullptr && current->data == data) {
            // Rearrange pointers to skip the node to be deleted
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }

            // Remove levels with no elements
            while (level > 0 && header->forward[level] == nullptr)
                level--;

            delete current;
            std::cout << "Deleted " << data << " from skip list" << std::endl;
        }
    }

    // Function to print skip list
    void display() {
        std::cout << "Skip List levels:" << std::endl;
        for (int i = 0; i <= level; i++) {
            Node* node = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (node != nullptr) {
                std::cout << node->data << " ";
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
    }
};

// Main function for testing the skip list
int main() {
    SkipList skipList;
    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    skipList.insert(19);
    skipList.insert(17);
    skipList.insert(26);
    skipList.insert(21);
    skipList.insert(25);
    skipList.display();

    skipList.search(19);
    skipList.search(10);

    skipList.erase(19);
    skipList.erase(17);
    skipList.display();

    return 0;
}