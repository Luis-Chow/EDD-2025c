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

    RoyalNode* findNodeById(RoyalNode* current, int id) {
        if (current == nullptr) return nullptr;
        if (current->id == id) return current;
        RoyalNode* foundLeft = findNodeById(current->left, id);
        if (foundLeft) return foundLeft;
        return findNodeById(current->right, id);
    }

public:
    RoyalTree() : root(nullptr) {}
    
    void loadFromCsv(string filepath) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "Error: No se pudo abrir " << filepath << endl;
            return;
        }

        string line;
        bool isHeader = true;
        while (getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            if (line.empty()) continue;

            stringstream ss(line);
            string segment;
            RoyalNode* newNode = new RoyalNode();

            try {
                getline(ss, segment, ','); newNode->id = stoi(segment);
                getline(ss, segment, ','); newNode->name = segment;
                getline(ss, segment, ','); newNode->last_name = segment;
                getline(ss, segment, ','); newNode->gender = segment[0];
                getline(ss, segment, ','); newNode->age = stoi(segment);
                getline(ss, segment, ','); newNode->id_father = (segment == "" || segment == "0") ? 0 : stoi(segment);
                getline(ss, segment, ','); newNode->is_dead = (segment == "1");
                getline(ss, segment, ','); newNode->was_king = (segment == "1");
                getline(ss, segment, ','); newNode->is_king = (segment == "1");
            } catch (...) { delete newNode; continue; }

            if (newNode->id_father == 0) {
                root = newNode;
            } else {
                RoyalNode* parent = findNodeById(root, newNode->id_father);
                if (parent) {
                    newNode->parent = parent;
                    if (parent->left == nullptr) parent->left = newNode;
                    else if (parent->right == nullptr) parent->right = newNode;
                    else { delete newNode; continue; }
                } else { delete newNode; }
            }
        }
        cout << "Datos cargados exitosamente." << endl;
        file.close();
    }
};

int main() {
    cout << "Sistema Royal Inicializado..." << endl;
    return 0;
}