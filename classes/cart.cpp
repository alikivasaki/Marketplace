#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include "product.h"
#include "cart.h"

using namespace std;

void Cart::add_product(Product& product, int quantity) {   
    if (item_map.find(product.get_title()) != item_map.end()) { //check if product is in the car
            cout << "Product already in cart\n";
        } else {
            if (product.get_quantity() < quantity) {   //chaeck available quantity
                quantity = product.get_quantity();
                cout << "The quantity you selcted is not available. Adding " << quantity << "\n";
            }
            items.push_back(make_pair(&product, quantity)); //add product
            item_map[product.get_title()] = --items.end();
        }
}

void Cart::update_quantity(Product& product, int quantity) {   
    if (item_map.find(product.get_title()) == item_map.end()) {
            cout << "Product not in cart\n";
        } else {
            if (product.get_quantity() < quantity) {
                quantity = product.get_quantity();
                cout << "The quantity you selcted is not available. Adding " << quantity << "\n";
            }
            auto it = item_map[product.get_title()]; //get iterator
            it->second = quantity; //update product
        }
}   

void Cart::remove_product(string product_title) {
    auto it = item_map.find(product_title);
    if (it != item_map.end()) {
        items.erase(it->second); //remove from list
        item_map.erase(it);      //remove from map
    } else {
        cout << "Product wasn't in cart\n";
    }
}

void Cart::print_cart() const {
    cout << "---CART START---" << endl;
    for (const auto& item : items) {
        cout << item.second << " " << item.first->get_title() << endl;
    }
    cout << "---CART END---" << endl;
    cout <<"Total Cost: " << total_cost() << "\n\n";
}

float Cart::total_cost() const {
        float total = 0.0;
        for (const auto& item : items) {
            total += item.first->get_price() * item.second;
        }
        return total;
}

void Cart::clear_cart() {
        items.clear();
        item_map.clear();
}


