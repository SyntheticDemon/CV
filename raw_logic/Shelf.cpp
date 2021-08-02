#include "Shelf.hpp"
#include "main_header.hpp"
#include "Exception.hpp"
#include <vector>
#include <algorithm>
using namespace std;
Shelf::Shelf(vector<string> &commands, int id, UserModel *owner)
{
    this->id = id;
    this->shelf_name = commands[commands.size() - 1];
    this->owner = owner;
}
void Shelf::add_recipe(Recipe *to_be_added)
{
    recipes.push_back(to_be_added);
}

bool lexographic_recipe_name(Recipe *const first, Recipe *const second) { return first->get_recipe_name() <= second->get_recipe_name(); }

void Shelf ::print_inside()
{
    sort(recipes.begin(), recipes.end(), &lexographic_recipe_name);
    if (recipes.size() == 0)
    {
        throw(Exception(EMPTY));
    }
    for (int i = 0; i < recipes.size(); i++)
    {
        recipes[i]->print_short(false);
    }
}
void Shelf::delete_recipe(vector<string> &commands, int id)
{
    for (int i = 0; i < recipes.size(); i++)
    {
        if (recipes[i]->get_id() == id)
        {
            recipes.erase(recipes.begin() + i);
            cout << "OK" << endl;
            return;
        }
    }
    throw(Exception(BAD_REQUEST));
}
