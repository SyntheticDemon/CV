#include "outerior_functions.hpp"
#include <vector>
#include <string>
#include "UserModel.hpp"
#include "Chef.hpp"
#include "Normal_User.hpp"
#include "Recipe.hpp"
#ifndef _SHELF_HPP_
#define _SHELF_HPP_
class Recipe;
class Shelf
{
public:
    void print_inside();

    Shelf(vector<string> &commands, int id, UserModel *owner);

    int get_id() { return id; }

    string get_shelf_name() { return shelf_name; }

    void delete_recipe(vector<string> &commands, int id);

    void add_recipe(Recipe *to_be_added);

    UserModel *owner;
    vector<Recipe *> get_recipes() { return recipes; }

private:
    int id;

    string shelf_name;

    vector<Recipe *> recipes;
};
#endif