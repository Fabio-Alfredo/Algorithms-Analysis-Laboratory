#include <iostream>
#include "MaxHeap.hpp"
#include "priorityQueue.hpp"
#include "reader.hpp"

using namespace std;

// Function to initialize the client data
void initializeClientData(Client data[], int rows, int cols)
{
    load_data(data, rows, cols);
}

// Function to create and fill the array of incomes
int *createAndFillIncomesArray(Client data[], int rows)
{
    int *incomes = new int[rows];
    for (int i = 0; i < rows; i++)
    {
        incomes[i] = data[i].income;
    }
    return incomes;
}

// Function to display the results
void displayResults(MaxHeap &MaxHeap)
{
    // display the minimum income
    cout << "The minimum income is: " << MaxHeap.getMinimum() << endl;

    // Extract the minimum income
    cout << "The minimum income extracted is: " << MaxHeap.extractMinimum() << endl;

    // display the minimum income
    cout << "The minimum income is: " << MaxHeap.getMinimum() << endl;

    // Decrease the key of the first element
    MaxHeap.decreaseKey(0, 60);

    // display the minimum income
    cout << "The minimum income is: " << MaxHeap.getMinimum() << endl;

    // display the minimum income
    cout << "The minimum income is: " << MaxHeap.getMinimum() << endl;

    

    // display the heap
    MaxHeap.display();

    // Sort the array
    MaxHeap.heapsort();

    // display the sorted array
    MaxHeap.display();
}

int main()
{
    // Define the number of rows and columns
    const int rows = 1000;
    const int cols = 5;

    // Define the array of structures
    Client data[rows];

    // Initialize client data
    initializeClientData(data, rows, cols);

    // Create and fill the array of incomes
    int *incomes = createAndFillIncomesArray(data, rows);

    // Create a MaxHeap object
    MaxHeap MaxHeap(incomes, rows);

    // Insert a new key
    MaxHeap.insert(30);

    // display the results
    displayResults(MaxHeap);


    return 0;
}
