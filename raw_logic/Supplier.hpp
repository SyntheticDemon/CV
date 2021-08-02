#include "main_header.hpp"
#include <vector>
#include <string>
#include "UserModel.hpp"
#include "Exception.hpp"
#include "../handlers.hpp"
#ifndef _SUPPLIER_HPP_
#define _SUPPLIER_HPP_

using namespace std;
class Request;
class Response;
class Supplier : public UserModel
{
public:
    Supplier(vector<string> &commands, int list_size);

    void delete_offer(string ingredient_name);

    void change_offer(vector<string> &commands);

    void see_recipes(vector<Recipe *> recipes);

    void long_recipe(vector<Recipe *> recipes, int pk);

    void rate(Recipe *&target_recipe, int score, vector<string> &commands);

    void add_recipe(vector<string> &commands, vector<Recipe *> &recepes);

    void my_recipes(vector<string> &commands);

    void delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes);

    bool print_user();

    bool print_chef();

    void print_chef_detailed();

    void create_shelf(Shelf *new_shelf);

    void delete_shelf_recipe();

    void get_shelves(int limit);

    void add_filter(Filter *new_filter);

    void delete_filters();

    string get_email() { return email; }

    void post_offer(vector<string> &commands, int size, vector<Offer *> &offers);

    void post_order(Recipe *target_recipe, vector<Offer *> &offers);

    void get_orders();

    Response *give_menu_response(Request *req, Menu *current_menu);

private:
    string email;
    vector<Offer *> offers;
};
#endif