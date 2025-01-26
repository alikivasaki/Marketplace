/*
    This headerfile is for declaring the class Category
    Note: In the get_subcategories, it will return all the vector as a string
*/
#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Category{
    private:
        string name;
        vector <string> subcategories;
        int size;  //the size of subcategories
    
    public:
        //Constructors and Destructor
        Category(string name, vector <string> sub);  
        Category();
        ~Category();  //destructor
 
        //Setters
        void set_name(string name);  // setting the name of the category object
        void set_subcategory(string sub);  //setting a new subcategory
        void set_subcategories(vector <string> sub);
        
        //Getters
        string get_name()const;
        vector <string> get_subcategories()const;  //getting all subcategories  
        string get_subcategory(int index);  //getting a specific subcategory
        int get_size()const;  //get the size of subcategories

        //Printers
        void print_name();  // prints the name of the category
        void print_subcategories();  //prints the subcategories
        void print_all();  //prints all 
};

#endif