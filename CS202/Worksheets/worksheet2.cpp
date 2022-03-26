#include <iostream>

const int MAXEMPLOYEE = 5;

struct Employee{
    std::string name;
    int age;
    double salary;
    std::string department;
};

void setEmployeeData(Employee &employeeObj);
void printEmployeeData(Employee &employeeObj);
void testData(Employee employeelist[]);

int main(){
    Employee employeelist[MAXEMPLOYEE];
    testData(employeelist);

    return 0;
}

void setEmployeeData(Employee &employeeObj){
    std::cout << "Enter name: ";
    std::cin >> employeeObj.name;
    std::cout << "Enter age: ";
    std::cin >> employeeObj.age;
    std::cout << "Enter salary: ";
    std::cin >> employeeObj.salary;
    std::cout << "Enter department: ";
    std::cin >> employeeObj.department;
    std::cout << std::endl;
}

void printEmployeeData(Employee &employeeObj){
    std::cout << "Name: " << employeeObj.name << 
    "\nAge: " << employeeObj.age << 
    "\nSalary: " << employeeObj.salary <<
    "\nDepartment: " << employeeObj.department << "\n\n";
}

void testData(Employee employeelist[]){
    for(int i=0; i<MAXEMPLOYEE; i++){
        std::cout << "Enter Employee " << i+1 << " details:\n";
        setEmployeeData(employeelist[i]);
    }

    std::cout << "**Printing Employee Details**\n\n";
    for(int i=0; i<MAXEMPLOYEE; i++){
        std::cout << "Employee " << i+1 << std::endl;
        printEmployeeData(employeelist[i]);
    }
}
