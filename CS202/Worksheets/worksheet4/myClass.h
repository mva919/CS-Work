#ifndef MYCLASS_H
#define MYCLASS_H

class myClass{
    private:
        int num1;
        int num2;
    public:
        myClass();
        myClass(int x, int y);
        void set(int x, int y);
        void print() const;
        int compute(int x);
        bool equal();  
};

#endif
