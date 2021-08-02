#include <vector>
#include <iostream>
#include <string>
class Shelf;
#ifndef _USER_MODEL_HPP_
#define _USER_MODEL_HPP_
#include "Recipe.hpp"
#include "Filters.hpp"
#include "Offer.hpp"
using namespace std;
class Recipe;
class Response;
class Request;
class Menu;
class UserModel
{
public:
    string get_username();

    string get_password();

    bool get_logged_in();

    void user_logout();

    void user_login(bool value);

    int get_id() { return primary_key; }

    int get_credits() { return credits; }
    UserModel(string name, string password, int user_size);

    void set_privilage(bool value);

    virtual void see_recipes(vector<Recipe *> recipes) = 0;

    virtual void update_credits(int new_credit) { credits = new_credit; }

    virtual void long_recipe(vector<Recipe *> recipes, int pk) = 0;

    virtual void rate(Recipe *&target_recipe, int score, vector<string> &commands) = 0;

    virtual void add_recipe(vector<string> &commands, vector<Recipe *> &recepes) = 0;

    virtual void my_recipes(vector<string> &commands) = 0;

    virtual void delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes) = 0;

    virtual bool print_user() = 0;

    virtual bool print_chef() = 0;

    virtual void print_chef_detailed() = 0;

    virtual void create_shelf(Shelf *new_shelf) = 0;

    virtual void delete_shelf_recipe() = 0;

    virtual void get_shelves(int limit) = 0;

    virtual void add_filter(Filter *new_filter) = 0;

    virtual void delete_filters() = 0;

    virtual void post_offer(vector<string> &commands, int size, vector<Offer *> &offers) = 0;

    virtual void change_offer(vector<string> &commands) = 0;

    virtual void delete_offer(string ingredient_name) = 0;

    virtual void post_order(Recipe *target_recipe, vector<Offer *> &offers) = 0;

    virtual void get_orders() = 0;

    virtual Response *give_menu_response(Request *req, Menu *current_menu) = 0;

protected:
    int credits;
    bool logged_in;
    int primary_key;
    string username;
    string password;
};
#endif