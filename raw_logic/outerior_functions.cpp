#include <vector>
#include <string>
#include <iostream>

using namespace std;
vector<string> tokenizer(string tokenee, char delimiter)
{
    vector<string> tokens;
    vector<int> delimiters;
    delimiters.push_back(-1);
    for (int i = 0; i < tokenee.size(); i++)
    {
        if (tokenee[i] == delimiter || tokenee[i] == '\n' || tokenee[i]==' ')
        {
            delimiters.push_back(i);
        }
    }
    string null = "";
    delimiters.push_back(tokenee.size());
    for (int i = 0; i < delimiters.size() - 1; i++)
    {
        for (int j = delimiters[i] + 1; j < delimiters[i + 1]; j++)
        {
            null.push_back(tokenee[j]);
        }
        tokens.push_back(null);
        null = "";
    }
    return tokens;
}
vector<string> read_input(){
    string input;
    vector<string> commands;
    getline(cin,input);
    commands=tokenizer(input,' ');
    return commands;
}
double round_result(double var)
{
    double value = (int)(var * 10 + .5);
    return (double)value / 10;
}
  