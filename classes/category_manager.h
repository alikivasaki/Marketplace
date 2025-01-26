/*
    This file is for declaring the class CategoryManager which manages every object of the class Category
*/
#ifndef CATEGORY_MANAGER_H
#define CATEGORY_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "category.h"
using namespace std;


class CategoryManager{
    private:
        //Variables
        vector <Category> allCategories;
        int size;

        //Auxiliary Methods
        void fix_line(string &line);
    public:
        /*CONSTRUCTOR AND DESTRUCTOR*/
        CategoryManager(string filepath);
        ~CategoryManager();
        
        /*SETTERS*/
        void set_all_vector(string filepath);  //initializer from file
        void set_category(Category categ);  //add a new category

        
        /*GETTERS*/
        Category get_category(int index = 0)const;  //returning a specific category of allCategories
        int get_size()const;   //get the size of allCategories

        
        /*PRINTERS*/
        void print_all_categories();
        void print_subcategories(string categ);  //print subcategories of given a category name

        
        /*FINDERS*/
        int find_category(string categ);  //given a category name, check if exists in allCategories
        int find_subcategory(string category_name, string sub);  //given a category name and a subcategory, chech if sub exists in allCategories

};

#endif

