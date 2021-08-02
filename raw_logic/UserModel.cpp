#include "UserModel.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "main_header.hpp"
#include "Recipe.hpp"
using namespace std;
UserModel::UserModel(string name, string password, int list_size)
{
    primary_key = list_size;
    this->username = name;
    this->password = password;
    logged_in = false;
    credits = 0;
}
string UserModel::get_username() { return username; }

string UserModel::get_password() { return password; }

bool UserModel::get_logged_in() { return logged_in; }

void UserModel::user_logout() { logged_in = false; }

void UserModel::user_login(bool value) { logged_in = value; }
