#ifndef ORDER_HISTORY_H
#define ORDER_HISTORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "product.h"
#include "cart.h"

using namespace std;

class OrderHistory {
private:
    list<string> orders;
    string filename;    

public:
    OrderHistory(const string& customer_name);
    void load_history();
    void save_history() const;
    void add_order(const Cart& cart);
    void print_history() const;
    static void create_history(const string& name);
};

#endif