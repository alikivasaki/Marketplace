/*
    An outline of the class Admin
*/
#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "user.h"
#include "category_manager.h"
#include "product_manager.h"
using namespace std;


class Admin: public User{
    //Already has username and password (from User)
    protected:
        //Aixiliary methods for create_new_prod
        string input_title();
        string input_description();
        string input_category_name(CategoryManager& manager);
        string input_subcategory(CategoryManager& manager, string& category_name);
        float input_price();
        string input_measurement_type();
        int input_quantity(string& measurement_type);

    public:
        //Constructors & Destructor
        Admin(string name, string pass);     
        ~Admin();

        //1. Add new product
        void create_new_prod(CategoryManager& categ_manager, ProductManager& prod_manager);
        
        //2. Edit a product
        void edit_prod(CategoryManager& categ_manager, ProductManager& prod_manager);

        //3. Remove a product
        void remove_prod(ProductManager& prod_manager);



        //5. Show Unavailable Products
        void show_unavailable_products(ProductManager& prod_manager);
        
        //Admin Entire Menu
        void admin_menu(CategoryManager& categ_manager, ProductManager& prod_manager);
};

#endif