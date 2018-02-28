#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <string>

using namespace std;

class Function;

/*
Node class is created in order to construct directed graph structure
*/
class Node{
public:
    // represents id of the node
    int id;

    // represents name of the node
    string name; 

};

/*
Subclass of node class and represents the variables.
Due to the different functionality, we have variable and function classes.
*/
class Variable : public Node{

public:
    bool isVisited=false;
    bool cyclicBool=false;
    // represents the value of the variable
    double value;
    bool isFirst=false;

    // represents the partial derivative value of the variable
    // i.e. (d output/ d variable)
    double derivative;

    // represents that which function determines the variable
    // it will be null for inputs or constants
    Function *from;

    // represents the list of functions that takes the variable as input
    vector<Function *> to;

    Variable(int _id, string _name, double _value = 0); // custom constructor

    // sets the from pointer
    void setFrom(Function *_from);

    // adds the given function to 'to' vector
    void addTo(Function *_to);

 };

#endif // VARIABLE