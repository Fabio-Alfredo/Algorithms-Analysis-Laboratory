#include <iostream>
#include <sstream>
#include "BST.hpp"

using namespace std;

void mostrarMenu(int& option) {
    cout << "_______________________________________________________" << endl;
    cout << "MENU:\n";
    cout << "1. Ingresar nueva palabra\n";
    cout << "2. Buscar palabras\n";
    cout << "3. Mostrar en inorden\n";
    cout << "4. Salir\n";
    cout << "Ingrese una opción: ";
    cin >> option;
    cout << "_______________________________________________________" << endl;
}

void manejarOpcion(int option, BinarySearchTree& bst) {
    switch (option) {
        case 1: {
            string word;
            cout << "Ingrese una nueva palabra: ";
            cin >> word;
            bst.insert( word);
            break;
        }
        case 2: {
            string search;
            vector<string> suggestions;
            cout << "Ingrese pista para buscar las palabras: ";
            cin >> search;
            suggestions = bst.search(search);
            cout << "\n" << "Palabras encontradas: '" << search << "': ";
            for (const string &word : suggestions) {
                cout << "\n" << word;
            }
            cout << "\n";
            break;
        }
        case 3: {
            vector<string> inOrderResult;
            inOrderResult.clear();
            bst.inorder(inOrderResult);
            cout << "Frases del arbol\n: ";
            for (const string &element : inOrderResult) {
                cout << "\n" << element;
            }
            cout << "\n";
            break;
        }
        case 4:
            cout << "Saliendo.\n";
            break;
        default:
            cout << "Opción invalida. Por favor ingrese una opción válida.\n";
            break;
    }
}

int main(void) {
    BinarySearchTree bst;
    int option = 0;

    string wordsInsert = "apple banana cherry dog elephant frog grape hat igloo jigsaw kangaroo lemon monkey nectarine orange parrot quokka raspberry strawberry tiger umbrella vampire watermelon xylophone yak zebra";
    istringstream iss(wordsInsert);
    string word;

    while (iss >> word) {
        bst.insert( word);
    }

    while (true) {
        mostrarMenu(option);
        manejarOpcion(option, bst);
        if (option == 4) {
            break;
        }
    }

    return 0;
}