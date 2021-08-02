#include <vector>
#include <string>
#include <iostream>
#ifndef _MENU_HPP_
#define _MENU_HPP_
#include "raw_logic/Chef.hpp"
#include "raw_logic/Normal_User.hpp"
#include "raw_logic/UserModel.hpp"
#include "raw_logic/Shelf.hpp"
#include "raw_logic/outerior_functions.hpp"
#include "raw_logic/Supplier.hpp"
using namespace std;
class Menu
{
public:
    Menu();

    void direct_command(vector<string> &commands);

    void signup(vector<string> &commands);

    void login(vector<string> &commands,UserModel * current_user);

    void check_duplication(string &username, string email);

    void handle_signup(vector<string> &commands);

    int recipe_search(int pk);

    UserModel *user_search(string username, vector<string> &commands);

    void handle_rating(vector<string> &commands);

    void logout(UserModel * current_user);

    void rate(vector<string> &commads,UserModel * current_user);

    void de_allocate();

    void handle_recipe(vector<string> &commands,UserModel * current_user);

    void handle_recipe_deletion(vector<string> &commands,UserModel * current_user);

    void lexo_arrange();

    void check_command_format(vector<string> command_format, vector<string> commands);

    void handle_shelves(vector<string> &commands,UserModel * current_user);

    void get_users(vector<string> &commands,UserModel * current_user);

    void get_chefs(vector<string> &commands);

    void shelf_recipe_commands(vector<string> &commands,UserModel * current_user);

    int shelf_search(vector<string> &commands, bool check_premission,UserModel * current_user);

    void handle_filters(vector<string> &commands,UserModel * current_user);

    void general_recipe(vector<string> &commands,UserModel * current_user);

    vector<UserModel *> users;
    vector<Recipe *> recipes;
    vector<Offer *> offers;
    vector<Shelf *> shelves;
    vector<UserModel *> active_users;
private:
};
#endif