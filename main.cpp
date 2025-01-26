#include <iostream>
#include <string>
#include "classes/customer.h"
#include "classes/product_manager.h"
#include "classes/admin.h"
#include "classes/user_manager.h"
#include "classes/category_manager.h"
#include "classes/order_history.h"
#include "classes/product_history.h"

using namespace std;

int main(int argc, char **argv) {
    //Check if every argument was passed from cmdline
    if(argc != 4){  //If not
        cout << "Usage: ./oop24 <categories file> <products file> <users file>" << endl;
        exit(1);  //terminates the program
    }

    //Load the managers with the filepaths given from cmdline
    CategoryManager cmanager(argv[1]);
    ProductManager pmanager(argv[2]);
    UserManager umanager(argv[3]);


    string log_reg, name, password;
    bool isAdmin;
    char answer;
    cout <<"Welcome to the e-shop!!!\n";
    cout << "Do you want to login or register? (enter option): ";
    cin >> log_reg;
    while (log_reg != "login" && log_reg != "register") {
        cout << "Invalid input. Please enter \"login\" or \"register\" \n";
        cin >> log_reg;
    }

    if (log_reg == "login") {
        cout << "Please enter your username: ";
        cin >> name;
        cout << "Please enter your password: ";
        cin >> password;
        while (!umanager.validate_user(name, password)){
            cout << "Wrong username or password\n";
            cout << "Please enter your username: ";
            cin >> name;
            cout << "Please enter your password: ";
            cin >> password;
        }
        cout << "\nWelcome " << name << "!\n\n";
        isAdmin = umanager.is_admin(name);

    } else if (log_reg == "register") {
        cout << "Please enter your username: ";
        cin >> name;
        while (umanager.find_user(name)) {
            cout << "User already exists.Please give different username\n";
            cout << "Please enter your username: ";
            cin >> name;
        }
        cout << "Please enter your password: ";
        cin >> password;
        
        cout << "Are you an admin user? (Y/N): ";
        cin >> answer;
        while (answer != 'y' && answer != 'n') {
            cout << "Invalid input. Please enter \'y\' or \'n\' \n";
            cout << "Are you an admin user? (Y/N): ";
            cin >> answer;
        }
        if (answer == 'n') {
            isAdmin = false;
            OrderHistory::create_history(name);
        } else {
            isAdmin = true;
        }
        umanager.add_user(name, password, isAdmin);
        umanager.save_users();
        cout << "Thanks for signing up! You are automatically logged-in as " << name << "\n\n";
    }

   ProductHistory::create_histrory ("files/product_history.txt");

    if (!isAdmin) {
        Customer customer(name, password);
        customer.menu(pmanager, cmanager);
    } else {
        Admin admin(name, password);
        admin.admin_menu(cmanager, pmanager);
    }

    
}

    
