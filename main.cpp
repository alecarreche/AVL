#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class AVL {

public:
    struct Student {
    public:
        long ID;
        string name;
        Student* left;
        Student* right;
        int balance;

        Student(long ID_, string name_) {
            ID = ID_;
            name = name_;
            left = nullptr;
            right = nullptr;
            balance = 0;
        };
    };

    // User functions
    Student* insert(Student* node, long ID, string name);
    Student* removeID(Student* node, long ID);
    Student* searchID(Student* node, long ID);
    string searchName(Student* node, string name);
    string printInOrder(Student* node);
    string printPreOrder(Student* node);
    string printPostOrder(Student* node);
    int printLevelCount(Student* node);
    void removeInOrder(Student* node, int N);

    // Helper functions
    int getHeight(Student* node);
    Student* findSuccessor(Student* node);
    vector<Student*> inOrderVector(Student* node, vector<Student*> list);
    void verifyParams(string command, string params);

    // Rotations
    Student* rotateLeft(Student* node);
    Student* rotateRight(Student* node);
    Student* rotateLeftRight(Student* node);
    Student* rotateRightLeft(Student* node);

};

AVL::Student* AVL::insert(Student* node, long ID, string name) {
    if(!node) {
        return new Student(ID, name);
    } else if(ID == node->ID) {
        throw invalid_argument("");
    } else if(ID < node->ID) {
        node->left = insert(node->left, ID, name);
    } else {
        node->right = insert(node->right, ID, name);
    }

    node->balance = getHeight(node->left) - getHeight(node->right);

    // left left case
    if(node->balance > 1 && ID < node->left->ID)
        node = rotateRight(node);

    // right right case
    else if(node->balance < -1 && ID > node->right->ID)
        node = rotateLeft(node);

    // left right case
    else if(node->balance > 1 && ID > node->left->ID)
        node = rotateLeftRight(node);

    // right left case
    else if(node->balance < -1 && ID < node->right->ID)
        node = rotateRightLeft(node);

    return node;
}

AVL::Student* AVL::removeID(Student* node, long ID) {
    if(!node)
        throw invalid_argument("");

    if(ID == node->ID) {
        if(node->right) {
            Student *replacementNode = findSuccessor(node);
            replacementNode->left = node->left;
            replacementNode->right = node->right;
            node = replacementNode;
        } else {
            node = node->left;
        }
    } else if(ID < node->ID)
        node->left = removeID(node->left, ID);
    else
        node->right = removeID(node->right, ID);

    return node;

}

AVL::Student* AVL::searchID(Student* node, long ID) {
    if(!node)
        throw invalid_argument("");

    if(ID == node->ID)
        return node;
    else if(ID < node->ID)
        return searchID(node->left, ID);
    else
        return searchID(node->right, ID);
}

string AVL::searchName(Student* node, string name) {
    string result = "";
    if(node) {
        if(node->name == name)
            result += to_string(node->ID) + '\n';

        result += searchName(node->left, name);
        result += searchName(node->right, name);
    }

    return result;

}

string AVL::printInOrder(Student* node) {
    string result = "";
    if(node) {
        result += printInOrder(node->left);
        result += node->name + ", ";
        result += printInOrder(node->right);
    }

    return result;

}

string AVL::printPreOrder(Student* node) {
    string result = "";
    if(node) {
        result += node->name + ", ";
        result += printPreOrder(node->left);
        result += printPreOrder(node->right);
    }

    return result;

}

string AVL::printPostOrder(Student* node) {
    string result = "";
    if(node) {
        result += printPostOrder(node->left);
        result += printPostOrder(node->right);
        result += node->name + ", ";
    }

    return result;
}

int AVL::printLevelCount(Student* node) {
    return getHeight(node);
}

void AVL::removeInOrder(Student* node, int N) {
    vector<Student*> flattened;
    flattened = inOrderVector(node, flattened);
    if(N >= flattened.size())
        throw invalid_argument("");
    else removeID(node, flattened[N]->ID);

}

int AVL::getHeight(Student* node) {
    if(!node)
        return 0;

    int leftHeight = 1;
    leftHeight += getHeight(node->left);

    int rightHeight = 1;
    rightHeight += getHeight(node->right);

    return max(leftHeight, rightHeight);
}

AVL::Student* AVL::findSuccessor(Student* node) {
    Student* successor = nullptr;
    if(node->left && node->left->left)
        findSuccessor(node->left);
    else if(node->right && !node->left) {
        successor = node->right;
        node->right = successor->right;
    } else {
        successor = node->left;
        node->left = successor->right;
    }

    return successor;
}

vector<AVL::Student*> AVL::inOrderVector(Student* node, vector<Student*> list) {
    if(node) {
        list = inOrderVector(node->left, list);
        list.push_back(node);
        list = inOrderVector(node->right, list);
    }

    return list;
}

void AVL::verifyParams(string command, string params) {
    string openQuote = "“";
    string closeQuote = "”";

    if(command == "insert") {
        string ID = params.substr(params.size() - 8, 8);
        for(auto c : ID) {
            if(isspace(c))
                throw invalid_argument("");
        }

        string name = params.substr(0, params.size()- 9);
        if(name[0] != '\"' || name[name.size()-1] != '\"')
            throw invalid_argument("");
    } else if(command == "remove" || command == "searchID") {
        if(params.size() != 8)
            throw invalid_argument("");
        for(auto c : params) {
            if(isspace(c))
                throw invalid_argument("");
        }
    } else { // searchName case
        if(params[0] != '\"' || params[params.size()-1] != '\"')
            throw invalid_argument("");
    }
}

AVL::Student* AVL::rotateLeft(Student* node) {
    Student* grandchild = node->right->left;
    Student* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent;
}

AVL::Student* AVL::rotateRight(Student* node) {
    Student* grandchild = node->left->right;
    Student* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    return newParent;
}

AVL::Student* AVL::rotateLeftRight(Student* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVL::Student* AVL::rotateRightLeft(Student* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

int main() {

    AVL tree;
    AVL::Student *treeRoot = nullptr;
    unsigned long numCommands;
    cin >> numCommands;
    cin.ignore(10000, '\n'); // resets cin

    for(unsigned long i = 0; i < numCommands; i++) {
        string userInput;

        getline(cin, userInput);
        int spacePos = userInput.find(" ");
        string command = userInput.substr(0, spacePos);
        string params = userInput.substr(spacePos + 1);

        if (command == "insert") {
            try {
                tree.verifyParams("insert", params);
                string ID = params.substr(params.size() - 8, 8);
                string name = params.substr(0, params.size() - 9);
                long longID = stol(ID);
//                string nameNoQuote = name.substr(3, name.size()-
                string nameNoQuote = name.substr(1, name.size() - 2);
                treeRoot = tree.insert(treeRoot, longID, nameNoQuote);
                cout << "successful" << endl;
            } catch (invalid_argument e) {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "remove") {
            try {
                tree.verifyParams("remove", params);
                long longID = stol(params);
                treeRoot = tree.removeID(treeRoot, longID);
                cout << "successful" << endl;
            } catch (invalid_argument e) {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "search") {
            bool searchID = true;
            long longID;
            try {
                longID = stol(params);
            } catch (invalid_argument e) {
                searchID = false;
            }

            if (searchID) {
                try {
                    tree.verifyParams("searchID", params);
                    AVL::Student *result = tree.searchID(treeRoot, longID);
                    cout << result->name << endl;
                } catch (invalid_argument e) {
                    cout << "unsuccessful" << endl;
                }
            } else {
                try {
                    tree.verifyParams("searchName", params);
                    string nameNoQuote = params.substr(1, params.size() - 2);
                    string result = tree.searchName(treeRoot, nameNoQuote);
                    if (result == "")
                        cout << "unsuccessful" << endl;
                    else
                        cout << result.substr(0, result.size() - 1) << endl;
                } catch (invalid_argument e) {
                    cout << "unsuccessful" << endl;
                }
            }

        } else if (command == "printInorder") {
            string inorder = tree.printInOrder(treeRoot);
            cout << inorder.substr(0, inorder.size() - 2) << endl;
        } else if (command == "printPreorder") {
            string preorder = tree.printPreOrder(treeRoot);
            cout << preorder.substr(0, preorder.size() - 2) << endl;
        } else if (command == "printPostorder") {
            string postorder = tree.printPostOrder(treeRoot);
            cout << postorder.substr(0, postorder.size() - 2) << endl;
        } else if (command == "printLevelCount") {
            cout << tree.printLevelCount(treeRoot) << endl;
        } else if (command == "removeInorder") {
            try {
                int N = stoi(params);
                tree.removeInOrder(treeRoot, N);
                cout << "successful" << endl;
            } catch (invalid_argument e) {
                cout << "unsuccessful" << endl;
            }
        }
    }

    return 0;
}