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
    void removeID(Student* node, long ID);
    Student* searchID(Student* node, long ID);
    void searchName(Student* node, string name);
    void printInOrder();
    void printPostOrder();
    void printLevelCount();
    void removeInOrder(int N);

    // Helper functions
    int getHeight(Student* node);

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

void AVL::removeID(Student* node, long ID) {

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

void AVL::searchName(Student* node, string name) {

}

void AVL::printInOrder() {

}

void AVL::printPostOrder() {

}

void AVL::printLevelCount() {

}

void AVL::removeInOrder(int N) {

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
        cout << "not found in tree";
    }





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