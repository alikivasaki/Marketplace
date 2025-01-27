#include <unordered_map>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "user_manager.h"

using namespace std;

UserManager::UserManager(string filepath) {
    filename = filepath;
    load_users();
}

void UserManager::load_users() {
    ifstream file(filename);  
    if (!file.is_open()) {    
        cerr << "Failed to open user file: " << filename << endl;
        return;              
    }

    string line;
    while (getline(file, line)) {
        istringstream current_line(line);
        string username, password, is_admin;

        // Parse line by splitting using ',' as delimiter
        if (getline(current_line, username, ',') &&
            getline(current_line, password, ',') &&
            getline(current_line, is_admin, ',')) {

            // Convert is_admin from string to boolean
            bool isAdmin = (is_admin == "1");

            users[username] = make_tuple(password, isAdmin);
        }
    }

    file.close(); 
}

bool UserManager::find_user(const string& username) const {
    return users.find(username) != users.end();
}

bool UserManager::validate_user(const string& username, const string& password) const {
    auto it = users.find(username); 
    if (it != users.end()) {        
        const auto& stored_password = get<0>(it->second); 
        return stored_password == password;              
    }
    return false;
}

bool UserManager::is_admin(const string& username) const {
    auto it = users.find(username); 
    if (it != users.end()) {       
        return get<1>(it->second);  
    }
    return false; 
}

void UserManager::add_user(const string& username, const string& password, bool is_admin) {
    users[username] = make_tuple(password, is_admin);
}

void UserManager::save_users() const {
    ofstream file(filename); 
    if (!file.is_open()) {
        cerr << "Failed to open file '" << filename << "' for saving users." << endl;
        return;
    }

    for (const auto& user : users) {
        file << user.first << "," << get<0>(user.second) << "," << get<1>(user.second) << endl;
    }

    file.close();
}
