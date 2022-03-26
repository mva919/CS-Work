/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_3
Description: This is the implementation for the manager class, this 
class is a derived class from employee using public inheritance. This
has all the functionality of the employee with some added features.
This class has a bonus percentage that is unique to managers, and it
is calcluated based on a 40 hour work week. The class calculates the
managers bonus pays and how much taxes are set on the bonus pay.
Input: This class does not take direct input from the user. 
Output: This class has the same output as the employee class in addition
to the bonus pay stub which is printed in red. This class also prints
error messages for invalid paramaters in setter functions. 
*/
#include "manager.h"
#include <cmath>

//manager parametrized constructor to initialize values
manager::manager(std::string frst, std::string lst, double pyRt, 
std::string rmpID, eStats es, double taxRT, double bonus) : 
employee(frst, lst, pyRt, rmpID, es, taxRT) {    
    //checking if the bonus is postive and not greater than max
    if(bonus >= 0 && bonus <= MAX_BONUS_PCT) bonusPercentage = bonus;
    else //displaying error message
        std::cout << "Error:- invalid bonus percentage.\n";
}

//this function returns the managers gross pay
double manager::grossPay() const{
    /*The gross pay for a manager is based on a 40 hours work week 
    even if the manager worked less than or more than 40 hours*/
    const int MANGER_WORK_WEEK = 40;
    //if on hours worked we return 0
    if(employee::getHoursWorked() == 0) return 0.0;
    //we calcuate based on the manager work week
    else
        return MANGER_WORK_WEEK * employee::getPayRate();
}

//this function returns the bonus pay
double manager::bonusPay() const{
    //returns the pay rate of the manager
    return employee::getPayRate();
}

//SETTER FUNCTIONS
//this function sets the hours worked for the manager
void manager::setHoursWorked(double hours){
    employee::setHoursWorked(hours);
}
//this function sets the bonus percentage
void manager::setBonusPct(double bonus){
    //checking if the percentage is positive and not greater than limit
    if(bonus >= 0 && bonus <= MAX_BONUS_PCT) bonusPercentage = bonus;
    else //displaying error message
        std::cout << "Error:- invalid bonus percentage.\n";
} 

//GETTER FUNCTION
//this function gets the current bonus percentage
double manager::getBonusPct() const{ return bonusPercentage; }

//this function shows the manager pay stub
void manager::showPayStub() const{
    double mediTax=grossPay() / 100 * wages::MEDICARE_TAX, 
    SSTax=grossPay() / 100 * wages::SOCIAL_SECURITY_TAX, 
    FedTax=grossPay() / 100 * employee::getTaxRate();
    //calling the employee function to get employee pay stub table
    //string array to get the enam name by enum value
    std::string eStatsName[] = {"FULLTIME", "PARTTIME", 
                                "CASUAL", "NONE"};
    //top line
    std::cout << '\n' << '-' << std::setw(70) << std::setfill('-') <<
    "-\n";
    //printing name and employement status
    std::cout << " Name: " << employee::getLastName() << ", " <<
    employee::getFirstName() << std::setw(24) << std::setfill(' ') <<
    "Status: " << eStatsName[employee::getEmploymentStatus()] << 
    std::endl;
    //printing the employee gross pay
    std::cout << " Manager Gross Pay:" << std::setw(15) <<
    std::setprecision(2) << std::fixed << grossPay() << std::endl;
    //printing hourse worked
    std::cout << " GetHoursWorked:" << std::setw(18) <<
    getHoursWorked() << std::endl;
    //printing withholding
    std::cout << ' ' << std::setw(15) << "Withholding" << std::endl;
    //printing medicare amount
    std::cout << ' ' << std::setw(18) << "Medicare:" << std::setw(16) <<
    mediTax << std::endl;
    //printing social security amount
    std::cout << ' ' << std::setw(25) << "Social Security:" <<
    std::setw(9) << SSTax << std::endl;
    //printing federal tax amount
    std::cout << ' ' << std::setw(21) << "Federal Tax:" <<
    std::setw(13) << FedTax << std::endl;
    //printing take home pay
    std::cout << ' ' << std::setw(18) << "Take Home Pay:" <<
    std::setw(16) << std::round((grossPay() - (mediTax + SSTax + FedTax))
    * 100) / 100.0 << std::endl;
    //displaying bonus amount
    std::cout << " Bonus Amount:" << std::setw(12) <<
    grossPay() * (bonusPercentage / 100) << std::endl;
    //displaying witholding
    std::cout << std::setw(17) << "Withholding\n";
    //displaying federal tax
    std::cout << std::setw(24) << "Federal Tax:" << std::setw(19) <<
    (grossPay() * (bonusPercentage / 100)) * (BONUS_TAX_RATE / 100) <<
    std::endl;
    //displaying Bonus check amount
    std::cout << std::setw(31) << "Bonus Check Amount:" <<
    std::setw(12) << (grossPay() * (bonusPercentage / 100)) - 
    ((grossPay() * (bonusPercentage / 100)) * (BONUS_TAX_RATE / 100))
    << std::endl;
}
