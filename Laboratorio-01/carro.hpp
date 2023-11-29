#pragma once 
#include <string>

using namespace std;

class carro 
{
    private:
    //atributes 
    string _brand;
    int _year;
    int _price;

    public: 
    //constructor
    carro (string, int, int );
    //getter 
    string getbrand ();
    int getyear ();
    int getprice ();
    //setter 
    void setbrand (string);
    void setyear (int); 
    void setprice (int);
};