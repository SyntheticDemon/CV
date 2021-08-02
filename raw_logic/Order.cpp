#include "Order.hpp"
#include <vector>
#include "Offer.hpp"
#include <string>
#include "main_header.hpp"
#include "Supplier.hpp"
#include <algorithm>
Order::Order(Recipe *target_recipe, Nuser *Submitter, int id)
{
    this->target_recipe = target_recipe;
    this->Submitter = Submitter;
    this->id = id;
}
int Order::calculate_total_cost()
{
    int cost = 0;
    for (int i = 0; i < offers.size(); i++)
    {
        cost += offers[i]->calculate_cost();
    }
    total_cost = cost;
    return cost;
}
void Order::print_order(bool mode)
{
    if (mode == true)
    {
        cout << "====order_" << id+1 << "====" << endl;
        cout << target_recipe->get_id() << endl;
    }
    for (int i = 0; i < order_format.size(); i++)
    {
        for (int j = 0; j < order_format[i].size(); j++)
        { 
            cout << order_format[i][j] << " ";
        }
        cout << "\n";
    }
    cout << total_cost << endl;
}
bool lex(const vector<string> &A, const vector<string> &B) { return A[0] <= B[0]; }
vector<vector<string>> Order::make_order()
{
    vector<string> supplier_names;
    vector<vector<string>> supplier_names_2;
    for (int i = 0; i < offers.size(); i++)
    {
        supplier_names.push_back(offers[i]->supplier->get_username());
    }
    for (int i = 0; i < supplier_names.size(); i++)
    {
        bool is_inside = false;
        for (int j = 0; j < supplier_names_2.size(); j++)
        {
            if (supplier_names_2[j][0] == supplier_names[i])
            {
                is_inside = true;
            }
        }
        if (is_inside == false)
        {
            supplier_names_2.push_back(vector<string>{supplier_names[i]});
        }
    }
    sort(supplier_names_2.begin(), supplier_names_2.end(), lex);
    for (int i = 0; i < offers.size(); i++)
    {
        for (int j = 0; j < supplier_names_2.size(); j++)
        {
            if (offers[i]->supplier->get_username() == supplier_names_2[j][0])
            {
                supplier_names_2[j].push_back(offers[i]->get_ingredient_name());
            }
        }
    }
    for (int i = 0; i < supplier_names_2.size(); i++)
    {
        sort(supplier_names_2[i].begin() + 1, supplier_names_2[i].end());
    }
    return supplier_names_2;
}
void Order::add_offer(Offer *mini_offer)
{
    offers.push_back(mini_offer);
}
void Order::update_suppliers()
{
    if (calculate_total_cost() > Submitter->get_credits())
    {
        throw(Exception(BAD_REQUEST));
    }
    for (int i = 0; i < offers.size(); i++)
    {
        offers[i]->supplier->update_credits(offers[i]->supplier->get_credits() + offers[i]->calculate_cost());
        offers[i]->update_count(offers[i]->get_count() - 1);
    }
    this->order_format = make_order();
    Submitter->update_credits(-calculate_total_cost() + Submitter->get_credits());
}