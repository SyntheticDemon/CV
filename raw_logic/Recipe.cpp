#include "Recipe.hpp"
#include "outerior_functions.hpp"
#include "main_header.hpp"
#include "Chef.hpp"
#define COMMA ' '
#define INGRED 6
#define VEG 8
#define IMAGE 14
#define TAG2 12
#define TIME_TO 10
#define RNAME 4
Recipe::Recipe(vector<string> &commands, int size, Chef *associate)
{

    this->ingredients = tokenizer(commands[INGRED], COMMA);
    this->recipe_name = commands[RNAME];
    this->suggestor = associate;
    this->vegetarian = commands[VEG];
    this->time_to_ready = commands[TIME_TO];
    this->tags = tokenizer(commands[TAG2], COMMA);
    image = commands[IMAGE];
    rating = 0.0;
    deleted = false;
    pk = size + 1;
}
void Recipe::set_deleted(bool value)
{
    deleted = value;
}
void Recipe::print_short(bool mode)
{
    cout << pk << " ";
    cout << recipe_name << " ";
    cout << vegetarian << " ";
    cout << time_to_ready << " ";
    if (mode == true)
    {
        cout << double(rating);
    }
    cout << endl;
}
void Recipe::list_print(vector<string> list, string list_name)
{
    cout << list_name << ": [";
    for (int i = 0; i < list.size(); i++)
    {
        if (i == list.size() - 1)
        {
            cout << list[i] << "]" << endl;
            break;
        }
        cout << list[i] << ", ";
    }
}
void Recipe::calculate_score()
{
    int sum = 0;
    for (int i = 0; i < scores.size(); i++)
    {
        sum += scores[i]->get_value();
    }
    rating = round_result(double(double(sum) / double(scores.size())));
}
void Recipe::push_back_score(Score *&score)
{
    scores.push_back(score);
}
void Recipe::print_recipe()
{
    cout << pk << endl;
    cout << recipe_name << endl;
    cout << "vegetarian: " << vegetarian << endl;
    list_print(ingredients, "ingredients");
    cout << "minutes to ready: " << time_to_ready << endl;
    list_print(tags, "tags");
    cout.precision(1);
    cout << "rating: " << fixed << rating << endl;
}