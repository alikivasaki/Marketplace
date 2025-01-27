#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "product.h"
#include "product_manager.h"
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////
//                      AUXILIARY METHODS
/////////////////////////////////////////////////////////////////////////////////////
//Replace " @ " with "@"
void ProductManager::fix_line_from_unwanted_spaces(string &line){
    //Replace substring with char
    string to_replace = " @ ";  //the thing which must be replaced 
    string replace_by = "@";

    //Find the first occurance of the " @ "
    size_t pos = line.find(to_replace);
    while(pos != string::npos){
        //Replace " @ " with "@"
        line.replace(pos, to_replace.size(), replace_by);
        pos = line.find(to_replace, pos + replace_by.size());  //find the next occurance after the previous occurance 
    }
}


//////////////////////////////////////////////////////////////////////
//                      BASIC METHODS
//////////////////////////////////////////////////////////////////////

/* Constructor and destructor */
//Constructor
ProductManager::ProductManager(string filepath){
    set_all_products(filepath);
}

//Destructor
ProductManager::~ProductManager(){}


/* Setters */
//Initializer from the file
void ProductManager::set_all_products(string filepath){
    /*Necessary declarations*/
    string line;
    string title, descr, categ, sub, measurement_type, for_price, for_quantity;  //elements of prod
    float price;   //elements of prod
    int quantity;  //elements of prod
   
    /*File opening*/
    ifstream fileprod(filepath);  //opens the products.txt
    if(fileprod.fail()){  //If products.txt did not open
        cout << "Unable to access the file(product.txt)" << endl;
        exit(1); //terminates the program
    }

    /*File reading*/
    while(getline(fileprod, line)){  
        fix_line_from_unwanted_spaces(line);
        istringstream allElements(line);
        
        //Get the elements using @ as delimeter
        getline(allElements, title, '@');  
        getline(allElements, descr, '@'); 
        getline(allElements, categ, '@');  
        getline(allElements, sub, '@');  
        getline(allElements, for_price, '@');
        getline(allElements, measurement_type, '@');
        getline(allElements, for_quantity, '@');

        //Convert for_price and for_quantity into float and int
        price = stof(for_price);  //into float
        quantity = stoi(for_quantity);  //into integer

        Product prod(title, descr, categ, sub, price, measurement_type, quantity); //create the prod

        allProducts[title] = prod;  //inserting the product into the hashmap
    }
}


//Inserts new product on the map
void ProductManager::set_new_product(const Product & prod){
    allProducts[prod.get_title()] = prod;  //key = title and value = prod
}



/*Getters*/
Product ProductManager::get_product(const string& title){
    return allProducts[title];  //return the product with this title
}

const unordered_map <string, Product>& ProductManager::get_allProducts_map()const{
    return allProducts;
}

Product& ProductManager::get_product_ref(const string& title) {
    return allProducts.at(title); //return a reference
}

/*Finders*/
bool ProductManager::find_product(const string &title){
    if(allProducts.find(title) == allProducts.end()){  //Case it has reached end and not found
        return false;
    }
    return true;
}

//Check whether a product exists on a specific category (includes an exist check for title and categ)
bool ProductManager::find_product(const string &title, const string &categ){
    if(find_product(title) == 1 && get_product(title).get_category_name() == categ){
        return true;
    }
    return false;
}

//Check whether a product exists on category's subcategory (includes an exist check for title, categ and sub)
bool ProductManager::find_product(const string& title, const string& categ, const string& sub){
    if(find_product(title, categ) == 1 && get_product(title).get_subcategory() == sub){
        return true;
    }
    return false;
}

/*Remove product*/
void ProductManager::remove_product(const string& title){
    allProducts.erase(title);
}



/*Printers*/
//Print product by title (checks inside if it exists or not, so just use it directly)
void ProductManager::print_by_title(const string& title){
    bool is_exist = find_product(title);  //Check whether the product exists
    if(is_exist == 0){  //If it does NOT exist
        cout << "Product does not exist!" << endl;
        return;
    }    

    get_product(title).print();  //If it exists, get it and print it
}


//Print product by category only  (ASSUME CATEGORY EXISTS - DOESNT include a validation)
void ProductManager::print_by_category(const string& categ){
    cout << "Results:";
    for(auto pair: get_allProducts_map()){
        if(pair.second.get_category_name() == categ){
            cout << " \"" << pair.second.get_title() << "\"";
        }
    }
    cout << endl;
}


//Print product by category AND subcategory  (ASSUME CATEGORY AND SUB EXIST - DOESNT include a validation)
void ProductManager::print_by_category_and_subcategory(const string& categ, const string& sub){
    cout << "Results: ";
    for(auto pair: get_allProducts_map()){
        if(pair.second.get_category_name() == categ && pair.second.get_subcategory() == sub){
            cout << " \"" << pair.second.get_title() << "\"";   //print the title of the product
        }
    }
    cout << endl;
}


//Print all available products
void ProductManager::print_available(){
    cout << "Results: ";
    for(auto pair: get_allProducts_map()){
        if(pair.second.get_quantity() != 0){  //If quantity != 0
            cout << " \"" << pair.second.get_title() << "\"";  //print the title of the product
        }
    }
    cout << endl;
}


//Print all
void ProductManager::print_all(){
    for(auto pair: allProducts){  //for every item on the allProducts
        pair.second.print();
        cout << "-----------------------------------------" << endl;
    }
}


/* Save data to products.txt */
void ProductManager::save_products(){
    ofstream tofile("files/products.txt");  //open products.txt
    if(tofile.fail()){  //file didn't open
        cerr << "Unable to save products.txt" << endl;
        exit(1);
    }
    //For every element on the map
    for(auto pair: get_allProducts_map()){
        tofile << pair.second.get_title() << " @ ";
        tofile << pair.second.get_description() << " @ ";
        tofile << pair.second.get_category_name() << " @ ";
        tofile << pair.second.get_subcategory() << " @ ";
        tofile << pair.second.get_price() << " @ ";
        tofile << pair.second.get_measurement_type() << " @ ";
        tofile << pair.second.get_quantity() << endl;
    }

    tofile.close();
}
