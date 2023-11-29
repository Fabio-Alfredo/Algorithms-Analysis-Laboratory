#include <iostream>
#include "Laboratorio02.hpp"


using namespace std;

void print(Client *data) {

    for(int i = 0; i < 1000; ++i){
        cout << i << " "<< data[i].name << " "<< 
        data[i].address << " "<< data[i].job << " " 
        << data[i].income << "\n";
    }

    cout << endl << endl << endl;

}

int main(void){
    Client data[1000];
    load_data(data);
    heapSort(data, 1000);

    print(data);
    return 0;
}

