#include <iostream>

const int MAXEMPLOYEE = 2;

class Employee{
    public:
        Employee(); //default constructor
        ~Employee(); //destructor
        void setEmployeeData();
        void printEmployeeData() const; //getter
    private:
        std::string name;
        int age;
        double salary;
        std::string department;
};

//funtion to test class decleration
void classTest(Employee employeelist[]);

int main(){
    Employee employeelist[MAXEMPLOYEE];
    classTest(employeelist);

    return 0;
}

//function definitions
void Employee::setEmployeeData(){
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << "Enter salary: ";
    std::cin >> salary;
    std::cout << "Enter department: ";
    std::cin >> department;
}

void Employee::printEmployeeData() const{
    std::cout << "Name: " << name << "\nAge: " << age << "\nSalary: " <<
    salary << "\nDepartment: " << department << std::endl;
}

//funtion to test class definition
void classTest(Employee employeelist[]){
    for(int i=0; i<MAXEMPLOYEE; i++){
        std::cout << "\nEnter Employee " << i+1 << " details:\n";
        employeelist[i].setEmployeeData();
    }

    for(int i=0; i<MAXEMPLOYEE; i++){
        std::cout << "\n**Printing Employee Details**\n";
        std::cout << "Employee " << i+1 << std::endl;
        employeelist[i].printEmployeeData();
    }
}

Employee::Employee(){}
Employee::~Employee(){}
