#include "carro.hpp"

//constructor

carro::carro (string brand, int year, int price):

    _brand  (brand),
    _year (year),
    _price (price)
    
{}
//brand 
   //getter 
    string carro::getbrand ()
    { 
         return _brand;
    }
    //setter
    void carro::setbrand (string brand)
    {
        _brand = brand;
    }
//year 
    //getter
    int carro::getyear ()
    {
        return _year;
    }
    //setter 
    void carro::setyear (int year)
    {
        _year = year;
    }
//price
    //getter
    int carro::getprice ()
    {
        return _price;
    }
    //setter
    void carro::setprice (int price)
    {
        _price = price;
    }