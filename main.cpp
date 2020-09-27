#include <iostream>
#include <sstream>
#include <vector>
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

    cout << "how many commands? "; // remove before submit
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
    }


    /*string user_input;
    cin >> user_input;
    cout << user_input;*/


    return 0;
}