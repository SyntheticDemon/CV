#include <vector>
#include <string>
#ifndef _OFFER_HPP_
#define _OFFER_HPP_
using namespace std;
class Supplier;
class Offer
{
public:
    Offer(vector<string> &commands, int size, Supplier *supplier);
    void set_price(int price) { this->price = price; }
    void set_count(int new_count) { this->count = count; }
    void update_count(int new_count) { this->count = new_count; }
    int get_pk() { return pk; }
    int get_count() { return count; }
    int get_cost() { return packaging_cost; }
    int calculate_cost();
    string get_ingredient_name();
    Supplier *supplier;

private:
    int pk;
    string ingredient_name;
    int price;
    int count;
    int packaging_cost;
};
#endif