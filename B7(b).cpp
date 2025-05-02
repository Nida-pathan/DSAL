/*For given expression eg. a-b*c-d/e+f construct inorder sequence and traverse it using postorder traversal (non-recursive) and delete the entire tree.*/

#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char value) {
        data = value;
        left = right = nullptr;
    }
};

// Manual stack for characters (operators)
class CharStack {
    char data[50];
    int top;
public:
    CharStack() { top = -1; }
    void push(char c) { data[++top] = c; }
    char pop() { return data[top--]; }
    char peek() { return data[top]; }
    bool empty() { return top == -1; }
};

// Manual stack for Nodes
class NodeStack {
    Node* data[50];
    int top;
public:
    NodeStack() { top = -1; }
    void push(Node* node) { data[++top] = node; }
    Node* pop() { return data[top--]; }
    Node* peek() { return data[top]; }
    bool empty() { return top == -1; }
    int size() { return top + 1; }
};

// Check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Get precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Manually check if alphanumeric
bool isAlnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

// Construct expression tree from infix
Node* constructExpressionTree(string infix) {
    CharStack operators;
    NodeStack nodes;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (c == ' ') continue;

        if (isAlnum(c)) {
            nodes.push(new Node(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.peek() != '(') {
                char op = operators.pop();
                Node* right = nodes.pop();
                Node* left = nodes.pop();
                Node* opNode = new Node(op);
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            if (!operators.empty()) operators.pop(); // Pop '('
        } else if (isOperator(c)) {
            while (!operators.empty() &&
                   precedence(operators.peek()) >= precedence(c)) {
                char op = operators.pop();
                Node* right = nodes.pop();
                Node* left = nodes.pop();
                Node* opNode = new Node(op);
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            operators.push(c);
        } else {
            cout << "Invalid character: " << c << endl;
            return nullptr;
        }
    }

    while (!operators.empty()) {
        char op = operators.pop();
        Node* right = nodes.pop();
        Node* left = nodes.pop();
        Node* opNode = new Node(op);
        opNode->left = left;
        opNode->right = right;
        nodes.push(opNode);
    }

    return nodes.pop(); // Root node
}

// Non-recursive Inorder Traversal
void inorderTraversal(Node* root) {
    if (!root) return;

    NodeStack st;
    Node* current = root;

    while (!st.empty() || current) {
        while (current) {
            st.push(current);
            current = current->left;
        }
        current = st.pop();
        cout << current->data << " ";
        current = current->right;
    }
    cout << endl;
}

// Non-recursive Preorder Traversal
void preorderTraversal(Node* root) {
    if (!root) return;

    NodeStack st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.pop();
        cout << current->data << " ";
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
    cout << endl;
}

// Non-recursive Postorder Traversal
void postOrderTraversal(Node* root) {
    if (!root) return;

    NodeStack st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* current = st1.pop();
        st2.push(current);

        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }

    while (!st2.empty()) {
        cout << st2.pop()->data << " ";
    }
    cout << endl;
}

// Delete the entire tree using postorder logic
void deleteTree(Node* root) {
    if (!root) return;

    NodeStack st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.pop();
        if (current->left) st.push(current->left);
        if (current->right) st.push(current->right);
        delete current;
    }
}

// MAIN MENU
int main() {
    Node* root = nullptr;
    int choice;
    string infix;

    do {
        cout << "\n--- Expression Tree Menu ---\n";
        cout << "1. Enter Infix Expression\n";
        cout << "2. Inorder Traversal (Infix)\n";
        cout << "3. Preorder Traversal (Prefix)\n";
        cout << "4. Postorder Traversal (Postfix)\n";
        cout << "5. Delete Expression Tree\n";
        cout << "6. Exit\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(); // clear buffer

        switch (choice) {
            case 1:
                cout << "Enter infix expression (e.g., a+b*c): ";
                getline(cin, infix);
                if (root) {
                    deleteTree(root);
                    root = nullptr;
                }
                root = constructExpressionTree(infix);
                if (root)
                    cout << "Expression tree constructed successfully.\n";
                else
                    cout << "Failed to construct tree.\n";
                break;
            case 2:
                cout << "Inorder traversal: ";
                inorderTraversal(root);
                break;
            case 3:
                cout << "Preorder traversal: ";
                preorderTraversal(root);
                break;
            case 4:
                cout << "Postorder traversal: ";
                postOrderTraversal(root);
                break;
            case 5:
                deleteTree(root);
                root = nullptr;
                cout << "Tree deleted.\n";
                break;
            case 6:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    // Ensure memory cleanup
    if (root) deleteTree(root);

    return 0;
}
