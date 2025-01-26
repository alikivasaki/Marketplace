/*
    The definition of the functions of the class Admin
*/
#include <iostream>
#include <string>
#include "user.h"
#include "admin.h"
#include "product.h"
#include "product_manager.h"
#include "product_history.h"
using namespace std;


////////////////////////////////////////////////////////////////////
//                     AUXILIARY METHODS
////////////////////////////////////////////////////////////////////

/*
    Methods for create_new_prod (Validation check included)
*/
string Admin::input_title(){
    string title;
    cout << "Enter product title: ";
    cin.ignore(1000, '\n');
    getline(cin, title);  //get title until \n
    return title;
}

string Admin::input_description(){
    string description;
    cout << "Enter product description: ";  //description
    getline(cin, description);  //get all input until \n
    return description;
}

string Admin::input_category_name(CategoryManager& manager){
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

string Admin::input_subcategory(CategoryManager& manager, string& category_name){
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

float Admin::input_price(){
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

string Admin::input_measurement_type(){
    string measurement_type;
    cout << "Give measurement type[Kg/Unit]: ";
    getline(cin, measurement_type);  //read the measurement type from the user
    while(measurement_type != "Kg" && measurement_type != "kg" && measurement_type != "Unit" && measurement_type != "unit"){  //INPUT CHECK 4 - Check if measurement type is [Kg|Unit]
        cout << "Invalid measurement type. Please enter Kg/kg or Unit/unit: ";
        getline(cin, measurement_type);  
    }
    return measurement_type;
}

int Admin::input_quantity(string& measurement_type){
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


////////////////////////////////////////////////////////////////////
//                        BASIC METHODS
///////////////////////////////////////////////////////////////////

//Constructor & Destructor
Admin::Admin(string name, string pass): User(name, pass){
    User::set_is_admin(true);
}

//Destructor
Admin::~Admin(){}


//1. Add a new product
void Admin::create_new_prod(CategoryManager& categ_manager, ProductManager& prod_manager){
    /*The CategoryManager and ProductManager must be initialized from main*/

    /*Nessesary definitions*/
    string title = input_title();  
    string description = input_description();
    string category_name = input_category_name(categ_manager);
    string subcategory = input_subcategory(categ_manager, category_name);
    float price = input_price();
    string measurement_type = input_measurement_type();  // kg or units
    int quantity = input_quantity(measurement_type);  //the available quantity of the product

    /*Creating and setting up the product*/
    Product prod(title, description, category_name, subcategory, price, measurement_type, quantity);    
    prod_manager.set_new_product(prod);
    cout << "\n";
}


//2. Edit product
void Admin::edit_prod(CategoryManager& categ_manager, ProductManager& prod_manager){
    /*Proper declarations*/
    float price;
    int quantity;
    bool status;  
    string title;  //the product title user want to edit
    string categ;  //temp category name (used for entering subcategory with a validation check)
    string input;
    string invalid_input;  
    int field;  //the field user want to edit


    cout << "Enter product title you wish to edit: ";
    cin.ignore();
    getline(cin, title); //works if product title is multiple words
    status = prod_manager.find_product(title);  //check whether the product exists
    if(status != 1){  //Product does NOT exist
        cout << "Product doesn't exist!" << endl << endl;
        return;
    }
    //Case it exists
    Product prod = prod_manager.get_product(title);
    cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing" << endl;
    cin >> field;  //reads the answer of the user (the field he wants to edit)
    switch (field){
        case 1:  //Edit the title
            cout << "Enter new title: ";
            cin.ignore(1000, '\n');
            getline(cin, input);  //read the title
            
            prod.set_title(input);  //sets the title into the product 
            cout << "Product updated!" << endl;
            break;
        
        case 2:   //Edit the description
            cout << "Enter new description: ";
            cin.ignore(1000, '\n');
            getline(cin, input);  //read the descr
            
            prod.set_description(input);   //sets new descr
            cout << "Product updated!" << endl;
            break;

        case 3:  //Edit the category and subcategory
            //Input of category
            cout << "Enter one of the following categories as new: ";
            categ_manager.print_all_categories();  //has an end of line at the end of all categories
            cin.ignore();
            getline(cin, input);  //read the line
            while(categ_manager.find_category(input) == -1){  //INPUT CHECK 1 - If category name doesnt exist
                cout << "Invalid category name. Please, select one of the following categories: ";
                categ_manager.print_all_categories();
                getline(cin, input);
            }
            
            prod.set_category_name(input);  //setting the new category name
            categ = input;  //saving the category name for the selection of categ's subcategories


            //Input of categ's subcategory
            cout << "Enter one of the following subcategories as new: ";
            categ_manager.print_subcategories(categ);  //prints all subcategories of the given category_name
            getline(cin, input);
            while(categ_manager.find_subcategory(categ, input) == -2){  //INPUT CHECK 2 - If subcategory doesnt exist
                cout << "Invalid subcategory name. Please, select one of the following subcategories of " << categ << ": ";
                categ_manager.print_subcategories(categ);
                getline(cin, input);
            }
            
            //Setting the categ's subcategory 
            prod.set_subcategory(input);  
            cout << "Product updated!" << endl; 
            break;

        case 4:   //Edit the price
            //Input 
            cin.ignore(1000, '\n');
            cout << "Enter a new price: ";
            cin >> price;

            // Check for non-numeric input or negative values
            while(cin.fail() || price < 0){
                if(cin.fail()){
                    cin.clear();  // Clear the error flag
                    cin.ignore(1000, '\n');  // Discard invalid input
                    cout << "Invalid input: Please enter a valid non-negative number." << endl;
                }
                else{
                    cout << "Only non-negative values for price allowed." << endl;
                }
                cout << "Enter a new price: ";
                cin >> price;
            }

            //Setting the price
            prod.set_price(price);
            cout << "Product Updated!" << endl;
            break;

        case 5:   //Edit the available quantity (doesn't matter in which measurement type)
            //Input 
            cin.ignore(1000, '\n');
            cout << "Enter a new quantity of " << prod.get_measurement_type() << " : ";
            cin >> quantity;
            while(cin.fail() || price < 0){
                if(cin.fail()){
                    cin.clear();  // Clear the error flag
                    cin.ignore(1000, '\n');  // Discard invalid input
                    cout << "Invalid input: Please enter a valid non-negative number." << endl;
                }
                else{
                    cout << "Only non-negative values for price allowed." << endl;
                }
                cout << "Enter a new price: ";
                cin >> quantity;
            }
            cin.ignore(1000, '\n');

            //Setting new available quantity
            prod.set_quantity(quantity);
            cout << "Product Updated!" << endl;
            break;
        default:
            cout << "Nothing changed." << endl;
            break;
    }
    prod_manager.remove_product(title);  //removes the old product from the map
    prod_manager.set_new_product(prod);  //sets the new product on the map
    cout << "\n";
}


//3. Remove product
void Admin::remove_prod(ProductManager& prod_manager){
    /*Necessary declarations*/
    bool status; 
    string title;

    /*Input*/
    cout << "Enter the product you wish to remove: ";
    cin.ignore();
    getline(cin, title); //works if product title is multiple words
    status = prod_manager.find_product(title);  //check whether the product exists
    if(status != 1){ //If DOESN'T exist
        cout << "Product doesn't exist!" << endl << endl;
        return;
    }    

    //Else (if it exists)
    prod_manager.remove_product(title);  //remove the product from the map
    cout << "Product removed!" << endl << endl;   
}




//5. Show Unavailable Products  
void Admin::show_unavailable_products(ProductManager& prod_manager){
    for(auto pair : prod_manager.get_allProducts_map()){  //for every element of prod_manager
        if(pair.second.get_quantity() == 0){  //If Product's quantity is 0 (unavailable)
            pair.second.print();  //print it
        }
    }
    cout << "\n";
}


//Admin Entire Menu
void Admin::admin_menu(CategoryManager& categ_manager, ProductManager& prod_manager){
    /* Variables Declaration */
    int choice;
    string answer;
    string invalid_input;

    /* Admin Menu (can be also build as method in Admin class) */
    cout << "---Admin Menu---" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Edit Product" << endl;
    cout << "3. Remove Product" << endl;
    cout << "4. Search Product" << endl;
    cout << "5. Show Unavailable Products" << endl;
    cout << "6. Show Top 5 Products" << endl;
    cout << "7. Exit" << endl;
    
    cout << "Enter your choice: ";
    cin >> choice;
    while(cin.fail()){  //Input check - If word was given
        cin.clear();
        getline(cin, invalid_input);
        cout << "Invalid choice: No words allowed. Please give again!" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    }
    
    /* Choices */
    while(choice != 7){
        if(choice == 1){  //1. Add Product
            create_new_prod(categ_manager, prod_manager); 
        }
        else if(choice == 2){  //2. Edit product (searching by title)
            edit_prod(categ_manager, prod_manager);
        }
        else if(choice == 3){  //3. Remove product 
            remove_prod(prod_manager);
        }  
        else if(choice == 4){   //4. Search Product
            search(prod_manager, categ_manager);
        }
        else if(choice == 5){  //5. Show unavailable products
            show_unavailable_products(prod_manager);
        }
        else if(choice == 6){  //6. Show Top 5 Products
            ProductHistory::show_top_products();
        }

        cout << "---Admin Menu---" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Edit Product" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. Search Product" << endl;
        cout << "5. Show Unavailable Products" << endl;
        cout << "6. Show Top 5 Products" << endl;
        cout << "7. Exit" << endl;
        
        cout << "Enter your choice: ";
        cin >> choice;
        while(cin.fail()){  //Input check - If word was given
            cin.clear();
            getline(cin, invalid_input);
            cout << "Invalid choice: No words allowed. Please give again!" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
        }
    }
    cout << "Goodbye!" << endl;
    prod_manager.save_products();
}

