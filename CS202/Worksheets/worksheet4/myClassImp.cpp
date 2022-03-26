#include <iostream>
#include "myClass.h"

void myClass::set(int x, int y){
    num1 = x;
    num2 = y;
}

void myClass::print() const{
    std::cout << "Number 1: " << num1 << "\nNumber 2: " <<
    num2 << std::endl;
}

int myClass::compute(int x){
    if(x > 0){
        return (num1 + num2) / x;
    }
    else{
        return num1 - num2 + x;
    }
}

bool myClass::equal(){
    return (num1 == num2);
}

myClass::myClass(){
    num1 = 0;
    num2 = 0;
}

myClass::myClass(int x, int y){
    num1 = x;
    num2 = y;
}
