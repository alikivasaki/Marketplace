/*
    The outline of the Class Product
*/
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;


class Product{
    private:
        string title;  
        string description;
        string category_name;
        string subcategory;
        float price;
        string measurement_type;  // kg or units
        int quantity;  //the available quantity of the product

    public:
        //Basic Functions
        Product(string title, string description, string category_name, string subcategory, float price, string measurement_type, int quantity); //All parameters passed
        Product();  //with no arguments
        ~Product();  

        //Setters/Editors (editing each variable individually)
        void set_title(const string& title);
        void set_description(const string& description);
        void set_category_name(const string& category);  
        void set_subcategory(const string& sub);  
        void set_price(const float& price);
        void set_measurement_type(const string& measurement_type);
        void set_quantity(const int& quantity);


        //Getters
        string get_title()const;
        string get_description()const;
        string get_category_name()const;
        string get_subcategory()const;
        float get_price()const;
        string get_measurement_type()const;
        int get_quantity()const;


        //Printers
        void print();  //prints every element of a Product
        

};

#endif