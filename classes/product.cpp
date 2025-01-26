/*
    The definitions of the functions of the class Product
*/
#include <iostream>
#include <string>
#include "product.h"
using namespace std;


/*
    CONSTRUCTORS & DESTRUCTOR
*/
//All the variables given
Product::Product(string title, string description, string category_name, string subcategory, float price, string measurement_type, int quantity){
    this->title = title;
    this->description = description;
    this->category_name = category_name;
    this->subcategory = subcategory;
    this->price = price;
    this->measurement_type = measurement_type;
    this->quantity = quantity;
}

Product::Product(){}

//Destructor
Product::~Product(){}


/*
    SETTERS - Editors (to edit each one individually)
*/
void Product::set_title(const string& title){
    this->title = title;   //setting new title
}

void Product::set_description(const string& description){
    this->description = description;   //setting new description
}

void Product::set_category_name(const string& category){
    this->category_name = category_name;   //setting new name of category
}

void Product::set_subcategory(const string& sub){
    this->subcategory = sub;  //setting new subcategories
}

void Product::set_price(const float& price){
    this->price = price;   //setting new price
}

void Product::set_measurement_type(const string& measurement_type){
    this->measurement_type = measurement_type;   //setting new measurement type as kg or unit
}

void Product::set_quantity(const int& quantity){
    this->quantity = quantity;   //setting new quantity
}


/*
    GETTERS
*/
string Product::get_title()const{
    return title;
}

string Product::get_description()const{
    return description;
}

string Product::get_category_name()const{
    return category_name;
}

string Product::get_subcategory()const{
    return subcategory;
}

float Product::get_price()const{
    return price;
}

string Product::get_measurement_type()const{
    return measurement_type;
}

int Product::get_quantity()const{
    return quantity;
}


/*
    PRINTERS
*/
void Product::print(){
    cout << "-----" << get_title() << "-----" << endl;
    cout << "Description: " << get_description() << endl;
    cout << "Category: " << get_category_name() << endl;
    cout << "Subcategory: " << get_subcategory() << endl;
    cout << "Price per unit: " << get_price() << "€" << endl;
    cout << "Total " << get_measurement_type() << " available: " << get_quantity() << endl;
    cout << "\n";
}