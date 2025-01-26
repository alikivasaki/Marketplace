#ifndef CART_H
#define CART_H

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include "product.h"
using namespace std;

class Cart {
private:
    list<pair<Product*, int>> items; // maintains incertion order
    unordered_map<string, list<pair<Product*, int>>::iterator> item_map; //fast look ups

public:
    //change cart contents
    void add_product(Product& product, int quantity);
    void remove_product(string product_title);
    void update_quantity(Product& product, int new_quantity);

    //print cart
    void print_cart() const;
    float total_cost() const;
    
    void clear_cart();

    //getter
    const list<pair<Product*, int>>& get_items() const {
        return items;
    }

};

#endif
