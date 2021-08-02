#include "Filters.hpp"
#include "Recipe.hpp"
#include "main_header.hpp"
#include "Exception.hpp"
#define YES "Yes"
#define MIN_POS 4
#define MAX_POS 6
Filter::Filter(bool provision)
{
    this->provision = provision;
}
Tag_Filter ::Tag_Filter(string tag) : Filter(false)
{
    this->tag = tag;
}

bool Tag_Filter::check_provision(Recipe *target_recipe)
{
    bool check = false;
    for (int i = 0; i < target_recipe->get_tags().size(); i++)
    {
        if (target_recipe->get_tags()[i] == tag)
        {
            check = true;
        }
    }
    return check;
}
Veg_Filter ::Veg_Filter() : Filter(false)
{
}
bool Veg_Filter::check_provision(Recipe *target_recipe)
{
    if (target_recipe->get_vegetarian() == YES)
    {
        return true;
    }
    return false;
}
Score_Filter::Score_Filter(vector<string> &commands) : Filter(false)
{

    if (stoi(commands[MIN_POS]) > stoi(commands[MAX_POS]) ||
        stoi(commands[MIN_POS]) > 5 ||
        stoi(commands[MIN_POS]) < 0 || stoi(commands[MAX_POS]) < 0 || stoi(commands[MAX_POS]) > 5)
    {
        throw(Exception(BAD_REQUEST));
    }
    max_score = stoi(commands[MAX_POS]);
    min_score = stoi(commands[MIN_POS]);
}
bool Score_Filter::check_provision(Recipe *target_recipe)
{
    if (target_recipe->get_rating() >= min_score && target_recipe->get_rating() <= max_score)
    {
        return true;
    }
    return false;
}
Time_Filter::Time_Filter(vector<string> &commands) : Filter(false)
{

    if (commands[MAX_POS] < commands[MIN_POS])
    {
        throw(Exception(BAD_REQUEST));
    }
    min_time = stoi(commands[MIN_POS]);
    max_time = stoi(commands[MAX_POS]);
}
bool Time_Filter::check_provision(Recipe *target_recipe)
{
    if (stoi(target_recipe->get_time()) >= min_time && stoi(target_recipe->get_time()) <= max_time)
    {
        return true;
    }
    return false;
}