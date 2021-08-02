#include "Normal_User.hpp"
#include "UserModel.hpp"
#include "main_header.hpp"
#include "Recipe.hpp"
#include "Chef.hpp"
#include "Exception.hpp"
#include "Shelf.hpp"
#include "Offer.hpp"
#include "Order.hpp"
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include "../handlers.hpp"
class Request;
class Response;
Nuser::Nuser(vector<string> &commands, int user_size) : UserModel(commands[USERNAME_POSITION], commands[PASSWORD_POSITION], user_size)
{
}
void Nuser::post_offer(vector<string> &commands, int size, vector<Offer *> &offers)
{
    throw(Exception(PERMISSION_DENIED));
}
void Nuser::delete_offer(string ingredient_name)
{
    throw(Exception(PERMISSION_DENIED));
}
void Nuser::change_offer(vector<string> &commands)
{
    throw(Exception(PERMISSION_DENIED));
}
void Nuser::see_recipes(vector<Recipe *> recipes)
{

    int t = 0;
    for (int i = 0; i < recipes.size(); i++)
    {
        ;
        bool filter_application = true;
        for (int j = 0; j < filters.size(); j++)
        {
            if (filters[j]->check_provision(recipes[i]) == false)
            {
                filter_application = false;
            }
        }
        if (filter_application)
        {
            if (recipes[i]->get_deleted() == false)
            {
                recipes[i]->print_short(false);
                t++;
            }
        }
    }
    if (t == 0)
    {
        throw(Exception(EMPTY));
    }
}
Response *Nuser::give_menu_response(Request *req, Menu *menu)
{
    string body;
    string sid = req->getQueryParam("sid");
    Response *res = new Response();
    vector<string> command;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body>";
    body += "<div style='float:right;'>";
    body += "<a style='margin-left: 15px;' href='/shelves";
    body += "?sid=" + username + "'>";
    body += "shelves</a>";
    body += "<a style='margin-left: 15px;' href='/logout?sid=" + username;
    body += "'>logout</a>";
    body += "<a style='margin-left: 15px;' href='/recipes'>recipes</a></div>";
    body += "<h1 style='text-align: center; margin-left:600px; width:400px;text-align:center; border-radius: 10px;background-color:gray; border-color: gray; border-style: double;'>Chef Recipes </h1>";
    for (int i = 0; i < menu->recipes.size(); i++)
    {
        body += "<div style='text-align: center; margin-left:600px; height:75px; width:400px;; border-radius: 10px;background-color:silver; border-color: gray; border-style: double;'>";
        body += "<a href='/recipes_detailed";
        body += "?id=";
        body += to_string(menu->recipes[i]->get_id());
        body += "&sid=";
        body += sid;
        body += "'>";
        body += menu->recipes[i]->get_recipe_name();
        body += "<br>";
        body += menu->recipes[i]->get_id();
        body += "<br>";
        body += "Vegetarian :";
        body += menu->recipes[i]->get_vegetarian();
        body += "<br>";
        body += "Preperation Time :";
        body += menu->recipes[i]->get_time();
        body += "</a>";
        body += "</div>";
    }
    body += "</body>";
    body += "</html>";
    res->setHeader("Content-Type", "text/html");
    res->setBody(body);
    return res;
}
bool shelf_lexographical_sort(Shelf *const A, Shelf *const B) { return A->get_id() < B->get_id(); }
void Nuser::add_filter(Filter *new_filter)
{
    for (int i = 0; i < filters.size(); i++)
    {
        for (int j = 0; j < filters.size(); j++)
        {
            if (typeid(*filters[i]) == typeid(*filters[j]) && i != j)
            {
                if (i < j)
                {
                    filters.erase(filters.begin() + i);
                }
                else
                {
                    filters.erase(filters.begin() + j);
                }
            }
        }
    }
    filters.push_back(new_filter);
}
void Nuser::delete_filters()
{
    filters.clear();
}
void Nuser::create_shelf(Shelf *new_shelf)
{
    shelves.push_back(new_shelf);
    sort(shelves.begin(), shelves.end(), &shelf_lexographical_sort);
}
void Nuser::delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes)
{
    throw(Exception(PERMISSION_DENIED));
}
void Nuser::my_recipes(vector<string> &commands)
{
    throw(Exception(BAD_REQUEST));
}

void Nuser::post_order(Recipe *target_recipe, vector<Offer *> &offers)
{
    Order *new_order = new Order(target_recipe, this, orders.size());
    for (int i = 0; i < target_recipe->get_ingredients().size(); i++)
    {
        Offer *default_offer = nullptr;
        Offer *best_offer;
        for (int j = 0; j < offers.size(); j++)
        {
            if (offers[j]->get_ingredient_name() == target_recipe->get_ingredients()[i] && offers[j]->get_count() != 0)
            {
                if (default_offer == nullptr)
                {
                    default_offer = offers[j];
                }
                best_offer = offers[j];
                if (best_offer->calculate_cost() <= default_offer->calculate_cost())
                {
                    default_offer = best_offer;
                }
            }
        }
        if (default_offer == nullptr)
        {
            throw(Exception(NOT_FOUND));
        }
        new_order->add_offer(default_offer);
    }
    new_order->update_suppliers();
    new_order->print_order(false);
    orders.push_back(new_order);
}
void Nuser::get_orders()
{
    for (int i = 0; i < orders.size(); i++)
    {
        orders[i]->print_order(true);
    }
}
void Nuser::rate(Recipe *&target_recipe, int score, vector<string> &commands)
{
    bool rated_before = false;
    for (int i = 0; i < target_recipe->scores.size(); i++)
    {
        if (target_recipe->scores[i]->get_name() == this->get_username())
        {

            target_recipe->scores[i]->set_value(stoi(commands[SCORE_POS + 2]));
            rated_before = true;
            target_recipe->calculate_score();
            target_recipe->get_suggestor()->calculate_rating();
            cout << "OK" << endl;
            return;
        }
    }
    if (rated_before == false && commands[GENERAL_TYPE] == POSTT)
    {
        Score *rating = new Score(score, this->get_id(), this);
        target_recipe->scores.push_back(rating);
    }
    else
    {
        throw(Exception(BAD_REQUEST));
    }
    target_recipe->calculate_score();
    target_recipe->get_suggestor()->calculate_rating();
    cout << "OK" << endl;
}
void Nuser::get_shelves(int limit)
{
    if (shelves.size() == 0)
    {
        throw(Exception(EMPTY));
    }
    for (int i = 0; i < min(limit, int(shelves.size())); i++)
    {
        cout << shelves[i]->get_id() << "  " << shelves[i]->get_shelf_name() << endl;
    }
}
bool Nuser::print_chef()
{
    return false;
}
void Nuser::print_chef_detailed() {}
bool Nuser::print_user()
{
    cout << this->get_username() << endl;
    return true;
}
void Nuser::delete_shelf_recipe()
{
}
void Nuser::add_recipe(vector<string> &commands, vector<Recipe *> &recepes)
{
    throw Exception(PERMISSION_DENIED);
}
void Nuser::long_recipe(vector<Recipe *> recipes, int pk)
{
    if (recipes[pk]->get_deleted() == false)
    {
        recipes[pk]->print_recipe();
    }
    else
    {
        throw(Exception(NOT_FOUND));
    }
}
