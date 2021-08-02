#include <vector>
#include <iostream>
#include <string>
#include "UserModel.hpp"
#ifndef _NORMAL_USER_HPP_
#define _NORMAL_USER_HPP_
#include "Recipe.hpp"
#include "Filters.hpp"
#include "Offer.hpp"
#include "Order.hpp"
class Recipe;
class Shelf;
class Order;
using namespace std;
class Nuser : public UserModel
{
public:
    Nuser(vector<string> &commands, int user_size);

    void see_recipes(vector<Recipe *> recipes);

    void rate(Recipe *&target_recipe, int score, vector<string> &commands);

    void add_recipe(vector<string> &commands, vector<Recipe *> &recepes);

    void long_recipe(vector<Recipe *> recipes, int pk);

    void my_recipes(vector<string> &commands);

    void delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes);

    void print_chef_detailed();

    void create_shelf(Shelf *new_shelf);

    void delete_shelf_recipe();

    bool print_user();

    bool print_chef();

    void get_shelves(int limit);

    void add_filter(Filter *new_filter);

    void delete_filters();

    void post_offer(vector<string> &commands, int size, vector<Offer *> &offers);

    void change_offer(vector<string> &commands);

    void delete_offer(string ingredient_name);

    void post_order(Recipe *target_recipe, vector<Offer *> &offers);

    void get_orders();

    Response * give_menu_response(Request * req,Menu * menu);

private:
    vector<Shelf *> shelves;
    vector<Order *> orders;
    vector<Filter *> filters;
};
#endif