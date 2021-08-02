#include <vector>
#include <string>
#ifndef _SCORE_HPP_
#define _SCORE_HPP_
class Nuser;
using namespace std;
class Score{
    public:
        Score(int value,int list_size,Nuser *associate);

        int get_pk(){return pk;}

        int get_value(){return value;}

        void set_value(int value){this->value=value;}

        string get_name();

    private:
        int pk;
        
        int value;

        Nuser * associated_user;        
};
#endif