#include "function.h"
#include "variable.h"

Variable::Variable(int _id, string _name, double _value) {
    this->id=_id;
    this->name=_name;
    this->value=_value;
    this->derivative=0;


}

void Variable::setFrom(Function *_from) {
    this->from=_from;
}

void Variable::addTo(Function *_to) {
    this->to.push_back(_to);
}
