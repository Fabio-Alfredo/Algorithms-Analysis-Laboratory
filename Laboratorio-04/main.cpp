#include <iostream>
#include <ctime>
#include "rb_tree.hpp"
#include "utility.hpp"
#include "pcb.hpp"

using namespace std;

void Insert(Red_Black_Tree& tree, PCB* array, int size) {
    for (int i = 0; i < size; ++i) {
        tree.Insert(array[i]);
    }
}

void Processes(Red_Black_Tree& tree) {
    while (!tree.isEmpty()) {
        PCB mini = tree.Minimum(tree.getRoot())->data;

        tree.Delete(mini);
        cout << "Ejecucion de proceso con:\n";
        mini.DisplayPCB();
        int timeSlice = RandomTimeSlice();
        mini.RecalculateTimeToComplete(timeSlice);
        mini.RecalculateVirtualRuntime(timeSlice);

        if (mini.GetTimeToComplete() > 0) {
            tree.Insert(mini);
        }
    }
}

int main() {
    Red_Black_Tree Tree;
    int const size = 35;
    PCB array[size];

    Insert(Tree, array, size);

    Processes(Tree);

    return 0;
}
