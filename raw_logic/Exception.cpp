#include <vector>
#include <string>
#include "Exception.hpp"
string Exception::get_err() { return this->err; };
Exception::Exception(string err)
{
    this->err = err;
}
