#include <iostream>
#include "reader.hpp"

using namespace std;
/**
 * Realiza la operación de min-heapify en un montículo representado como un arreglo de Clientes.
 *  data El arreglo de Clientes.
 *  n    El tamaño del montículo.
 *  i    El índice de la raíz del subárbol para hacer heapify.
 */
void minHeapify(Client *data, int n, int i) {
    int shorter = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // Comprueba si el hijo izquierdo es menor que el nodo actual.
    if (l < n && data[l].income < data[shorter].income) {
        shorter = l;
    } else {
        shorter = i;
    }
    // Comprueba si el hijo derecho es menor que el nodo actual o el hijo izquierdo.
    if (r < n && data[r].income < data[shorter].income) {
        shorter = r;
    }

    // Si el índice del nodo más pequeño ha cambiado, intercambia los nodos y realiza min-heapify recursivamente.
    if (shorter != i) {
        swap(data[i], data[shorter]);
        minHeapify(data, n, shorter);
    }
}

/**
 * Extrae el elemento mínimo de un montículo representado como un arreglo de Clientes.
 *  data El arreglo de Clientes.
 *  n    El tamaño del montículo.
 */
void extractMinHeap(Client *data, int n) {
    for (int i = n - 1;  i >= 0; --i) {
        // Intercambia el elemento mínimo con el último elemento del montículo
        swap(data[0], data[i]);
        // Realiza min-heapify en el subárbol reducido.
        minHeapify(data, i, 0);
    }
}

/**
 * Construye un montículo mínimo a partir de un arreglo de Clientes.
 *  data El arreglo de Clientes.
 *  n    El tamaño del montículo.
 */
void buildMinHeap(Client *data, int n){
    // Comienza desde el último nodo que tiene hijos y realiza min-heapify en cada nodo hacia arriba.
    for (int i = (n / 2) - 1; i >= 0; --i) {
        minHeapify(data, n, i);
    }
}

/**
 * Ordena un arreglo de Clientes en orden ascendente utilizando Heap Sort.
 *  data El arreglo de Clientes.
 *  n    El tamaño del arreglo.
 */


void heapSort(Client *data, int n) {
    // Construye un montículo mínimo a partir del arreglo dado.
    buildMinHeap(data, n);
    // Extrae el elemento mínimo repetidamente, lo que resulta en un arreglo ordenado.
    extractMinHeap(data, n);
}

