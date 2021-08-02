#include <vector>
#include <string>
#include "Offer.hpp"
#define INGREDIENT_POS 4
#define PRICE_POS 6
#define COUNT_POS 8
#define PACKAGING_POS 10
Offer::Offer(vector<string> &commands, int size, Supplier *supplier)
{
    packaging_cost = stoi(commands[PACKAGING_POS]);
    ingredient_name = commands[INGREDIENT_POS];
    price = stoi(commands[PRICE_POS]);
    count = stoi(commands[COUNT_POS]);
    pk = size;
    this->supplier = supplier;
}
int Offer::calculate_cost()
{
    return price + packaging_cost;
}
string Offer::get_ingredient_name() { return ingredient_name; }