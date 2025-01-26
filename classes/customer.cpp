#include <iostream>
#include <string>
#include "user.h"
#include "customer.h"
#include "cart.h"
#include "product.h"
#include "order_history.h"
#include "product_history.h"

using namespace std;

Customer::Customer(string name, string pass): User(name, pass){
     cart = new Cart();
     order_history = new OrderHistory(name);
}

Customer::~Customer() {
    delete cart;
    delete order_history;
}

//call cart through customer
void Customer::add_to_cart(Product& product, int quantity) {
    cart->add_product(product, quantity);
}

void Customer::update_cart(Product& product, int new_quantity) {
    cart->update_quantity(product, new_quantity);
}

void Customer::remove_from_cart(string product_title) {
    cart->remove_product(product_title);
}

void Customer::print_cart() const {
    cart->print_cart();
}

//complete order
void Customer::checkout() {
    const auto& items = cart->get_items();
    if (items.empty()) {
        cout << "Your cart is empty. Add products before checking out.\n\n";
        return;
    }

    for (auto& item : items) {
        Product& product = *(item.first);
        int current_quantity = product.get_quantity();
        product.set_quantity(current_quantity - item.second);
        ProductHistory::update_purchase_count(product.get_title());

    }

    order_history->add_order(*cart);
    cart->clear_cart();

    cout << "Order Completed!\n\n";


}

void Customer::print_order_history() const {
    order_history->print_history();
}

void Customer::menu(ProductManager& pmanager, CategoryManager& cmanager) {
    Product p;
    
    bool flag = true;
    string invalid_input;

    while (flag) {
        int num_choice;
        string categ, subcateg, prod;
        cout << "---Customer Menu---\n";
        cout << "1. Search for a product\n";
        cout << "2. Add product to cart\n";
        cout << "3. Update product from cart\n";
        cout << "4. Remove product from cart\n";
        cout << "5. Complete order\n";
        cout << "6. View order history\n";
        cout << "7. View cart\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> num_choice;
        while(cin.fail()){
            cout << "No words allowed. Please give an numeric choice." << endl;
            cout << "Enter your choice: ";
            cin.clear();  //clear the cin error flag (as for a non-numeric value the flag is set as TRUE) 
            cin.ignore(1000, '\n');  // Discard invalid input
            cin >> num_choice;
        }

        switch (num_choice) {
            case 1:
                search(pmanager, cmanager);
                break;

            case 2:
                cout << "Which product do you want to add? ";
                cin.ignore();
                getline(cin, prod); //works if product title is multiple words
                while (!pmanager.find_product(prod)) {
                    cout << "Product does not exist. Please enter a different product ";
                    getline(cin, prod);
                }
                cout << "Enter quantity: ";
                cin >> num_choice;
                while(cin.fail() || num_choice <= 0){
                    if (cin.fail()) { //checks input wasnt an interger
                        cout << "No words allowed. Please give an numeric choice." << endl;
                        cout << "Enter your quantity: ";
                        cin.clear();  //clear the cin error flag (as for a non-numeric value the flag is set as TRUE) 
                        cin.ignore(1000, '\n');  // Discard invalid input
                        cin >> num_choice;
                    }else {
                        cout << "Please give a positive number ";
                        cin >> num_choice;
                    }
                }

                add_to_cart(pmanager.get_product_ref(prod), num_choice);
                cout << "\n";
                break;

            case 3:
                cout << "Which product do you want to update? ";
                cin.ignore();
                getline(cin, prod); //works if product title is multiple words
                while (!pmanager.find_product(prod)) {
                    cout << "Product does not exist. Please enter a different product ";
                    getline(cin, prod);
                }
                cout << "Enter new quantity: ";
                cin >> num_choice;
                while(cin.fail() || num_choice <= 0){
                    if (cin.fail()) { //checks input wasnt an interger
                        cout << "No words allowed. Please give an numeric choice." << endl;
                        cout << "Enter new quantity: ";
                        cin.clear();  //clear the cin error flag (as for a non-numeric value the flag is set as TRUE) 
                        cin.ignore(1000, '\n');  // Discard invalid input
                        cin >> num_choice;
                    }else {
                        cout << "Please give a positive number ";
                        cin >> num_choice;
                    }
                }
                update_cart(pmanager.get_product_ref(prod), num_choice);
                cout << "\n";
                break;

            case 4:
                cout << "Which product do you want to remove from your cart? ";
                cin.ignore();
                getline(cin, prod);
                remove_from_cart(prod);
                cout << "\n";
                break;

            case 5:
                checkout();
                break;

            case 6:
                print_order_history();
                break;

            case 7:
                cout << "\n";
                print_cart();
                break;

            case 8:
                cout << "Goodbye!\n";
                order_history->save_history();
                pmanager.save_products();
                ProductHistory::save_product_history("files/product_history.txt"); //update how many times a product has been bought
                flag = false;
                break;
            
            default:
                cout << "Option does not exist.\n\n";
        }
    }
}


