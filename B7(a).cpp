/*Construct an expression tree from the given prefix expression eg. +--a*bc/def and traverse it using postordertraversal(non recursive) and then delete the entire tree.*/

// BEGINNING OF CODE
#include<iostream>
#include<string.h>
using namespace std;

struct node{
    char data;
    node *left;
    node *right;
};

class tree{
    char prefix[50];
    public:
        node *top;
        void expression(char []);
        void display(node *);
        void deletion(node *node);
};

class stack1{
    public:
        node *data[30];
        int top;
        stack1(){
            top=-1;
        }
        int empty(){
            if(top==-1){
                return 1;
            }
            return 0;
        }
        void push(node *p){
            data[++top]=p;
        }
        
        node *pop(){
        
            return(data[top--]);
        }
};

void tree::expression(char prefix[]){
    char c;
    stack1 s;
    node *t1,*t2;
    int len,i;
    len=strlen(prefix);
    for(i=len-1;i>=0;i--){
        top = new node;
        top->left=NULL;
        top->right=NULL;
        
        if(isalpha(prefix[i])){
            top->data=prefix[i];
            s.push(top);
        }else if(prefix[i]=='+'||prefix[i]=='-'||prefix[i]=='*'||prefix[i]=='/'){
            t2 = s.pop();
            t1=s.pop();
            top->data=prefix[i];
            top->left = t2;
            top->right=t1;
            s.push(top);
        }
    }
    top = s.pop();
}

void tree::display(node *top){
    stack1 s1,s2;
    
    node *T = top;
    s1.push(T);
    while(!s1.empty()){
        T = s1.pop();
        s2.push(T);
        
        if(T->left!=NULL){
            s1.push(T->left);
        }
        
        if(T->right!=NULL){
            s1.push(T->right);
        }
    }
    
    while(!s2.empty()){
        
        top = s2.pop();
        cout<<top->data;
        
    }
    cout<<endl;
}

void tree::deletion(node *node){
    if(node==NULL){
        return;
    }
    deletion(node->left);
    deletion(node->right);
    cout<<"Deleting node: "<<node->data<<endl;
    free(node);
}

int main(){
    tree t;
    char exp1[20];
    
    int ch;
    do{
        cout<<"1 -> Enter prefix expression"<<endl;
        cout<<"2 -> Display postfix Expression"<<endl;
        cout<<"3 -> Deletion"<<endl;
        cout<<"4 -> Exit"<<endl;
        cout<<"Choose an option (1-4):\t";
        cin>>ch;
        
        switch(ch){
        
            case 1:
                cout<<"Enter the expression (eg.: +--a*bc/def):\t";
                cin>>exp1;
                t.expression(exp1);
                break;
            case 2:
                t.display(t.top);
                break;
            case 3:
                t.deletion(t.top);
                break;
            case 4:
                cout<<"\n// END OF CODE\n"<<endl;
                break;
            default:
                cout<<"Choose a valid option (1-4).";
                break;
        }
    }while(ch!=4);
}
// END OF CODE


/*
#include <iostream>
#include <string.h>
using namespace std;

struct node {
    char data;
    node *left;
    node *right;
};

class stack1 {
public:
    node *data[30];
    int top;
    stack1() {
        top = -1;
    }
    int empty() {
        return top == -1;
    }
    void push(node *p) {
        data[++top] = p;
    }
    node *pop() {
        return data[top--];
    }
};

class tree {
public:
    node *top;
    void expression(char[]);
    void display(node *);
    void deletion(node *);
    void inorder(node *);
    void infixToPostfix(char infix[], char postfix[]);
    void buildTreeFromPostfix(char postfix[]);
    int precedence(char);
    bool isOperator(char);
};

// Build expression tree from prefix expression
void tree::expression(char prefix[]) {
    stack1 s;
    node *t1, *t2;
    int len = strlen(prefix);
    for (int i = len - 1; i >= 0; i--) {
        top = new node;
        top->left = top->right = NULL;
        if ((prefix[i] >= 'a' && prefix[i] <= 'z') || (prefix[i] >= 'A' && prefix[i] <= 'Z')) {
            top->data = prefix[i];
            s.push(top);
        } else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/') {
            t2 = s.pop();
            t1 = s.pop();
            top->data = prefix[i];
            top->left = t2;
            top->right = t1;
            s.push(top);
        }
    }
    top = s.pop();
}

// Postorder traversal (non-recursive) – shows postfix expression
void tree::display(node *top) {
    stack1 s1, s2;
    node *T = top;
    s1.push(T);
    while (!s1.empty()) {
        T = s1.pop();
        s2.push(T);
        if (T->left != NULL) s1.push(T->left);
        if (T->right != NULL) s1.push(T->right);
    }
    while (!s2.empty()) {
        top = s2.pop();
        cout << top->data;
    }
    cout << endl;
}

// Inorder traversal (recursive) – shows infix expression
void tree::inorder(node *node) {
    if (node == NULL) return;
    if (node->left != NULL && node->right != NULL) cout << "(";
    inorder(node->left);
    cout << node->data;
    inorder(node->right);
    if (node->left != NULL && node->right != NULL) cout << ")";
}

// Delete entire tree
void tree::deletion(node *node) {
    if (node == NULL) return;
    deletion(node->left);
    deletion(node->right);
    cout << "Deleting node: " << node->data << endl;
    free(node);
}

// Check if character is operator
bool tree::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Get precedence of operator
int tree::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
void tree::infixToPostfix(char infix[], char postfix[]) {
    char stack[50];
    int top = -1, j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            postfix[j++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--; // pop '('
        } else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}

// Build expression tree from postfix
void tree::buildTreeFromPostfix(char postfix[]) {
    stack1 s;
    node *t1, *t2;
    for (int i = 0; postfix[i] != '\0'; i++) {
        node *newNode = new node;
        newNode->left = newNode->right = NULL;
        newNode->data = postfix[i];

        if (isOperator(postfix[i])) {
            t2 = s.pop();
            t1 = s.pop();
            newNode->left = t1;
            newNode->right = t2;
        }
        s.push(newNode);
    }
    top = s.pop();
}

// MAIN
int main() {
    tree t;
    char exp1[50], infixExp[50], postfixExp[50];
    int ch;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1 -> Enter prefix expression\n";
        cout << "2 -> Display postfix expression\n";
        cout << "3 -> Display infix expression\n";
        cout << "4 -> Enter infix expression\n";
        cout << "5 -> Delete tree\n";
        cout << "6 -> Exit\n";
        cout << "Choose an option (1-6): ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter prefix expression (e.g., +--a*bc/def): ";
                cin >> exp1;
                t.expression(exp1);
                break;
            case 2:
                cout << "Postfix expression: ";
                t.display(t.top);
                break;
            case 3:
                cout << "Infix expression: ";
                t.inorder(t.top);
                cout << endl;
                break;
            case 4:
                cout << "Enter infix expression (e.g., a+b*c-d/e): ";
                cin >> infixExp;
                t.infixToPostfix(infixExp, postfixExp);
                cout << "Converted postfix: " << postfixExp << endl;
                t.buildTreeFromPostfix(postfixExp);
                break;
            case 5:
                t.deletion(t.top);
                break;
            case 6:
                cout << "// END OF CODE\n";
                break;
            default:
                cout << "Invalid option, try again.\n";
                break;
        }
    } while (ch != 6);

    return 0;
}
*/
