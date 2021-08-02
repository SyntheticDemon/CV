#include "Score.hpp"
#include "Normal_User.hpp"
Score::Score(int value,int list_size,Nuser *associate){
    this->associated_user=associate;
    
    this->value=value;

    this->pk=list_size;

}
string Score::get_name(){
    return associated_user->get_username();
}