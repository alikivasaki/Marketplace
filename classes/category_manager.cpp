/*
    This file is for defining the operations of the CategoryManager
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "category_manager.h"
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                      AUXILIARY METHODS
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Replace " @ " with "@"
void CategoryManager::fix_line(string &line){
    /*REPLACEMENT 1*/
    string to_replace1 = "(";  //the thing which must be replaced 
    string replace_by1 = "@ ";

    //Find the first occurance of the "("
    size_t pos1 = line.find(to_replace1);
    while(pos1 != string::npos){
        //Replace " @ " with "@"
        line.replace(pos1, to_replace1.size(), replace_by1);
        pos1 = line.find(to_replace1, pos1 + replace_by1.size());  //find the next occurance after the previous occurance 
    }
    
    /*REPLACEMENT 2*/
    string to_replace2 = ")";  //the thing which must be replaced 
    string replace_by2 = "@";

    //Find the first occurance of the ")"
    size_t pos2 = line.find(to_replace2);
    while(pos2 != string::npos){
        //Replace " @ " with "@"
        line.replace(pos2, to_replace2.size(), replace_by2);
        pos2 = line.find(to_replace2, pos2 + replace_by2.size());  //find the next occurance after the previous occurance 
    }


    /*REPLACEMENT 2*/
    //Replace substring with char
    string to_replace3 = " @ ";  //the thing which must be replaced 
    string replace_by3 = "@";

    //Find the first occurance of the " @ "
    size_t pos3 = line.find(to_replace3);
    while(pos3 != string::npos){
        //Replace " @ " with "@"
        line.replace(pos3, to_replace3.size(), replace_by3);
        pos3 = line.find(to_replace3, pos3 + replace_by3.size());  //find the next occurance after the previous occurance 
    }
}



//////////////////////////////////////////////////////////////////////
//                      BASIC METHODS
////////////////////////////////////////////////////////////////////// 

//Constructor 
CategoryManager::CategoryManager(string filepath){
    set_all_vector(filepath);
}
CategoryManager::~CategoryManager(){}

/*
    SETTERS
*/
//Sets the vector from categories.txt (Initializer)
void CategoryManager::set_all_vector(string filepath){
    // ACCESSING THE FILE
    ifstream filecateg(filepath);
    if(filecateg.fail()){  //Check if opening was unsuccessful
        cout << "Unable to access the file(categories.txt)" << endl;
        exit(1);  //if categories.txt fails to open, the program will be TERMINATED
    }
    
    string line;  //the line that we take each time
    string word;  //the word we extract from the line each time
    int i;

    while(getline(filecateg, line)){  //Getting every line until EOF 
        Category categ;   //creates a Category
        i = 0;   //time counter used for the category/subcategory seperation (the first word only must be category)
        
        fix_line(line);  //Clears the current line from @ and ()

        istringstream current_line(line);  //creates a string stream for extracting the words of the current line (cleared from @ and ())
        
        while(getline(current_line, word, '@')){  //until the current_line is finished
            if(i == 0){  //if it is the first word
                categ.set_name(word);  //set it as name
            }
            else{
                categ.set_subcategory(word);   //else, set it as subcategory
            }
            i++;
        }
        set_category(categ);
    }

    filecateg.close();
}


//Add a new category on the vector
void CategoryManager::set_category(Category categ){
    allCategories.push_back(categ);
}


/*
    GETTERS
*/
// Get the size of the vector allCategories
int CategoryManager::get_size()const{
    return allCategories.size();  //we get the size of the allCategories
}

// Gets a specific category from allCategories
Category CategoryManager::get_category(int index)const{
    Category categ;
    categ.set_name("NULL");  //setting with fake string values in case index > allCategories.size
    categ.set_subcategory("NULL");
    if(index <= get_size()){   //if the index is in the range of the allCategories size
        categ = allCategories[index];
    }
    return categ;
}


/*
    PRINTERS
*/
//Display categories (prints new line at the end)
void CategoryManager::print_all_categories() {
    for(int i = 0; i < get_size(); i++) {   //for every element of allCategories
        Category categ = get_category(i); 
        categ.print_name();
    }
    cout << "\n";
}


//Print subcategories of a given Category obj's name
void CategoryManager::print_subcategories(string categ){
    Category temp;
    int index = find_category(categ); //check if exists, and if it does, get the index in allCategories
    if(index == -1){
        cout << "Category not found\n";
        return;
    }
    temp = get_category(index);  //take that category
    temp.print_subcategories();  //print its subcategories
}



/*
    FINDERS
*/

/*
    Find a specific category
    Returns index in allCategories it it exists,
    else returns -1
*/
int CategoryManager::find_category(string categ){
    Category temp;
    for(int i = 0; i < get_size(); i++){  //for every element of allCategories, until found
        temp = get_category(i);
        if(categ == temp.get_name()){
            return i;  //if it exists, return index
        }
    }
    return -1;  //if it doesnt exist, return code -1
}


/*
    Find a specific subcategory (given a category_name and a sub)
    Returns index in subcategories of the Category which name is category_name if it exists (else -1),
    else returns -2
*/
int CategoryManager::find_subcategory(string category_name, string sub){
    Category categ;
    int index = find_category(category_name);  //it is nessecary so we get the index
    if(index == -1){
        return -1;   //if category doesnt exist
    }
    categ = get_category(index);
    for(int i = 0; i < categ.get_size(); i++){
        if(categ.get_subcategory(i) == sub){  //for each element of categ.subcategories
            return i;  //if sub exists, return index
        }
    }
    return -2;  //if category exists, and subcategory doesnt, return -2
}