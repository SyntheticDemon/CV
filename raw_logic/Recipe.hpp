#include <vector>
#include <string>
#include <iostream>
#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_
#include "Score.hpp"
using namespace std;
class Chef;
class Recipe
{
public:
    Recipe(vector<string> &commands, int size, Chef *associate);

    vector<Score *> scores;

    void list_print(vector<string> list, string);

    void print_recipe();

    Chef *get_suggestor() { return suggestor; }

    string get_recipe_name() { return recipe_name; }

    int get_id() { return pk; }

    double get_rating() { return rating; }

    void push_back_score(Score *&score);

    void print_short(bool mode);

    void calculate_score();

    vector<string> get_ingredients() { return ingredients; }

    vector<string> get_tags() { return tags; }

    string get_vegetarian() { return vegetarian; }

    string get_time() { return time_to_ready; }

    void set_deleted(bool value);

    bool get_deleted() { return deleted; }

private:
    int pk;

    string recipe_name;

    string image;

    string time_to_ready;

    vector<string> tags;

    string vegetarian;

    Chef *suggestor;

    vector<string> ingredients;

    bool deleted;

    double rating;
};
#endif