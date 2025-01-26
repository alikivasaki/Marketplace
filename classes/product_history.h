#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem> 

using namespace std;

class ProductHistory {
private:
    static unordered_map<string, int> product_purchase_count;

public:
    static void load_user_histories(const string& directory_path);
    static void save_product_history(const string& filename);
    static void update_purchase_count(const string& product_name);
    static void create_histrory(const string& filename);
    static void show_top_products();
};
