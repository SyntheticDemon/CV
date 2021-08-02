#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_
#include <string>
using namespace std;
class Exception
{

public:
    string get_err();
    Exception(string err);

private:
    string err;
    string specific;
};
#endif