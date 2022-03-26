#include <iostream>

template<class T>
class Larger{
    public:
        Larger(){}
        Larger(T a, T b){
            this->a = a;
            this->b = b;
        }
        void largest(){
            std::cout << "Largest between " << a << " and " << b << ": "
            << (a > b ? a : b) << std::endl;
        }
        T largest(T input1, T input2){
            return (input1 > input2 ? input1 : input2);
        }
    private:
        T a;
        T b;
};

int main(){
    Larger<int> intCompare(2,5);
    Larger<double> doubleCompare(98.7, 24.5);
    Larger<std::string> stringCompare;

    intCompare.largest();
    doubleCompare.largest();
    std::cout << "Largest between \"Computer\" and \"Engineer\": " <<
    stringCompare.largest("Computer", "Engineer");
    return 0;
}
