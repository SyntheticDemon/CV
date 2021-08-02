#include "raw_logic/main_header.hpp"
#include "raw_logic/outerior_functions.hpp"
#include "raw_logic/main_header.hpp"
#include "raw_logic/Normal_User.hpp"
#include "raw_logic/Chef.hpp"
#include "raw_logic/Exception.hpp"
#include "raw_logic/Shelf.hpp"
#include "raw_logic/Offer.hpp"
#include "raw_logic/Order.hpp"
#include <algorithm>
#include "data_root.hpp"
Menu::Menu()
{
}
int Menu::recipe_search(int pk)
{
    for (int i = 0; i < recipes.size(); i++)
    {
        if (recipes[i]->get_id() == pk)
        {
            return i;
        }
    }
    throw(Exception(NOT_FOUND));
}
void Menu::handle_recipe(vector<string> &commands, UserModel *current_user)
{
    if (commands.size() > CM_ALL_RECIPES_SIZE && commands.size() == DETAILED_RECIPE_SIZE)
    {
        if (commands[OTHER_ARG_START] == ARG_FOLLOWS)
        {
            current_user->long_recipe(recipes, recipe_search(stoi(commands[RECIPE_ID_POSITION])));
        }
        else
        {
            throw(Exception(BAD_REQUEST));
        }
    }
    else if (commands.size() == CM_ALL_RECIPES_SIZE)
    {
        current_user->see_recipes(recipes);
    }
    else
    {
        throw(Exception(BAD_REQUEST));
    }
}
void Menu ::get_chefs(vector<string> &commands)
{
    if (commands[GENERAL_TYPE] == GETT && commands.size() == GET_ALL_CHEFS)
    {
        for (int i = 0; i < users.size(); i++)
        {
            users[i]->print_chef();
        }
        return;
    }
    else if (commands[GENERAL_TYPE] == GETT && commands.size() == GET_ONE_CHEF)
    {
        const vector<string> get_one_chef_format = {GETT, CHEFS, ARG_FOLLOWS, CHEF_USERNAME, NODIF};
        for (int i = 0; i < get_one_chef_format.size(); i++)
        {
            if (commands[i] != get_one_chef_format[i] && get_one_chef_format[i] != NODIF)
            {
                throw(Exception(BAD_REQUEST));
            }
            else if (i == GET_ONE_CHEF - 1)
            {
                {
                    UserModel *temp_chef = user_search(commands[i], commands);
                    temp_chef->print_chef_detailed();
                    return;
                }
            }
        }
    }
    throw(Exception(BAD_REQUEST));
}
void Menu::check_command_format(vector<string> command_format, vector<string> commands)
{
    if (command_format.size() == commands.size())
    {
        for (int i = 0; i < commands.size(); i++)
            if (command_format[i] != NODIF && commands[i] != command_format[i])
            {
                throw(Exception(BAD_REQUEST));
            }
    }
    else
    {
        throw(Exception(BAD_REQUEST));
    }
}
int Menu::shelf_search(vector<string> &commands, bool check_permission, UserModel *current_user)
{
    for (int i = 0; i < shelves.size(); i++)
    {
        if (stoi(commands[4]) == shelves[i]->get_id())
        {
            return shelves[i]->get_id();
        }
    }
    throw(Exception(NOT_FOUND));
}
void Menu::shelf_recipe_commands(vector<string> &commands, UserModel *current_user)
{
    vector<string> recipe_addition_format = {PUT, SHELVES_RECIPES, ARG_FOLLOWS, SHELF_ID, NODIF, RECIPE_ID, NODIF};
    if (commands[0] == PUT)
    {
        current_user->delete_shelf_recipe();
        check_command_format(recipe_addition_format, commands);
        shelves[shelf_search(commands, true, current_user) - 1]->add_recipe(recipes[recipe_search(stoi(commands[recipe_addition_format.size() - 1]))]);
        cout << "OK" << endl;
    }
    else if (commands[0] == DELETE)
    {
        current_user->delete_shelf_recipe();
        recipe_addition_format[0] = DELETE;
        check_command_format(recipe_addition_format, commands);
        int id = recipe_search(stoi(commands[recipe_addition_format.size() - 1]));
        shelves[shelf_search(commands, true, current_user) - 1]->delete_recipe(commands, stoi(commands[recipe_addition_format.size() - 1]));
    }
}
void Menu::handle_shelves(vector<string> &commands, UserModel *current_user)
{
    if (commands[0] == POSTT)
    {
        vector<string> shelf_creation_format = {POSTT, SHELVES, ARG_FOLLOWS, NAME, NODIF};
        check_command_format(shelf_creation_format, commands);
        Shelf *new_shelf = new Shelf(commands, shelves.size() + 1, current_user);
        shelves.push_back(new_shelf);
        current_user->create_shelf(new_shelf);
        cout << new_shelf->get_id() << endl;
    }
    else if (commands[0] == GETT)
    {
        vector<string> see_shelves_format = {GETT, SHELVES, ARG_FOLLOWS, USERNAME, NODIF, LIMIT, NODIF};
        int limit = stoi(commands[see_shelves_format.size() - 1]);
        string username = commands[USERNAME_POSITION];
        user_search(username, commands)->get_shelves(limit);
    }
}
void Menu ::get_users(vector<string> &commands, UserModel *current_user)
{
    if (current_user->print_user() == false)
    {
        throw(Exception(PERMISSION_DENIED));
    }
    int user_size = 0;
    if (commands[GENERAL_TYPE] == GETT)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i]->get_username() != current_user->get_username())
            {
                if (users[i]->print_user() == true)
                {
                    user_size++;
                }
            }
        }
        if (user_size == 0)
        {
            throw(Exception(EMPTY));
        }
    }
    else
        throw(Exception(BAD_REQUEST));
}
void Menu::handle_recipe_deletion(vector<string> &commands, UserModel *current_user)
{

    if (commands.size() < DETAILED_RECIPE_SIZE)
        throw(Exception(BAD_REQUEST));

    const vector<string> deletion_format = {DELETE, RECIPES, ARG_FOLLOWS, ID};

    for (int i = 0; i < deletion_format.size(); i++)
    {
        if (commands[i] != deletion_format[i])
        {
            throw(Exception(BAD_REQUEST));
        }
    }
}
void Menu::general_recipe(vector<string> &commands, UserModel *current_user)
{
    if (commands[GENERAL_TYPE] == PUT)
        throw Exception(BAD_REQUEST);
    else if (commands[GENERAL_TYPE] == GETT)
    {
        handle_recipe(commands, current_user);
    }
    else if (commands[GENERAL_TYPE] == POSTT)
    {

        current_user->add_recipe(commands, recipes);
    }
    else if (commands[GENERAL_TYPE] == DELETE)
    {

        handle_recipe_deletion(commands, current_user);
        int id = recipe_search(stoi(commands[RECIPE_ID_POSITION]));
        current_user->delete_recipes(commands, id, recipes);
    }
}
void Menu::handle_filters(vector<string> &commands, UserModel *current_user)
{
    const vector<string> tag_filter_format = {POSTT, FILTERS, ARG_FOLLOWS, TAG, NODIF};
    const vector<string> vegetarian_format = {POSTT, FILTERS, ARG_FOLLOWS, VEGETARIAN};
    const vector<string> time_format = {POSTT, FILTERS, ARG_FOLLOWS, MIN_MINUTES, NODIF, MAX_MINUTES, NODIF};
    const vector<string> score_format = {POSTT, FILTERS, ARG_FOLLOWS, MIN_RATING, NODIF, MAX_RATING, NODIF};
    Filter *new_filter;
    if (commands[3] == TAG)
    {
        check_command_format(tag_filter_format, commands);
        new_filter = new Tag_Filter(commands[tag_filter_format.size() - 1]);
    }
    else if (commands[3] == VEGETARIAN)
    {
        check_command_format(vegetarian_format, commands);
        new_filter = new Veg_Filter();
    }
    else if (commands[3] == MIN_MINUTES)
    {
        check_command_format(time_format, commands);
        new_filter = new Time_Filter(commands);
    }
    else if (commands[3] == MIN_RATING)
    {
        check_command_format(score_format, commands);
        new_filter = new Score_Filter(commands);
    }
    current_user->add_filter(new_filter);
}

void Menu::check_duplication(string &username, string email)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (username == users[i]->get_username())
        {
            throw Exception(BAD_REQUEST);
        }
    }
}
void Menu::handle_signup(vector<string> &commands)
{
    vector<string> signup_format = {POSTT, SIGNUP, ARG_FOLLOWS, USERNAME, NODIF, PASSWORD, NODIF, TYPE, NODIF};
    check_command_format(signup_format, commands);
}
bool lexo_user_arrange(UserModel *const A, UserModel *const B) { return A->get_username() <= B->get_username(); }
void Menu::signup(vector<string> &commands)
{

    check_duplication(commands[USERNAME_POSITION], " ");
    handle_signup(commands);
    if (commands[commands.size() - 1] == USER)
    {
        Nuser *new_user = new Nuser(commands, users.size());
        users.push_back(new_user);
    }
    else if (commands[commands.size() - 1] == CHEF)
    {
        Chef *new_chef = new Chef(commands, users.size());
        users.push_back(new_chef);
    }
    else
    {
        throw Exception(BAD_REQUEST);
    }
}
UserModel *Menu::user_search(string username, vector<string> &commands)
{
    sort(users.begin(), users.end(), &lexo_user_arrange);
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->get_username() == username)
        {
            return users[i];
        }
    }
    if (commands[SPECIFIC_COMMAND] == LOGIN)
    {
        throw(Exception(BAD_REQUEST));
    }
    else
    {
        throw(Exception(NOT_FOUND));
    }
}
void Menu::de_allocate()
{
    for (int i = 0; i < users.size(); i++)
    {
        delete (users[i]);
    }
    for (int i = 0; i < recipes.size(); i++)
    {
        delete (recipes[i]);
    }
    for (int i = 0; i < shelves.size(); i++)
    {
        delete (shelves[i]);
    }
}
void Menu::handle_rating(vector<string> &commands)
{
    if (commands[GENERAL_TYPE] != POSTT && commands[GENERAL_TYPE] != PUT)
    {

        throw(Exception(BAD_REQUEST));
    }
    if (commands[OTHER_ARG_START] != ARG_FOLLOWS ||
        commands.size() < RATE_SIZE ||
        commands[SPECIFIC_COMMAND] != RATES ||
        commands[RECIPE_ID_KEYWORD] != RECIPE_ID)
    {
        throw(Exception(BAD_REQUEST));
    }
}
void Menu::rate(vector<string> &commands, UserModel *current_user)
{
    try
    {
        if (commands[GENERAL_TYPE] == POSTT || commands[GENERAL_TYPE] == PUT)
        {
            const vector<string> rating_format = {NODIF, RATES, ARG_FOLLOWS, RECIPE_ID, NODIF, SCORE, NODIF};
            check_command_format(rating_format, commands);
        }
        else
        {
            throw(Exception(BAD_REQUEST));
        }
        current_user->rate(recipes[recipe_search(stoi(commands[SCORE_POS]))], stoi(commands[SCORE_POS + 2]), commands);
    }
    catch (Exception rating_error)
    {
        cout << rating_error.get_err() << endl;
    }
}
void Menu::login(vector<string> &commands, UserModel *current_user)
{

    const vector<string> login_format = {POSTT, LOGIN, ARG_FOLLOWS, USERNAME, NODIF, PASSWORD, NODIF};
    check_command_format(login_format, commands);
    if (commands[PASSWORD_POSITION] == user_search(commands[USERNAME_POSITION], commands)->get_password())
    {

        current_user->user_login(true);
        active_users.push_back(user_search(commands[USERNAME_POSITION], commands));
    }
    else
    {
        throw(Exception(BAD_REQUEST));
    }
}
void Menu::logout(UserModel *current_user)
{
    current_user->user_login(false);
    current_user->user_logout();
    current_user->delete_filters();
    cout << "OK" << endl;
}