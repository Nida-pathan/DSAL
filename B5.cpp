/*A book consists of chapters, chapters consist of sections and sections consist of
subsections. Construct a tree and print the nodes. Find the time and space requirements
of your method. */

#include <iostream>
#include <string>
using namespace std;

// Structure for representing each node (chapter, section, or subsection)
struct Node {
    string name;        // Name of the chapter, section, or subsection
    bool flag;          // To distinguish between chapter, section, and subsection
    Node* down;         // Pointer to the next level (section/subsection)
    Node* next;         // Pointer to the next sibling at the same level

    // Constructor
    Node(string n, bool f) : name(n), flag(f), down(nullptr), next(nullptr) {}
};

// Class for the book tree
class BookTree {
private:
    Node* root;  // Root of the tree (book)
    string bookName;  // The name of the book

public:
    // Constructor
    BookTree() : root(nullptr) {}

    // Create a new book tree with a book name
    void createBook() {
        cout << "Enter book name: ";
        cin.ignore();
        getline(cin, bookName);
        root = nullptr;
        cout << "Book '" << bookName << "' created successfully.\n";
    }

    // Add a chapter to the book
    void addChapter() {
        string chapterName;
        cout << "Enter chapter name: ";
        cin.ignore();
        getline(cin, chapterName);
        Node* newChapter = new Node(chapterName, true);  // Chapter nodes have flag = true
        if (!root) {
            root = newChapter;
        } else {
            Node* temp = root;
            while (temp->next) {
                temp = temp->next;  // Traverse to the last chapter
            }
            temp->next = newChapter;  // Add the new chapter at the end
        }
        cout << "Chapter '" << chapterName << "' added successfully.\n";
    }

    // Add a section to a chapter
    void addSection() {
        string chapterName, sectionName;
        cout << "Enter chapter name: ";
        cin.ignore();
        getline(cin, chapterName);
        cout << "Enter section name: ";
        getline(cin, sectionName);

        Node* chapter = searchNode(root, chapterName, true);
        if (chapter) {
            Node* newSection = new Node(sectionName, false);  // Section nodes have flag = false
            if (!chapter->down) {
                chapter->down = newSection;  // Add as the first section
            } else {
                Node* temp = chapter->down;
                while (temp->next) {
                    temp = temp->next;  // Traverse to the last section
                }
                temp->next = newSection;  // Add the new section at the end
            }
            cout << "Section '" << sectionName << "' added successfully to chapter '" << chapterName << "'.\n";
        } else {
            cout << "Chapter '" << chapterName << "' not found!\n";
        }
    }

    // Add a subsection to a section
    void addSubsection() {
        string chapterName, sectionName, subsectionName;
        cout << "Enter chapter name: ";
        cin.ignore();
        getline(cin, chapterName);
        cout << "Enter section name: ";
        getline(cin, sectionName);
        cout << "Enter subsection name: ";
        getline(cin, subsectionName);

        Node* chapter = searchNode(root, chapterName, true);
        if (chapter) {
            Node* section = searchNode(chapter->down, sectionName, false);
            if (section) {
                Node* newSubsection = new Node(subsectionName, false);
                if (!section->down) {
                    section->down = newSubsection;  // Add as the first subsection
                } else {
                    Node* temp = section->down;
                    while (temp->next) {
                        temp = temp->next;  // Traverse to the last subsection
                    }
                    temp->next = newSubsection;  // Add the new subsection at the end
                }
                cout << "Subsection '" << subsectionName << "' added successfully to section '" << sectionName << "' in chapter '" << chapterName << "'.\n";
            } else {
                cout << "Section '" << sectionName << "' not found in chapter '" << chapterName << "'.\n";
            }
        } else {
            cout << "Chapter '" << chapterName << "' not found!\n";
        }
    }

    // Display the book tree with improved labeling
    void display(Node* node, int level = 0) {
        if (node) {
            // Print the book name first (only once)
            if (level == 0) {
                cout << "\nBook Name: \"" << bookName << "\"\n";
            }

            // Print the current node's name with proper indentation and labels
            for (int i = 0; i < level; i++) cout << "    ";

            if (node->flag) {
                cout << "Chapter: \"" << node->name << "\"" << endl;  // Chapter
            } else {
                // Check if it's a section or subsection by level of indentation
                if (node->down) {
                    cout << "Section: \"" << node->name << "\"" << endl;  // Section
                } else {
                    cout << "Subsection: \"" << node->name << "\"" << endl;  // Subsection
                }
            }

            // Display the subsections or sections (down level)
            if (node->down) {
                display(node->down, level + 1);  // Display subsections
            }
            // Display the next sibling at the same level (next chapter, section, or subsection)
            display(node->next, level);
        }
    }

    // Search for a chapter, section, or subsection by name
    Node* searchNode(Node* node, const string& name, bool isChapter) {
        while (node) {
            if (node->name == name && node->flag == isChapter) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    // Wrapper for displaying the book
    void showBook() {
        if (root) {
            display(root);
        } else {
            cout << "Book is empty.\n";
        }
    }

    // Wrapper for searching a node
    void searchItem() {
        string name;
        cout << "Enter the name to search: ";
        cin.ignore();
        getline(cin, name);
        Node* result = searchNode(root, name, true);
        if (result) {
            cout << "Found chapter: \"" << result->name << "\"\n";
        } else {
            result = searchNode(root, name, false);
            if (result) {
                cout << "Found section or subsection: \"" << result->name << "\"\n";
            } else {
                cout << "Not found.\n";
            }
        }
    }
};

// Main menu for interacting with the BookTree
int main() {
    BookTree book;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create Book Tree\n";
        cout << "2. Add Chapter\n";
        cout << "3. Add Section\n";
        cout << "4. Add Subsection\n";
        cout << "5. Display Book Tree\n";
        cout << "6. Search Item\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                book.createBook();
                break;
            case 2:
                book.addChapter();
                break;
            case 3:
                book.addSection();
                break;
            case 4:
                book.addSubsection();
                break;
            case 5:
                book.showBook();
                break;
            case 6:
                book.searchItem();
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
