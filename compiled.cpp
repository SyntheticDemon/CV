#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include "utils/utilities.hpp"
using namespace std;
int main(int argc, char const *argv[])
{
std::map<std::string, std::string> context;
readMapFromFile(".template/map.txt", &context);
string __unparsedTemplate__ = readFile(".template/local0.html");

string __variable0;
__variable0 = __unparsedTemplate__.substr(0, 4145152);
cout << __variable0;
return 0;
}
