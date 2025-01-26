/*
    General functions
*/
#include <iostream>
#include <string>
#include "category_manager.h"
#include "product_manager.h"
using namespace std;

string input_title();
string input_description();
string input_category_name(CategoryManager& categ_manager);
string input_subcategory(CategoryManager& categ_manager, const string& category_name);
float input_price();
string input_measurement_type();
int input_quantity(const string& measurement_type);