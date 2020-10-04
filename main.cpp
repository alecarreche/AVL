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
    string printPostOrder(Student* node);
    int printLevelCount(Student* node);
    void removeInOrder(Student* node, int N);

    // Helper functions
    int getHeight(Student* node);
    Student* findSuccessor(Student* node);
    vector<Student*> inOrderVector(Student* node, vector<Student*> list);

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

    // left left
    if(node->balance > 1 && ID < node->left->ID)
        node = rotateRight(node);

    // right right
    else if(node->balance < -1 && node->right->ID)
        node = rotateLeft(node);

    // left right
    else if(node->balance > 1 && ID > node->right->ID)
        node = rotateLeftRight(node);

    // right left
    else if(node->balance < -1 && ID < node->left->ID)
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
    else {
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
    AVL test;
    AVL::Student* root = nullptr;
    root = test.insert(root, 12, "twelve");
    root = test.insert(root, 8, "eight");
    root = test.insert(root, 18, "eighteen");
    root = test.insert(root, 5, "five");
    root = test.insert(root, 11, "eleven");
    root = test.insert(root, 17, "seventeen");
    root = test.insert(root, 4, "four");
    root = test.insert(root, 7, "seven");
    root = test.insert(root, 2, "two");

    try {
        root = test.insert(root, 11, "two");
    } catch (invalid_argument e){
        cout << "already in tree" << endl;
    }


    try {
        AVL::Student *search = test.searchID(root, 1);
    } catch (invalid_argument e){
        cout << "not found in tree" << endl;
    }

    string inorder = test.printInOrder(root);
    cout << inorder.substr(0, inorder.size() - 2) << endl;

    string postorder = test.printPostOrder(root);
    cout << postorder.substr(0, postorder.size() - 2) << endl;

    string searchName = test.searchName(root, "seven");
    cout << searchName.substr(0, searchName.size() - 1) << endl;

    root = test.insert(root, 77, "seven");

    string searchName2 = test.searchName(root, "seven");
    cout << searchName2.substr(0, searchName2.size() - 1) << endl;

    root = test.removeID(root, 77);
    string inorder2 = test.printInOrder(root);
    cout << inorder2.substr(0, inorder2.size() - 2) << endl;

    int removeIdx = 0;
    test.removeInOrder(root, removeIdx);
    string inorder3 = test.printInOrder(root);
    cout << inorder3.substr(0, inorder3.size() - 2) << endl;


    /*vector<AVL::Student*> testVector;
    testVector = test.inOrderVector(root, testVector);
    for (auto x : testVector)
        cout << x->ID << " ";*/

    cout << "done" << endl;






    /*cout << "how many commands? "; // remove before submit
    unsigned long numCommands;
    cin >> numCommands;
    cin.ignore(10000, '\n'); // resets cin

    for(unsigned long i = 0; i < numCommands; i++) {
        string userInput;

        cout << "command: " << i+1 << " "; // remove before submit

        getline(cin, userInput);
        int spacePos = userInput.find(" ");
        string command = userInput.substr(0, spacePos);

        cout << command << endl; // remove before submit

        if(command == "insert") {
            // insert value into temporary node
            // if temp node
            //    print success
            //    root = temp
            // else
            //     print unsuccess
        } else if(command == "remove") {

        } else if(command == "search") {

        } else if(command == "printInorder") {

        } else if(command == "printPreorder") {

        } else if(command == "printPostorder") {

        } else if(command == "printLevelCount") {

        } else if(command == "removeInorder") {

        }

        string params = userInput.substr(spacePos + 1);
        int spacePos2 = params.find(" ");
        string param1 = params.substr(0, spacePos2);
        cout << userInput << endl;
        cout << command << endl;
        cout << param1 << endl;
    }*/


    /*string user_input;
    cin >> user_input;
    cout << user_input;*/


    return 0;
}