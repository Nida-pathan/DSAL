/*A Dictionary stores keywords & its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data
sorted in ascending/ Descending order. Also find how many maximum comparisons may
require for finding any keyword. Use Binary Search Tree for implementation.*/

#include <iostream>
#include <string>
using namespace std;

// Node structure for BST
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;

    Node(string key, string val) : keyword(key), meaning(val), left(nullptr), right(nullptr) {}
};

// BST class for dictionary
class Dictionary {
private:
    Node* root;

    // Helper function to insert a node
    Node* insert(Node* node, string key, string val) {
        if (node == nullptr) {
            return new Node(key, val);
        }
        if (key < node->keyword) {
            node->left = insert(node->left, key, val);
        } else if (key > node->keyword) {
            node->right = insert(node->right, key, val);
        } else {
            node->meaning = val; // Update meaning if keyword already exists
        }
        return node;
    }

    // Helper function to find a node
    Node* find(Node* node, string key, int& comparisons) {
        if (node == nullptr || node->keyword == key) {
            comparisons++;
            return node;
        }
        comparisons++;
        if (key < node->keyword) {
            return find(node->left, key, comparisons);
        } else {
            return find(node->right, key, comparisons);
        }
    }

    // Helper function to delete a node
    Node* remove(Node* node, string key) {
        if (node == nullptr) return nullptr;

        if (key < node->keyword) {
            node->left = remove(node->left, key);
        } else if (key > node->keyword) {
            node->right = remove(node->right, key);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);
            node->keyword = temp->keyword;
            node->meaning = temp->meaning;
            node->right = remove(node->right, temp->keyword);
        }
        return node;
    }

    // Helper function to find the node with the minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper function to display data in ascending order (inorder traversal)
    void displayAscending(Node* node) {
        if (node == nullptr) return;
        displayAscending(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        displayAscending(node->right);
    }

    // Helper function to display data in descending order (reverse inorder traversal)
    void displayDescending(Node* node) {
        if (node == nullptr) return;
        displayDescending(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        displayDescending(node->left);
    }

public:
    Dictionary() : root(nullptr) {}

    // Add a new keyword and meaning
    void addKeyword(string key, string val) {
        root = insert(root, key, val);
        cout << "Keyword added successfully!" << endl;
    }

    // Delete a keyword
    void deleteKeyword(string key) {
        root = remove(root, key);
        cout << "Keyword deleted successfully!" << endl;
    }

    // Update the meaning of a keyword
    void updateKeyword(string key, string val) {
        int comparisons = 0;
        Node* node = find(root, key, comparisons);
        if (node != nullptr) {
            node->meaning = val;
            cout << "Keyword updated successfully!" << endl;
        } else {
            cout << "Keyword not found!" << endl;
        }
    }

    // Display the dictionary in ascending order
    void displayAscending() {
        if (root == nullptr) {
            cout << "Dictionary is empty!" << endl;
            return;
        }
        cout << "Dictionary in ascending order:" << endl;
        displayAscending(root);
    }

    // Display the dictionary in descending order
    void displayDescending() {
        if (root == nullptr) {
            cout << "Dictionary is empty!" << endl;
            return;
        }
        cout << "Dictionary in descending order:" << endl;
        displayDescending(root);
    }

    // Find a keyword and return the number of comparisons
    void findKeyword(string key) {
        int comparisons = 0;
        Node* node = find(root, key, comparisons);
        if (node != nullptr) {
            cout << "Keyword found: " << node->keyword << " : " << node->meaning << endl;
        } else {
            cout << "Keyword not found!" << endl;
        }
        cout << "Number of comparisons: " << comparisons << endl;
    }
};

// Menu function
void menu() {
    Dictionary dict;
    int choice;
    string key, val;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Keyword\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Find Keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore(); // To ignore the newline character left by previous input
                getline(cin, val);
                dict.addKeyword(key, val);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                dict.deleteKeyword(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, val);
                dict.updateKeyword(key, val);
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                cout << "Enter keyword to find: ";
                cin >> key;
                dict.findKeyword(key);
                break;
            case 7:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
