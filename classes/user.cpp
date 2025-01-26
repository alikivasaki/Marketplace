/*
    The definitions of the functions of class User
*/
#include <iostream>
#include <string>
#include "user.h"
using namespace std;


//CONSTRUCTORS AND DESTRUCTOR
//With parameters
User::User(string username, string password){
    this->username = username;  
    this->password = password;
}

//Destructor
User::~User(){}

//Without parameters but with default values
User::User(){
    this->username = "None";
    this->password = "None";
}


//SETTERS
//Username
void User::set_username(string username){
    this->username = username;
}

//Password
void User::set_password(string password){
    this->password = password;
}

//Is admin status
void User::set_is_admin(bool status){
    this->is_admin = status;
}


//GETTERS
//Username
string User::get_username() const{
    return username;
}

//Password
string User::get_password() const{
    return password;
}

//Is_admin status
bool User::get_is_admin() const{
    return is_admin;
}

void User::search(ProductManager& pmanager, CategoryManager& cmanager) const {
    int num_choice;
    string prod, categ, subcateg, option;
    cout << "\n";
    cout << "Product Search Options:\n";
    cout << "1. Search for a specific product (by title).\n";
    cout << "2. View the products of a specific category.\n";
    cout << "3. Show all the available products.\n";
    cin >> num_choice;

    while ((num_choice != 1 && num_choice !=2 && num_choice !=3) || cin.fail()) {
        if(cin.fail()){
            cout << "No words allowed. Please give an numeric choice." << endl;
        }else{
            cout << "Option does not exist. Please select again\n";
        }
        cin.clear();  //clear the cin error flag (as for a non-numeric value the flag is set as TRUE) 
        cin.ignore(1000, '\n');  // Discard invalid input
        cout << "Enter your choice: ";
        cin >> num_choice;
    }

    switch (num_choice) {
        case 1:
            cout << "Select a product title: ";
            cin.ignore();
            getline(cin, prod); //works for more that one word
            while (!pmanager.find_product(prod)) {
                cout << "Product does not exist. Please enter a different product ";
                getline(cin, prod);
            }
            pmanager.get_product(prod).print(); 
            break;

        case 2:
            cout << "Search by category or subcategory? ";
            cin >> option;
            while (option != "category" && option != "subcategory") {
                cout << "Please enter category or subcategory: ";
                cin >> option;
            }
            cout << "Select one of the following categories: ";
            cmanager.print_all_categories();
            cin.ignore();
            getline(cin, categ);
            while (cmanager.find_category(categ) == -1) {
                cout << "Category does not exist. Please select one of the following categories:";
                cmanager.print_all_categories();
                getline(cin, categ);
            }

            if (option == "category") {
                pmanager.print_by_category(categ); 
                cout << "Select a product title: ";
                getline(cin, prod);
                while (!pmanager.find_product(prod, categ)) { 
                    cout << "Product does not exist. Please select one of the following products:\n";
                    pmanager.print_by_category(categ);
                    getline(cin, prod);
                }
                pmanager.get_product(prod).print(); 
            } else {

                cout << "Select one of the following subcategories: ";
                cmanager.print_subcategories(categ);
                getline(cin, subcateg);
                while (cmanager.find_subcategory(categ, subcateg) == -2) {
                    cout << "Subcategory does not exist. Please select one of the following subcategories:";
                    cmanager.print_subcategories(categ);
                    getline(cin, subcateg);
                }

                pmanager.print_by_category_and_subcategory(categ, subcateg); 
                cout << "Select a product title: ";
                getline(cin, prod);
                while (!pmanager.find_product(prod, categ, subcateg)) { 
                    cout << "Product does not exist. Please select one of the following products:\n";
                    pmanager.print_by_category_and_subcategory(categ, subcateg);
                    getline(cin, prod);
                }
                pmanager.get_product(prod).print();
            }
            break;

        case 3:
            pmanager.print_available();
            cout << "Select a product title: ";
            cin.ignore();
            getline(cin, prod);
            while (!pmanager.find_product(prod)) {
                cout << "Product does not exist. Please enter a different product ";
                getline(cin, prod);
            }
            pmanager.get_product(prod).print(); 
            break;
    }
}
