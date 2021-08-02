#include <vector>
#include <string>
using namespace std;
#include "Supplier.hpp"
#include "Exception.hpp"
#include "Shelf.hpp"
#include "Filters.hpp"
#include "Offer.hpp"
#include "main_header.hpp"
#define EMAIL_POSITION 6
#define NEW_COUNT_POS 8
#define NEW_PRICE_POS 6
void Supplier::delete_offer(string ingredient_name)
{
    for (int i = 0; i < offers.size(); i++)
    {
        if (offers[i]->get_ingredient_name() == ingredient_name)
        {
            offers.erase(offers.begin() + i);
            cout << "OK" << endl;
            return;
        }
    }
    throw(Exception(BAD_REQUEST));
}
void Supplier::get_orders(){
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::change_offer(vector<string> &commands)
{
    for (int i = 0; i < offers.size(); i++)
    {
        if (offers[i]->get_ingredient_name() == commands[2])
        {
            offers[i]->set_count(stoi(commands[NEW_COUNT_POS]));
            offers[i]->set_price(stoi(commands[NEW_PRICE_POS]));
            cout << "OK" << endl;
            return;
        }
    }
    throw(Exception(BAD_REQUEST));
}
void Supplier ::post_order(Recipe *target_recipe, vector<Offer *> &offers)
{
    throw(Exception(PERMISSION_DENIED));
}
Response * Supplier::give_menu_response(Request * req,Menu * menu){
    
}

void Supplier::post_offer(vector<string> &commands, int size, vector<Offer *> &offers)
{
    Offer *new_offer = new Offer(commands, size, this);
    this->offers.push_back(new_offer);
    offers.push_back(new_offer);
    cout << "OK" << endl;
}
void Supplier::my_recipes(vector<string> &commands)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes)
{
    throw(Exception(PERMISSION_DENIED));
}
Supplier ::Supplier(vector<string> &commands, int list_size) : UserModel(commands[USERNAME_POSITION], commands[PASSWORD_POSITION + 2], list_size)
{
    email = commands[EMAIL_POSITION];
}
void Supplier::add_filter(Filter *new_filter)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::add_recipe(vector<string> &commands, vector<Recipe *> &recepes)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::create_shelf(Shelf *new_shelf)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::see_recipes(vector<Recipe *> recipes)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::get_shelves(int limit)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::rate(Recipe *&target_recipe, int score, vector<string> &commands)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::delete_shelf_recipe()
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::long_recipe(vector<Recipe *> recipes, int pk)
{
    throw(Exception(PERMISSION_DENIED));
}
void Supplier::delete_filters()
{
    if (logged_in == true)
        throw(Exception(PERMISSION_DENIED));
}
bool Supplier::print_chef()
{
    return false;
}
bool Supplier::print_user()
{
    return false;
}
void Supplier::print_chef_detailed()
{
    throw(Exception(PERMISSION_DENIED));
}