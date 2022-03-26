#include <iostream>

class Box{
    public:
        Box(int l=0, int w=0): length(l), width(w) {}
        void print() const { std::cout << length << " " << width << "\n"; }
        void operator - ();
        bool operator == (Box second);
        Box operator - (Box second);
    private:
        int length;
        int width;
};

void Box::operator - (){
    length = -length;
    width = -width;
}

bool Box::operator == (Box second) {
    if(length == second.length && width == second.width) return true;
    return false;
}

Box Box::operator - (Box second){
    int l = length - second.length;
    int w = width - second.width;
    Box res(l, w);
    return res;
}

int main(){
    Box b1(1,3);
    -b1;
    b1.print();
    Box b2(-1, -3);
    if(b1 == b2)
        std::cout << "The boxes are equal.\n";

    Box b3(0,0);
    Box b4(4, 6);
    b3 = b1 - b4;
    b3.print();
    return 0;
}
