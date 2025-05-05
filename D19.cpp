/*A Dictionary stores keywords & its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data
sorted in ascending/ Descending order. Also find how many maximum comparisons may
require for finding any keyword. Use Height balance tree and find the complexity for
finding a keyword*/

#include <iostream>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string key, string val) : keyword(key), meaning(val), left(nullptr), right(nullptr), height(1) {}
};

// Custom max function
int maxHeight(int a, int b) {
    return (a > b) ? a : b;
}

// AVL Tree class
class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    void updateHeight(Node* node) {
        node->height = 1 + maxHeight(getHeight(node->left), getHeight(node->right));
    }

    int getBalance(Node* node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, string key, string val) {
        if (node == nullptr) return new Node(key, val);

        if (key < node->keyword)
            node->left = insert(node->left, key, val);
        else if (key > node->keyword)
            node->right = insert(node->right, key, val);
        else {
            node->meaning = val;
            return node;
        }

        updateHeight(node);
        int balance = getBalance(node);

        // Rotations
        if (balance > 1 && key < node->left->keyword)
            return rightRotate(node);
        if (balance < -1 && key > node->right->keyword)
            return leftRotate(node);
        if (balance > 1 && key > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string key) {
        if (root == nullptr) return root;

        if (key < root->keyword)
            root->left = deleteNode(root->left, key);
        else if (key > root->keyword)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }

                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (root == nullptr) return root;

        updateHeight(root);
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inOrder(Node* root) {
        if (root == nullptr) return;
        inOrder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inOrder(root->right);
    }

    void reverseInOrder(Node* root) {
        if (root == nullptr) return;
        reverseInOrder(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        reverseInOrder(root->left);
    }

    Node* search(Node* root, string key, int& comparisons) {
        while (root != nullptr) {
            comparisons++;
            if (key == root->keyword)
                return root;
            else if (key < root->keyword)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string key, string val) {
        root = insert(root, key, val);
    }

    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    void update(string key, string val) {
        root = deleteNode(root, key);
        root = insert(root, key, val);
    }

    void displayAscending() {
        inOrder(root);
    }

    void displayDescending() {
        reverseInOrder(root);
    }

    void searchKeyword(string key) {
        int comparisons = 0;
        Node* result = search(root, key, comparisons);
        if (result)
            cout << "Keyword found: " << result->keyword << " : " << result->meaning << endl;
        else
            cout << "Keyword not found." << endl;
        cout << "Number of comparisons made: " << comparisons << endl;
    }

    int getTreeHeight() {
        return getHeight(root);
    }
};

// Main menu-driven program
int main() {
    AVLTree dictionary;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Search Keyword\n";
        cout << "7. Get Tree Height (Max Comparisons)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dictionary.insert(key, meaning);
                break;

            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dictionary.deleteKeyword(key);
                break;

            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dictionary.update(key, meaning);
                break;

            case 4:
                cout << "Dictionary in ascending order:\n";
                dictionary.displayAscending();
                break;

            case 5:
                cout << "Dictionary in descending order:\n";
                dictionary.displayDescending();
                break;

            case 6:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                dictionary.searchKeyword(key);
                break;

            case 7:
                cout << "Maximum comparisons (tree height): " << dictionary.getTreeHeight() << endl;
                break;

            case 8:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
