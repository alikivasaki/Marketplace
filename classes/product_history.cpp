#include "product_history.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>


unordered_map<string, int> ProductHistory::product_purchase_count;

void ProductHistory::load_user_histories(const string& directory_path) {
    for (const auto& entry : filesystem::directory_iterator(directory_path)) {
        ifstream file(entry.path());
        if (!file.is_open()) {
            cerr << "Failed to open user history file: " << entry.path() << endl;
            continue;
        }

        string line;
        while (getline(file, line)) {
            if (line.find("---CART") != string::npos) {
                continue;
            }

            if (line.find("END---") != string::npos) {
                continue;
            }

            if (line.find("Total Cost:") != string::npos) {
                continue;
            }

            istringstream iss(line);
            string title;
            iss >> title;
            iss >> title;    
            if (!title.empty() && title[0] == ' ') {
                title = title.substr(1);
            }

            if (!title.empty()) {
                update_purchase_count(title);
            } 
        }

        file.close();
    }

}

void ProductHistory::update_purchase_count(const string& product_name) {
    product_purchase_count[product_name] += 1;
}

void ProductHistory::save_product_history(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open product history file: " << filename << endl;
        return;
    }

    for (const auto& product : product_purchase_count) {
        file << product.first << "," << product.second << endl;
    }

    file.close();
    //cout << "Product history saved to " << filename << endl;
}


void ProductHistory::create_histrory(const string& filename) {
    if (!filesystem::exists(filename)) { //create file on first run by loading pre-existing historie
        ofstream create_file(filename);
        if (!create_file.is_open()) {
            cerr << "Failed to create product history file: " << filename << endl;
            return;
        }
        create_file.close();

        load_user_histories("files/order_history/");
        save_product_history("files/product_history.txt");
    } else {
        ifstream file(filename);  //else use the product_history.txt file to load the history
        if (!file.is_open()) {    
            cerr << "Failed to open user file: " << filename << endl;
            return;              
        }

        string line;
        while (getline(file, line)) {
            istringstream current_line(line);
            string title, count;

            if (getline(current_line, title, ',') && getline(current_line, count, ',')) {

                product_purchase_count[title] = stoi(count);

            }
        }

        file.close();
        }

}

void ProductHistory::show_top_products() {
    vector<pair<string, int>> products(product_purchase_count.begin(), product_purchase_count.end());

    sort(products.begin(), products.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "Top 5 most purchased products:\n";
    for (size_t i = 0; i < 5 && i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].first << " - " << products[i].second << " purchases\n";
    }
    cout << "\n";
}
