#include "Chef.hpp"
#include "main_header.hpp"
#include "Exception.hpp"
#include "Recipe.hpp"
#include "Shelf.hpp"
#include <algorithm>
#define DEFAULT_RATING 0.0
using namespace std;
Chef::Chef(vector<string> commands, int user_list_size) : UserModel(commands[USERNAME_POSITION], commands[PASSWORD_POSITION], user_list_size)
{
    average_score = DEFAULT_RATING;
}
void Chef::see_recipes(vector<Recipe *> recipes)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::get_shelves(int limit)
{
    throw(Exception(PERMISSION_DENIED));
}
Response *Chef::give_menu_response(Request *req, Menu *menu)
{
    string body;
    Response *res = new Response();
    string sid = req->getQueryParam("sid");
    vector<string> command;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body>";
    body += "<div style='margin-left:50px;width:500px;text-align: center ;float: left; border-radius: 15px; border-color: black; border-style: double;'>";
    body += "<form method ='post' action='/post_recipe?sid=" + sid + "'>";
    body += "Post your recipe<br>";
    body += "<br>";
    body += "<br>";
    body += "Recipe name<br>";
    body += "<input type = 'text' name = 'title' style = 'border-radius:10px;margin-left: 40 px;'";
    body += "<br>";
    body += "<br>";
    body += "<br>";
    body += "Ingredients";
    body += "<br>";
    body += "<br>";
    body += "<input type = 'text' name = 'ingredients' style = 'border-radius:10px;margin-left: 40 px;'";
    body += "<br>";
    body += "<br>";
    body += "<br>";
    body += "Preperation Time<br>";
    body += "<br>";
    body += "<br>";
    body += "<input type = 'number' name = 'preperation_time' style = 'border-radius:10px;margin-left: 40 px;'>";
    body += "<br>";
    body += "Tags : <br>";
    body += "<input type = 'text' name = 'tags' style = 'border-radius:10px;margin-left: 40 px;'>";
    body += "<br>";
    body += "<br>";
    body += "<div style = 'float: inherit; text-align: inherit;'>";
    body += "Vegeterian:";
    body += " <br>";
    body += "<input type='radio' name='Vegeterian' value ='Yes'> Yes";
    body += "<br>";
    body += "<input type='radio' name='Vegeterian' value ='No'> No";
    body += "</div>";
    body += "<br>";
    body += "<br>";
    body += "<br>";
    body += "<button type = 'submit'> Post</button>";
    body += " </form>";
    body += "</div>";
    body += "<div style='text-align: left;'>";
    body += "<div style='float:right;'>";
    body += "<a style='margin-left: 15px;background-color:silver; border-color: gray; border-style: double;'' href='/logout?sid=" + username;
    body += "'>logout</a>";
    body += "<a  style='margin-left: 15px;background-color:silver; border-color: gray; border-style: double;'' href='/recipes'>recipes</a>";
    body += "</div>";
    body += "</div>";
    body += "<h1 style='text-align: center; margin-left:600px; width:400px;text-align:center; border-radius: 10px;background-color:gray; border-color: gray; border-style: double;'> Your Recipes </h1>";
    for (int i = 0; i < recipes.size(); i++)
    {
        body += "<div style='text-align: center; margin-left:600px; height:75px; width:400px;; border-radius: 10px;background-color:silver; border-color: gray; border-style: double;'>";
        body += "<h2>"+recipes[i]->get_recipe_name()+"</h2>";
        body += "<a href='/delete_recipes?id=" + to_string(recipes[i]->get_id()) + "&sid=" + sid + "'>";
        body += "<h3>delete</h3>";
        body += "</a>";
        body += "</div>";
        body + "<br>";
    }
    body += "</body>";
    body += "</html>";
    res->setHeader("Content-Type", "text/html");
    res->setBody(body);
    return res;
}
bool Chef::print_chef()
{
    calculate_rating();
    cout << this->get_username() << " " << average_score << endl;
    return true;
}
void Chef ::delete_offer(string ingrdient_name)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::post_order(Recipe *target_recipe, vector<Offer *> &offers)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::change_offer(vector<string> &commands)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::add_filter(Filter *new_filter)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::create_shelf(Shelf *new_shelf)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::delete_filters()
{
    if (logged_in == true)
    {
        throw(Exception(PERMISSION_DENIED));
    }
}
bool Chef::print_user()
{
    return false;
}
void Chef::rate(Recipe *&target_recipe, int score, vector<string> &commands)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::delete_shelf_recipe()
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::calculate_rating()
{

    double sum = 0;
    int count = 0;
    for (int i = 0; i < recipes.size(); i++)
    {
        if (recipes[i]->get_rating() != DEFAULT_RATING)
        {
            sum += recipes[i]->get_rating();
            count++;
        }
    }
    if (count == 0)
    {
        average_score == DEFAULT_RATING;
        return;
    }
    if (recipes.size() != 0)
    {
        average_score = sum / count;
        return;
    }
}
void Chef::post_offer(vector<string> &commands, int size, vector<Offer *> &offers)
{
    throw(Exception(PERMISSION_DENIED));
}
bool lexographical_chef_recipe(Recipe *const A, Recipe *const B) { return A->get_recipe_name() <= B->get_recipe_name(); }
void Chef::add_recipe(vector<string> &commands, vector<Recipe *> &recepes)
{
    sort(recipes.begin(), recipes.end(), &lexographical_chef_recipe);
    Recipe *new_recipe = new Recipe(commands, recepes.size(), this);
    recipes.push_back(new_recipe);
    recepes.push_back(new_recipe);
}
void Chef::long_recipe(vector<Recipe *> recipes, int pk)
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::my_recipes(vector<string> &commands)
{
    for (int i = 0; i < recipes.size(); i++)
    {
        recipes[i]->print_recipe();
        cout << "\n";
    }
    if (recipes.size() == 0)
    {
        throw(Exception(EMPTY));
    }
}
void Chef::get_orders()
{
    throw(Exception(PERMISSION_DENIED));
}
void Chef::print_chef_detailed()
{
    calculate_rating();
    cout << get_username() << endl;
    cout << average_score << endl;
    cout << "recipes:" << endl;
    for (int i = 0; i < recipes.size(); i++)
    {
        recipes[i]->print_short(true);
    }
}
void Chef::delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes)
{

    if (all_recipes[pk]->get_suggestor()->get_id() == this->get_id())
    {

        for (int i = 0; i < recipes.size(); i++)
        {

            if (recipes[i]->get_id() == pk + 1)
            {

                for (int j = 0; j < recipes[i]->scores.size(); j++)
                {
                    delete (recipes[i]->scores[j]);
                }
                recipes.erase(recipes.begin() + i);
                all_recipes[pk]->set_deleted(true);
                calculate_rating();
                cout << "OK" << endl;
                return;
            }
        }
        throw(Exception(NOT_FOUND));
    }
    else
    {
        throw(Exception(PERMISSION_DENIED));
    }
}