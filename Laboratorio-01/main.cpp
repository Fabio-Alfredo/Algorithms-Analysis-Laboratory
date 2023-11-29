#include "iostream"
#include "carro.cpp"

using namespace std;
void SelectionSort(carro* arr, int n);
void BurbboleSort(carro* arr, int n);

int main(){

    carro Toyota("Toyota", 2020, 30000);
    carro Honda("Honda", 2015, 5000);
    carro Nissan("Nissan", 2023, 20000);
    carro Kia("Kia", 2008, 8000);

    carro arr[4] = {Toyota, Honda, Nissan, Kia};
    SelectionSort(arr, 4);
    for(int i =0; i <4; i++){
        cout << arr[i].getyear() << endl;
    }
    BurbboleSort(arr, 4);
    cout << "\n \n";
    for(int i = 0; i<4 ;i++){
        cout << arr[i].getprice()<< endl;
    }
    return 0;
}

void swap(carro* arr, int i, int min)
{
    carro temp = arr[i];
    arr[i] = arr[min];
    arr[min] = temp;

}

void SelectionSort(carro* arr, int n){
    
    for(int i = 0; i < n; i++){
        int  min = i;

        for(int j = i+1; j < n; j++){
            if(arr[j].getyear() < arr[min].getyear()){
                min = j;
            }
        }

        if(min != i){
            swap(arr, i, min);
        }

    }
}



void BurbboleSort(carro* arr, int n){
    
    for (int i = 0; i < n - 1; i++) {

        for (int j = n - 1; j > i; j--) {

            if (arr[j].getprice() > arr[j - 1].getprice()) {

                swap(arr[j], arr[j - 1]);
            }
        }
    }
}