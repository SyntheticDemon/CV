#include "UserModel.hpp"
#include "Recipe.hpp"
#include "../handlers.hpp"
#ifndef _CHEF_HPP_
#define _CHEF_HPP_
class Request;
class Response;
class Chef : public UserModel
{
public:
    Chef(vector<string> commands, int user_list_size);

    void see_recipes(vector<Recipe *> recipes);

    void rate(Recipe *&target_recipe, int score, vector<string> &commands);

    void add_recipe(vector<string> &commands, vector<Recipe *> &recepes);

    void long_recipe(vector<Recipe *> recipes, int pk);

    void calculate_rating();

    void delete_offer(string ingredient_name);

    void change_offer(vector<string> &commands);

    void my_recipes(vector<string> &commands);

    void delete_recipes(vector<string> &commands, int pk, vector<Recipe *> &all_recipes);

    bool print_chef();

    bool print_user();

    void print_chef_detailed();

    void delete_shelf_recipe();

    void create_shelf(Shelf *new_shelf);

    void get_shelves(int limit);

    void add_filter(Filter *new_filter);

    void delete_filters();

    void post_offer(vector<string> &commands, int size, vector<Offer *> &offers);

    void post_order(Recipe *target_recipe, vector<Offer *> &offers);

    void get_orders();

    Response * give_menu_response(Request * req,Menu * menu);
private:
    double average_score;

    vector<Recipe *> recipes;
};
#endif