#include <iostream>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <random>
#include "graph.h"

template<class Container>
void split1(const string& str, Container& cont){
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),back_inserter(cont));
}
using namespace std;

int main(int argc, char* argv[]){
    if(argc!=5){
        cout<<"Run the code with following command: ./project4 [functionDefinitionFile] [inputValuesFile] [outputValuesFile] [derivativeValuesFile]"<<endl;
        return 1;
    }

    ifstream infile1(argv[2]);
    string line;
    getline(infile1,line);
    ofstream outfile(argv[3]);
    ofstream outfile1(argv[4]);
    outfile.precision(std::numeric_limits<double>::max_digits10);
    outfile1.precision(std::numeric_limits<double>::max_digits10);

    bool b=true;
    bool boool=true;
    Graph g;
    g.readGraph(argv[1]);

    if(g.isCyclic()){
        outfile<<"ERROR: COMPUTATION GRAPH HAS CYCLE!";
        outfile1<<"ERROR: COMPUTATION GRAPH HAS CYCLE!";
        return 0;
    }
    while(true){
        vector<double> inputValues;
        Graph myGraph;
        getline(infile1,line);
        myGraph.readGraph(argv[1]);
        vector<string> words;
        if(line.length()==0) {
            break;
        }
        if(b) {
            outfile << myGraph.nameOfOutput << endl;
            b = false;
        }
        split1(line,words);
        for(int i=0;i<words.size();i++) {
            inputValues.push_back(stod(words[i]));
        }
        outfile<<myGraph.forwardPass(inputValues)<<endl;

        vector<double> backPass;
        backPass=myGraph.backwardPass();
        if(boool) {
            outfile1 << "d" << myGraph.vars[myGraph.outputNode]->name << "/d"
                     << myGraph.vars[myGraph.inputNodes[0]]->name;
            for (int i = 1; i < myGraph.inputNodes.size(); i++) {
                outfile1 << " d" << myGraph.vars[myGraph.outputNode]->name << "/d"
                         << myGraph.vars[myGraph.inputNodes[i]]->name;
            }
            boool=false;
            outfile1<<endl;
        }
        for(int i=0;i<backPass.size();i++){
            outfile1<<backPass[i]<<" ";
        }
        outfile1<<endl;
    }



    return 0;
}