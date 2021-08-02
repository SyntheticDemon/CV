#include "outerior_functions.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    Menu *new_menu = new Menu();
    while (true)
    {
        vector<string> input = read_input();
        if (input.size() == 1)
        {
            new_menu->de_allocate();
            break;
        }

        new_menu->direct_command(input);
    }
    return 0;
}