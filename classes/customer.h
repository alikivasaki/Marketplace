#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include "user.h"
#include "cart.h"
#include "product.h"
#include "product_manager.h"
#include "category.h"
#include "category_manager.h"
#include "order_history.h"

using namespace std;


class Customer: public User{
    private:
        Cart* cart; 
        OrderHistory* order_history; 
    public:
        Customer(string name, string pass);  
        ~Customer();

        void add_to_cart(Product& product, int quantity);
        void update_cart(Product& product, int new_quantity);
        void remove_from_cart(string product_title);
        void print_cart() const;

        void checkout();
        void print_order_history() const;

        void menu(ProductManager& pmanager, CategoryManager& cmanager);
};

#endif