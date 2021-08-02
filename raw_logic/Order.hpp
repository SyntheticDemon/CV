#ifndef _ORDER_HPP_
#define _ORDER_HPP_
#include <string>
#include <algorithm>
#include "Recipe.hpp"
#include "Offer.hpp"
#include "Normal_User.hpp"
class Order
{
public:
    Order(Recipe *target_recipe, Nuser *Submitter,int id);
    int calculate_total_cost();
    void add_offer(Offer *mini_offer);
    int return_offers_size() { return offers.size(); }
    void update_suppliers();
    UserModel *Submitter;
    void print_order(bool mode);
    vector<vector<string>> make_order();

private:
    int total_cost;
    int id;
    vector<vector<string>> order_format;
    vector<Offer *> offers;
    Recipe *target_recipe;
};
#endif