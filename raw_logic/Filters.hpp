#include <vector>
#include <string>
#include "Recipe.hpp"
#ifndef _FILTER_HPP_
#define _FILTER_HPP_
using namespace std;
class Filter
{
public:
    Filter(bool provision);
    
    virtual bool check_provision(Recipe *target_recipe) = 0;
    ;

private:
    bool provision;
};
class Tag_Filter : public Filter
{
public:
    bool check_provision(Recipe *target_recipe);

    Tag_Filter(string tag);


private:
    string tag;
};
class Veg_Filter : public Filter
{
public:
    bool check_provision(Recipe *target_recipe);

    Veg_Filter();

};
class Score_Filter : public Filter
{
public:
    bool check_provision(Recipe *target_recipe);

    Score_Filter(vector<string> &commands);


private:
    double min_score;
    double max_score;
};
class Time_Filter : public Filter
{
public:
    bool check_provision(Recipe *target_recipe);

    Time_Filter(vector<string> &commands);


private:
    int min_time;

    int max_time;
};
#endif