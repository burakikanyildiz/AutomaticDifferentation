#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <iterator>
#include <sstream>
#include <cmath>
#include <stack>

using namespace std;

template<class Container>
void split1(const string& str, Container& cont){
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),back_inserter(cont));
}


// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}
vector<int> allNums; //vector holds numbers to act them as variable after
int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        allNums.push_back(idCount);
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    // printf("%s -> %d\n",inp.c_str(), res);
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);
    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fId = getFunction(fnc);
    int inpId1 = getVariable(inp1);
    int inpId2 = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId1]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId1]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::readGraph(string fileName){
    ifstream infile(fileName);
    string line;
    while(true){
        getline(infile, line);
        if(line.length()==0)
            break;
        vector<string> words2;
        split1(line,words2);
        if(words2[0].compare("input")==0){
            int temp=getVariable(words2[1]);
           inputNodes.push_back(temp);
            vars[temp]->isFirst=true;
        }else if(words2[0].compare("output")==0){
            int a=getVariable(words2[1]);
            outputNode=a;
            nameOfOutput=words2[1];
        }else{
            string lValue=words2[0];
            string rValue = words2[2];
            for (int i = 3; i < words2.size(); i++) {
                rValue += " " + words2[i];
            }
            addAssignment(lValue, rValue);
        }
    }
}



bool Graph::isCyclic(){
    queue<Variable> q;
    for(int i=0; i<allNums.size();i++){
        q.push(*vars[allNums[i]]);
    }

    for(int i=0;i<inputNodes.size();i++) {
        q.push(*vars[inputNodes[i]]);
    }
    while(!q.empty()) {
        Variable n = q.front();
        q.pop();
        if(vars[n.id]->cyclicBool){
            return true;
        }
        vars[n.id]->cyclicBool=true;
        for(int i=0;i<vars[n.id]->to.size();i++){
            int k=vars[n.id]->to[i]->id;
            fncs[k]->inputSize2--;
            if(fncs[k]->inputSize2==0) {
                q.push(*fncs[k]->output);
            }
        }
    }
    return false;

}

double Graph::forwardPass(vector<double> inputValues){
    queue<Variable> q;
    for(int i=0; i<allNums.size();i++){
        q.push(*vars[allNums[i]]);
    }
    for(int i=0; i<inputValues.size();i++){
        vars[inputNodes[i]]->value=inputValues[i];
        q.push(*vars[inputNodes[i]]);
    }
    while(!q.empty()){
        Variable n=q.front();
        q.pop();
        for(int i=0;i<vars[n.id]->to.size();i++){
            int k=vars[n.id]->to[i]->id;
            fncs[k]->doForward();
            fncs[k]->inputsSize--;
            if(fncs[k]->inputsSize==0) {
                q.push(*fncs[k]->output);
            }
        }
    }
    return vars[outputNode]->value;


}
vector<double> Graph::backwardPass(){

    vars[outputNode]->derivative=1;
    for(int i=0;i<inputNodes.size();i++)
        backwardPassHelper(inputNodes[i]);

    vector<double> returnVec;
    for(int i=0;i<inputNodes.size();i++){
        returnVec.push_back(vars[inputNodes[i]]->derivative);
    }
    return returnVec;
}

void Graph::addAssignment(string lvalue, string rvalue) {
    vector<string> words;
    split1(rvalue,words);
    int length=words.size();
    if(length==1) {
        addUnaryFunction("identity",rvalue,lvalue);
    }
    else if(length==2){
        addUnaryFunction(words[0], words[1],lvalue);
    }else{
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }
}

void Graph::backwardPassHelper(int id) {
        for (int i = 0; i < vars[id]->to.size(); i++) {
            backwardPassHelper(vars[id]->to[i]->output->id);
        }
        if(!vars[id]->isFirst) {
            if(!fncs[vars[id]->from->id]->isVisited) {
                fncs[vars[id]->from->id]->doBackward();
                fncs[vars[id]->from->id]->isVisited=true;
            }
        }
};