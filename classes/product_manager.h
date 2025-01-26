#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "product.h"
using namespace std;

class ProductManager{
    private:
        unordered_map <string, Product> allProducts; 

    protected:
        //Auxiliary methods 
        void fix_line_from_unwanted_spaces(string &line);
    public:
        /*Constructor*/
        ProductManager(string filepath);  //default constructor
        ~ProductManager();

        /*Setters*/
        void set_all_products(string filepath);  //Initializer from the file
        void set_new_product(const Product & prod);  //Καταχώριση νέων προιόντων από Admin
        //Set_details_of_product (specific details) - μπορεί να κάνει remove και add το product updated (ίσως) 
        

        /*Getters*/
        Product get_product(const string& title);  //get a product from the map given a title
        const unordered_map <string, Product>& get_allProducts_map()const;
        Product& get_product_ref(const string& title); //return refrence to the product

        /*Finders*/
        bool find_product(const string& title);  //by title [exist|dont exist]
        bool find_product(const string& title, const string& categ);  //check if the product exists in a given category
        bool find_product(const string& title, const string& categ, const string& sub);
        
        /*Remover*/
        void remove_product(const string& title);
        

        /*Printers*/
        void print_by_title(const string& title);  //Title
        void print_by_category(const string& categ);  //Category
        void print_by_category_and_subcategory(const string& categ, const string& sub);  //Category and subcategory
        void print_available();  //all available
        void print_all();

        /* Save data to products.txt*/
        void save_products();
};


#endif