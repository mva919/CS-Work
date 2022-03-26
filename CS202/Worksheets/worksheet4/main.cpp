#include <iostream>
#include "myClass.h"

int main(){
    int n1, n2, x;
    std::cout << "Enter number1: ";
    std::cin >> n1;
    std::cout << "Enter number2: ";
    std::cin >> n2;
    myClass m1(n1, n2);
    m1.print();

    std::cout << "Compute X value:\n" <<
     m1.compute(n1) << std::endl;

    std::cout << "Compare num1 and num2:\n" <<
    m1.equal() << std::endl;

    std::cout << "Set the values using set function\n";
    m1.set(20, 20);

    std::cout << "Compute X value:\n" <<
    m1.compute(-5) << std::endl;

    std::cout << "Compare num1 and num2:\n" <<
    m1.equal() << std::endl;

    return 0;
}
