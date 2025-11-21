#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct RoyalNode {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_father;
    bool is_dead;
    bool was_king;
    bool is_king;

    RoyalNode* left;
    RoyalNode* right;
    RoyalNode* parent;

    RoyalNode() : left(nullptr), right(nullptr), parent(nullptr) {}
};

class RoyalTree {
private:
    RoyalNode* root;

public:
    RoyalTree() : root(nullptr) {}
    
};

int main() {
    cout << "Sistema Royal Inicializado..." << endl;
    return 0;
}