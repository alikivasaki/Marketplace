/*
    An outline of the super-class User (declaration)
*/
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "product_manager.h"
#include "category_manager.h"
using namespace std;


class User{
    private:
        string username;
        string password;
        bool is_admin;

    protected:
        //Constructors
        User(string username, string password);  //with parameters
        User();  //without parameters (but with default values)  
        ~User();  //destructor
        
        //Setters/editors
        void set_username(string username);   //set/edit username
        void set_password(string password);   //set/edit password
        void set_is_admin(bool status);     //set the is_admin status (TRUE if Admin, FALSE if Customer)

        //Getters
        string get_username()const;  //gets username
        string get_password()const;  //gets password
        bool get_is_admin()const;
        
        void search(ProductManager& pmanager, CategoryManager& cmanager)const;

};

#endif