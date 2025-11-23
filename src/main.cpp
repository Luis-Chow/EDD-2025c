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

    void printRecursive(RoyalNode* node) {
        if (node == nullptr) return;
        if (!node->is_dead) {
            string role = (node->is_king) ? " [REY/REINA ACTUAL]" : "";
            cout << "- " << node->name << " " << node->last_name 
                 << " (" << node->age << " a, " << node->gender << ")" << role << endl;
        }
        printRecursive(node->left);
        printRecursive(node->right);
    }

    bool findSuccessorRecursive(RoyalNode* node, RoyalNode*& bestMale, RoyalNode*& bestFemale) {
        if (node == nullptr) return false;
        if (!node->is_dead) {
            if (node->gender == 'H' && node->age < 70) {
                bestMale = node; return true; 
            }
            if (node->gender == 'M' && node->age > 15) {
                if (bestFemale == nullptr || node->age < bestFemale->age) bestFemale = node;
            }
        }
        if (findSuccessorRecursive(node->left, bestMale, bestFemale)) return true;
        if (findSuccessorRecursive(node->right, bestMale, bestFemale)) return true;
        return false;
    }

    RoyalNode* findCurrentKingRecursive(RoyalNode* node) {
        if (!node) return nullptr;
        if (node->is_king) return node;
        RoyalNode* leftRes = findCurrentKingRecursive(node->left);
        if (leftRes) return leftRes;
        return findCurrentKingRecursive(node->right);
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

    void printSuccessionLine() {
        cout << "\n--- Linea de Sucesion (Vivos) ---" << endl;
        printRecursive(root);
    }

    void assignNewKing() {
        RoyalNode* current = findCurrentKingRecursive(root);
        bool needNew = false;
        
        if (!current) { needNew = true; cout << "Sin rey actual." << endl; }
        else if (current->is_dead || current->age > 70) {
            cout << "Reinado de " << current->name << " terminado." << endl;
            current->is_king = false; current->was_king = true; needNew = true;
        } else { cout << "El rey sigue reinando." << endl; }

        if (!needNew) return;

        RoyalNode* male = nullptr; RoyalNode* female = nullptr;
        findSuccessorRecursive(root, male, female);
        
        RoyalNode* newKing = (male) ? male : female;
        
        if (newKing) {
            newKing->is_king = true;
            cout << ">>> NUEVO REY/REINA: " << newKing->name << " <<<" << endl;
        } else { cout << "CRISIS: Sin herederos." << endl; }
    }

    void editNode() {
        int id;
        cout << "Ingrese ID del nodo a editar: ";
        cin >> id;
        
        RoyalNode* node = findNodeById(root, id);
        if (!node) {
            cout << "ID no encontrado." << endl;
            return;
        }

        cout << "Editando a: " << node->name << " (Deje '-' para no cambiar)" << endl;
        
        string input;
        cout << "Nuevo Nombre [" << node->name << "]: ";
        cin >> input; 
        if (input != "-") node->name = input;

        cout << "Nueva Edad [" << node->age << "]: ";
        cin >> input;
        if (input != "-") node->age = stoi(input);

        cout << "Esta muerto? (1=Si, 0=No) [" << node->is_dead << "]: ";
        cin >> input;
        if (input != "-") node->is_dead = (input == "1");
        
        cout << "Datos actualizados." << endl;
    }
};

int main() {
    RoyalTree tree;
    string path = "bin/royal_data.csv";
    ifstream check(path);
    if (!check.good()) path = "royal_data.csv";
    check.close();

    tree.loadFromCsv(path);

    bool running = true;
    while (running) {
        cout << "\n1. Ver Linea\n2. Asignar Rey\n3. Editar\n4. Salir\nOp: ";
        int opt; 
        if(!(cin >> opt)) { cin.clear(); cin.ignore(10000,'\n'); continue; }

        switch (opt) {
            case 1: tree.printSuccessionLine(); break;
            case 2: tree.assignNewKing(); break;
            case 3: tree.editNode(); break;
            case 4: running = false; break;
        }
    }
    return 0;
}