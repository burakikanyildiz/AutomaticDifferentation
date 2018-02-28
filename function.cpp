#include <iostream>
#include "function.h"
#include <cmath>
Function::Function(int _id, string _name) {
    this->id=_id;
    this->name=_name;
    inputsSize=0;
    inputSize2=0;
}

void Function::addInput(Variable *input) {
    inputs.push_back(input);
    inputsSize++;
    inputSize2++;
}

void Function::setOutput(Variable *_output) {
    this->output=_output;
}

void Addition::doForward() {
    double d=inputs[0]->value+inputs[1]->value;
    output->value=d;
}

void Addition::doBackward() {
    inputs[0]->derivative+=output->derivative;
    inputs[1]->derivative+=output->derivative;
}

Addition::Addition(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Multiplication::doForward() {
    double d=inputs[0]->value*inputs[1]->value;
    this->output->value=d;
  }

void Multiplication::doBackward() {
    inputs[0]->derivative+=inputs[1]->value*output->derivative;
    inputs[1]->derivative+=inputs[0]->value*output->derivative;
}

Multiplication::Multiplication(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Sine::doForward() {
    double d=sin(inputs[0]->value);
    output->value=d;

}

void Sine::doBackward() {
    inputs[0]->derivative+=cos(inputs[0]->value)*output->derivative;
}

Sine::Sine(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;

}

void Subtraction::doForward() {
    double d=inputs[0]->value-inputs[1]->value;
    output->value=d;

}

void Subtraction::doBackward() {
    inputs[0]->derivative+=output->derivative;
    inputs[1]->derivative+=-output->derivative;
}

Subtraction::Subtraction(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Division::doForward() {
    double d=inputs[0]->value/inputs[1]->value;
    output->value=d;

}

void Division::doBackward() {
    inputs[0]->derivative+=1.0/inputs[1]->value*output->derivative;
    inputs[1]->derivative+=-1.0/pow(inputs[1]->value,2)*inputs[0]->value*output->derivative;
}

Division::Division(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Power::doForward() {
    double d=pow(inputs[0]->value,inputs[1]->value);
    output->value=d;

}

void Power::doBackward() {
    inputs[0]->derivative+=inputs[1]->value*pow(inputs[0]->value,inputs[1]->value-1)*output->derivative;
    inputs[1]->derivative+=pow(inputs[0]->value,inputs[1]->value)*log(inputs[0]->value)*output->derivative;
}

Power::Power(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Cosine::doForward() {
    double d=cos(inputs[0]->value);
    output->value=d;
}

void Cosine::doBackward() {
    inputs[0]->derivative+=(-sin(inputs[0]->value))*output->derivative;
}

Cosine::Cosine(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Tangent::doForward() {
    double d=tan(inputs[0]->value);
    output->value=d;
}

void Tangent::doBackward() {
    inputs[0]->derivative+=1.0/pow(cos(inputs[0]->value),2)*output->derivative;
}

Tangent::Tangent(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void ArcTangent::doForward() {
    double d=atan(inputs[0]->value);
    output->value=d;
}

void ArcTangent::doBackward() {
    inputs[0]->derivative+=1.0/(1+pow(inputs[0]->value,2))*output->derivative;

}

ArcTangent::ArcTangent(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void ArcCosine::doForward() {
    double d=acos(inputs[0]->value);
    output->value=d;
}

void ArcCosine::doBackward() {
    inputs[0]->derivative+=-1.0/sqrt(1-pow(inputs[0]->value,2))*output->derivative;
}

ArcCosine::ArcCosine(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void ArcSine::doForward() {
    double d=asin(inputs[0]->value);
    output->value=d;
}

void ArcSine::doBackward() {
    inputs[0]->derivative+=1.0/sqrt(1-pow(inputs[0]->value,2))*output->derivative;

}

ArcSine::ArcSine(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Exponential::doForward() {
    double d=exp(inputs[0]->value);
    output->value=d;
}

void Exponential::doBackward() {
    inputs[0]->derivative+=exp(inputs[0]->value)*output->derivative;
}

Exponential::Exponential(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Log::doForward() {
    double d=log(inputs[0]->value);
    output->value=d;
}

void Log::doBackward() {
    inputs[0]->derivative+=1.0/inputs[0]->value*output->derivative;
}

Log::Log(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Sqrt::doForward() {
    double d=sqrt(inputs[0]->value);
    output->value=d;
}

void Sqrt::doBackward() {
    inputs[0]->derivative+=1.0/(2*sqrt(inputs[0]->value))*output->derivative;
}

Sqrt::Sqrt(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Identity::doForward() {
    double d=inputs[0]->value;
    output->value=d;
}

void Identity::doBackward() {
    inputs[0]->derivative+=output[0].derivative;
}

Identity::Identity(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}

void Log10::doForward() {
    double d=log10(inputs[0]->value);
    output->value=d;
}

void Log10::doBackward() {
    inputs[0]->derivative+=1.0/inputs[0]->value*log10(exp(1))*output->derivative;

}

Log10::Log10(int _id, string _name) : Function(_id, _name) {
    this->id=_id;
    this->name=_name;
}
