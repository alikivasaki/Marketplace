/*
    This file is for defining the functions of the class Category
*/
#include <iostream>
#include <string>
#include <vector>
#include "category.h"
using namespace std;


/*
    Constructors and Destructor
*/
//With parameters (direct initialization)
Category::Category(string name, vector <string> sub){
    this->name = name;
    subcategories = sub;    
}

//Without parameters (will use setters later)
Category::Category(){}

//Destructor
Category::~Category(){}


/*
    Setters
*/
// Setting the name
void Category::set_name(string name){
    this->name = name;
}

// Setting a new subcategory
void Category::set_subcategory(string sub){
    subcategories.push_back(sub);
}

//Setting the all subcategories
void Category::set_subcategories(vector <string> sub){
    subcategories = sub;
}



/*
    Getters
*/
//For name
string Category::get_name()const{
    return name;
}

//For all the subcategories
vector <string> Category::get_subcategories()const{
    return subcategories;
}

//For a specific subcategory
string Category::get_subcategory(int index){
    if(index <= get_size()){
        return subcategories[index];
    }
    return 0;
}

//For the size of the subcategories
int Category::get_size()const{
    return subcategories.size();
}



/*
    Printers
*/
// Print the name of the Category
void Category::print_name(){
    cout << get_name() << " ";
}

// Print subcategories
// void Category::print_subcategories(){
//     cout << "Subcategories: ";
//     for(int i = 0; i < get_size(); i++){  //for the range of subcategories
//         cout << get_subcategory(i);  //print every element of subcategories
//         if(i != get_size() - 1){  //if last, dont print @
//             cout << " @ ";
//         }
//     }
//     cout << endl;
// }

//Print category's subcategories
void Category::print_subcategories(){
    for(int i = 0; i < get_size(); i++){  //for every single element of subcategories (vector)
        cout << get_subcategory(i) << " ";
    }
    cout << endl;
}


// Print all
void Category::print_all(){
    cout << "Category: " << get_name() << endl;  //not the same printed format with print_name()
    print_subcategories();
}
