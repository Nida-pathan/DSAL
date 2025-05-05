#include <iostream>
#include <stack>
#include <cctype>
#include <stdexcept>

using namespace std;

// Node structure for the expression tree
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = right = nullptr;
    }
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // For non-operators
}

// Function to construct the expression tree from the infix expression
Node* constructExpressionTree(string infix) {
    stack<Node*> nodes; // Stack to hold nodes
    stack<char> operators; // Stack to hold operators and parentheses

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // Skip spaces
        if (isspace(c)) continue;

        // If the character is an operand, create a node and push it to the nodes stack
        if (isalnum(c)) {
            nodes.push(new Node(c));
        }
        // If the character is an opening parenthesis, push it to the operators stack
        else if (c == '(') {
            operators.push(c);
        }
        // If the character is a closing parenthesis, process the operators stack until an opening parenthesis is found
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                Node* opNode = new Node(operators.top());
                operators.pop();

                Node* right = nodes.top();
                nodes.pop();
                Node* left = nodes.top();
                nodes.pop();

                opNode->left = left;
                opNode->right = right;

                nodes.push(opNode);
            }
            operators.pop(); // Pop the '('
        }
        // If the character is an operator, process the operators stack based on precedence
        else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                Node* opNode = new Node(operators.top());
                operators.pop();

                Node* right = nodes.top();
                nodes.pop();
                Node* left = nodes.top();
                nodes.pop();

                opNode->left = left;
                opNode->right = right;

                nodes.push(opNode);
            }
            operators.push(c);
        } else {
            throw invalid_argument("Invalid character in expression");
        }
    }

    // Process any remaining operators in the stack
    while (!operators.empty()) {
        Node* opNode = new Node(operators.top());
        operators.pop();

        Node* right = nodes.top();
        nodes.pop();
        Node* left = nodes.top();
        nodes.pop();

        opNode->left = left;
        opNode->right = right;

        nodes.push(opNode);
    }

    // The final node in the nodes stack is the root of the expression tree
    if (nodes.size() != 1) {
        throw invalid_argument("Invalid expression");
    }

    return nodes.top();
}

// Function to perform inorder traversal (non-recursive)
void inorderTraversal(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    Node* current = root;

    while (!st.empty() || current != nullptr) {
        // Reach the leftmost node of the current node
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        // Current must be nullptr at this point
        current = st.top();
        st.pop();

        // Print the data
        cout << current->data << " ";

        // Move to the right subtree
        current = current->right;
    }
    cout << endl;
}

// Function to perform preorder traversal (non-recursive)
void preorderTraversal(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        // Print the data
        cout << current->data << " ";

        // Push the right child first (so that the left child is processed first)
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
    cout << endl;
}

// Function to perform post-order traversal (non-recursive)
void postOrderTraversal(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* current = st1.top();
        st1.pop();
        st2.push(current);

        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }

    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
    cout << endl;
}

// Function to delete the entire tree using post-order traversal
void deleteTree(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        if (current->left) st.push(current->left);
        if (current->right) st.push(current->right);

        delete current;
    }
}

int main() {
    string infix;
    cout << "Enter the infix expression: ";
    getline(cin, infix);

    try {
        // Construct the expression tree
        Node* root = constructExpressionTree(infix);

        // Display inorder traversal (should match the infix expression with proper parentheses)
        cout << "Inorder traversal: ";
        inorderTraversal(root);

        // Display preorder traversal (prefix expression)
        cout << "Preorder traversal (Prefix expression): ";
        preorderTraversal(root);

        // Perform post-order traversal
        cout << "Post-order traversal: ";
        postOrderTraversal(root);

        // Delete the entire tree
        deleteTree(root);
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
