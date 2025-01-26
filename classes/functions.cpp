/*
    General functions
*/
#include <iostream>
#include <string>
#include "category_manager.h"
#include "product_manager.h"
using namespace std;


//Getting the title from the user
string input_title(){
    string title;
    cout << "Enter product title: ";
    cin.ignore(1000, '\n');
    getline(cin, title);  //get title until \n
    return title;
}

//Getting the description from the user
string input_description(){
    string description;
    cout << "Enter product description: ";  //description
    getline(cin, description);  //get all input until \n
    return description;
}

//Getting the category name from the user
string input_category_name(CategoryManager& manager){
    string category_name;
    cout << "Enter one of the following categories: ";  //category
    manager.print_all_categories();
    getline(cin, category_name);
    while(manager.find_category(category_name) == -1){  //INPUT CHECK 1 - If category name doesnt exist
        cout << "Invalid category name. Please, select one of the following categories: ";
        manager.print_all_categories();
        getline(cin, category_name);
    }
    return category_name;
}


//Getting the subcategory from the user
string input_subcategory(CategoryManager& manager, string& category_name){
    string subcategory;
    cout << "Enter one of the following subcategories: ";
    manager.print_subcategories(category_name);  //prints all subcategories of the given category_name
    getline(cin, subcategory);
    while(manager.find_subcategory(category_name, subcategory) == -2){  //INPUT CHECK 2 - If subcategory doesnt exist
        cout << "Invalid subcategory name. Please, select one of the following subcategories of " << category_name << ": ";
        manager.print_subcategories(category_name);
        getline(cin, subcategory);
    }
    return subcategory;
}


//Getting the price from the user
float input_price(){
    float price;
    string for_price;
    string invalid_input;
    cout << "Enter product price: ";
    cin >> price;

    // Check for non-numeric input or negative values
    while(cin.fail() || price < 0){
        if(cin.fail()){
            cin.clear();  // Clear the error flag
            cin.ignore(1000, '\n');  // Discard invalid input
            cout << "Words not allowed." << endl;
        }
        else{
            cout << "Negative numbers not allowed." << endl;
        }
        cout << "Give product price: ";
        cin >> price;
    }
    cin.ignore(1000, '\n');
    return price;
}


//Getting the measurement type from the user [kg/unit]
string input_measurement_type(){
    string measurement_type;
    cout << "Give measurement type[Kg/Unit]: ";
    getline(cin, measurement_type);  //read the measurement type from the user
    while(measurement_type != "Kg" && measurement_type != "kg" && measurement_type != "Unit" && measurement_type != "unit"){  //INPUT CHECK 4 - Check if measurement type is [Kg|Unit]
        cout << "Invalid measurement type. Please enter Kg/kg or Unit/unit: ";
        getline(cin, measurement_type);  
    }
    return measurement_type;
}

int input_quantity(string& measurement_type){
    int quantity;
    cout << "Give amount of " << measurement_type << ": ";  //Give amount of kg/unit
    cin >> quantity; 
    while(quantity < 0 || cin.fail()){  //INPUT CHECK 5 - If quantity is negative
        if(quantity < 0){
            cout << "Negative quantity value not allowed." << endl;
        }
        else{
            cin.clear();  //clear the cin error flag (as for a non-numeric value the flag is set as TRUE) 
            cin.ignore(1000, '\n');  // Discard invalid input
            cout << "No words allowed." << endl;
        }
        cout << "Give amount of " << measurement_type << ": ";
        cin >> quantity;
    }
    cin.ignore(1000, '\n');
    return quantity;
}