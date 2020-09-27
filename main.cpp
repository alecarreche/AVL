#include <iostream>
using namespace std;

class AVL {

public:
    struct Student {
    public:
        int ID;
        string name;
        Student* left;
        Student* right;
        int height;
    };

    // Constructors
    AVL();
    AVL(Student* root);

    // User functions
    void insert(string nameID);
    void removeID(int ID);
    void searchID(int ID);
    void searchName(string name);
    void printInOrder();
    void printPostOrder();
    void printLevelCount();
    void removeInOrder(int N);

    // Helper functions

    // Balancers


private:
    Student* root;
};

AVL::AVL() {
    root = nullptr;
}

AVL::AVL(Student* root_) {
    root = root_;
}

int main() {
    AVL::Student test;
    test.ID = 0;
    test.name = "test";
    test.left = nullptr;
    test.right = nullptr;
    test.height = 0;

    AVL test_tree = AVL(&test);
    return 0;
}