#include <vector>
#include <string>
#include <iostream>
#ifndef _MENU_HPP_
#define _MENU_HPP_
#include "Chef.hpp"
#include "Normal_User.hpp"
#include "UserModel.hpp"
#include "Shelf.hpp"
#include "outerior_functions.hpp"
#include "Supplier.hpp"
using namespace std;
class Menu
{
public:
    Menu();

    void handle_offer(vector<string> &commands);

    void direct_command(vector<string> &commands);

    void handle_orders(vector<string> &commands);

    void signup(vector<string> &commands);

    void login(vector<string> &commands);

    void check_duplication(string &username,string email,bool supplier);

    void handle_signup(vector<string> &commands);

    int recipe_search(int pk);

    UserModel *user_search(string username, vector<string> &commands);

    void handle_rating(vector<string> &commands);

    void logout();

    Supplier *supplier_search(string email, vector<string> &commands);

    void validate_command(vector<string> &commands);

    void handle_credits(vector<string> &commands);

    void rate(vector<string> &commads);

    void de_allocate();

    void handle_recipe(vector<string> &commands);

    void handle_recipe_deletion(vector<string> &commands);

    void lexo_arrange();

    void check_command_format(vector<string> command_format, vector<string> commands);

    void handle_shelves(vector<string> &commands);

    void get_users(vector<string> &commands);

    void get_chefs(vector<string> &commands);

    void shelf_recipe_commands(vector<string> &commands);

    int shelf_search(vector<string> &commands, bool check_premission);

    void handle_filters(vector<string> &commands);

    void general_recipe(vector<string> &commands);

    void supplier_login(vector<string> &commands);

    void supplier_signup(vector<string> &commands);

private:
    vector<UserModel *> users;
    vector<Recipe *> recipes;
    vector<Supplier *> suppliers;
    vector<Offer *> offers;
    vector<Shelf *> shelves;
    UserModel *current_user;
};
#endif