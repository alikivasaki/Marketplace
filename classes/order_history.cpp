#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>
#include <sstream>
#include "product.h"
#include "cart.h"
#include "order_history.h"

using namespace std;

OrderHistory::OrderHistory(const string& customer_name) {
    filename = "files/order_history/" + customer_name + "_history.txt";
    load_history();
}

void OrderHistory::load_history() {
    ifstream file(filename);  
    if (!file.is_open()) {    
        cerr << "Failed to open history file: " << filename << endl;
        return;               
    }

    string line, order;       
    while (getline(file, line)) {  

        if (line.empty()) { //skip empty lines
            continue; 
        }

        if (line.find("Total Cost: ") != string::npos) { //if line has total cost push this order and clear 
            order += line + "\n";       
            orders.push_back(order);   
            order.clear();              
        } else {
            order += line + "\n";       
        }
    }
    file.close();  

    // auto it =next(orders.begin());
    // cout << *it << endl;
} 

void OrderHistory::add_order(const Cart& cart) {
    string order;
    int cart_number = orders.size() + 1;

    order += "---CART " + to_string(cart_number) + " START---\n";
    for (const auto& item : cart.get_items()) {
        order += to_string(item.second) + " " + item.first->get_title() + "\n";
    }
    order += "---CART " + to_string(cart_number) + " END---\n";
    order += "Total Cost: " ;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << cart.total_cost(); //format with 2 decimal places

    order += oss.str() + "\n";

    orders.push_back(order);
}


void OrderHistory::print_history() const {
    if (orders.size() == 0) {
        cout << "No history\n\n";
    }
    
    for (const auto& order : orders) {
        cout << order;
        cout << "\n";
    }
}

void OrderHistory::save_history() const {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) return;

    for (const auto& order : orders) {
        file << order << "\n";
    }
    file.close();
}

void OrderHistory::create_history(const string& name) {
    string filename = "files/order_history/" + name + "_history.txt"; 
    ofstream file(filename);           
    if (file.is_open()) {
        file.close();                             
    } else {
        cerr << "Error: Could not create file '" << filename << "'." << endl;
    }
}
