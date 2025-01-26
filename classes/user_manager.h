#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class UserManager {
    private:
        unordered_map<string, tuple<string, bool>> users;
        string filename;
    public:
        UserManager(string filepath);
        void load_users();
        void add_user(const string& username, const string& password, bool is_admin);
        void save_users() const;

        bool find_user(const string& username) const;
        bool validate_user(const string& username, const string& password) const;
        bool is_admin(const string& username) const;
};

#endif