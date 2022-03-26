/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_3
Description: This is the employee class implementation, the employee
class has-a wages object as a public member. The employee class will
work as the base class for the manager class. This class has setters
and getters function to retrive and update data of the employee, it
calculates the employess gross pay and take home pay based on the 
employees taxes and pay rate which is stored in the wages object.
Input: This class does not take input directly from the user.
Output: The class prints error when invalid data has been passed to 
setter functions and it prints the employees stub showing all the 
employees information and pay break down. 
*/
#include "employee.h"

employee::employee(std::string lst, std::string frst, double pyRt, 
std::string rmpID, eStats es, double taxRT){
    //initialzing the name of employee
    lastName = lst;
    firstName = frst;
    wagesObj.setHoursWorked(0.0);
    /*checking that the pay rate and tax rate are positve and within the
    valid range*/
    if(pyRt >= 0 && pyRt <= wages::MAX_PAY_RATE)
        wagesObj.setPayData(pyRt);
    else //displaying error message
        std::cout << "Error:- invalid pay rate.\n";
    //checking if the taxrate is positive and less then max value
    if(taxRT >= 0 && taxRT <= wages::MAX_TAX_RATE) 
        wagesObj.setTaxRate(taxRT);
    else //displaying error message
        std::cout << "Error:- invalid tax rate.\n";
    //checking if the employee id is valid
    if(checkID(rmpID)) employeeID = rmpID;
    else //displaying error message for invalid id
        std::cout << "Error :- invalid employeeID\n";
    //setting employement status
    employementStatus = es;
}

//GETTER FUNCTIONS
//this get function returns the employee's last name
std::string employee::getLastName() const{ return lastName; }
//this get function returns the employee's first name
std::string employee::getFirstName() const{ return firstName; }
//this get function returns the employee's pay rate
double employee::getPayRate() const{ return wagesObj.getPayData(); }
//this get function returns the employee's ID
std::string employee::getEmployeeID() const{ return employeeID; }
//this get function returns the employee's employement status with enum
eStats employee::getEmploymentStatus() const{ return employementStatus;}
//this get function returns the employee's tax rate using wages object
double employee::getTaxRate() const{ return wagesObj.getTaxRate(); }
//this get function returns the employee's hours worked using wages obj
double employee::getHoursWorked() const{ 
    return wagesObj.getHoursWorked(); 
}

//SETTER FUNCTIONS
//this set functions sets the employee's first and last name
void employee::setEmployeeName(std::string lst, std::string frst){
    lastName = lst, firstName = frst;
}
//this set functions sets the employee's pay rate using wages object
void employee::setPayRate(double newPayRate){
    wagesObj.setPayData(newPayRate);
}
//this set functions sets the employee's ID
void employee::setEmployeeID(std::string newID){
    if(checkID(newID)) employeeID = newID;
    else //displaying error message for invalid id
        std::cout << "Error :- invalid employeeID\n";
}
//this set functions sets the employee's employement status using enum
void employee::setEmploymentStatus(eStats newStat){
    /*set the class variable to the passed enumeration value of 
    type sStats. No other values should be accepted*/
    employementStatus = newStat;
}
//this set functions sets the employee's tax rate using wages object
void employee::setTaxRate(double newRate){
    wagesObj.setTaxRate(newRate);
}
//this set functions sets the employee's hours worked using wages object
void employee::setHoursWorked(double hrs){
    wagesObj.setHoursWorked(hrs);
}

//this function returns the gross pay (hours worked * pay rate)
double employee::grossPay() const{ 
    const int MAX_HOURS_OVERTIME = 40;
    //for hours worked that are not considered overtime
    if(getHoursWorked() <= MAX_HOURS_OVERTIME)
        return getHoursWorked() * getPayRate();
    // if there are more than 40 hours worked
    else{
        //calculate the over time hours
        double overtimeHours = getHoursWorked() - MAX_HOURS_OVERTIME;
        /*adding the regular hours worked by the overtime hours which 
        are paid at half the pay rate*/
        return (getHoursWorked() * getPayRate()) + 
            (overtimeHours * (getPayRate() / 2));
    }
}

//this funciton calculates the final take home pay by subracting taxes
double employee::takeHomePay() const{
    //calculating the  medicare tax
    double medicareTax = grossPay() / 100 * wages::MEDICARE_TAX;
    //calculating the social sercurity tax
    double ssTax = grossPay() / 100 * wages::SOCIAL_SECURITY_TAX;
    //calculating the federal tax
    double federalTax = grossPay() / 100 * getTaxRate();
    //subracting all the taxes from the gross pay
    return grossPay() - (medicareTax + ssTax + federalTax);
}

/*this function prints a table of all the employee information including
the employee name, their employee status, the hours worked, the taxes,
and the final take home pay*/
void employee::showPayStub() const{
    //string array to get the enam name by enum value
    std::string eStatsName[] = {"FULLTIME", "PARTTIME", 
                                "CASUAL", "NONE"};
    //top line
    std::cout << '\n' << '-' << std::setw(70) << std::setfill('-') <<
    "-\n";
    //printing name and employement status
    std::cout << " Name: " << lastName << ", " << firstName <<
    std::setw(24) << std::setfill(' ') << "Status: " << 
    eStatsName[employementStatus] << std::endl;
    //printing the employee gross pay
    std::cout << " Employee Gross Pay:" << std::setw(14) <<
    std::setprecision(2) << std::fixed << grossPay() << std::endl;
    //printing hourse worked
    std::cout << " GetHoursWorked:" << std::setw(18) <<
    getHoursWorked() << std::endl;
    //printing withholding
    std::cout << ' ' << std::setw(15) << "Withholding" << std::endl;
    //printing medicare amount
    std::cout << ' ' << std::setw(18) << "Medicare:" << std::setw(16) <<
    (grossPay() / 100 * wages::MEDICARE_TAX) << std::endl;
    //printing social security amount
    std::cout << ' ' << std::setw(25) << "Social Security:" <<
    std::setw(9) << (grossPay() / 100 * wages::SOCIAL_SECURITY_TAX) <<
    std::endl;
    //printing federal tax amount
    std::cout << ' ' << std::setw(21) << "Federal Tax:" <<
    std::setw(13) << (grossPay() / 100 * getTaxRate()) << std::endl;
    //printing take home pay
    std::cout << ' ' << std::setw(18) << "Take Home Pay:" <<
    std::setw(16) << takeHomePay() << std::endl;
}

//private method of employee for checking if the id is valid or not
bool employee::checkID(std::string tmpID) const{
    //first character in ID must be an upper case letter
    if(!isalpha(tmpID[0]) || islower(tmpID[0])) return false;
    //the ID should then have exaclty 5 digits
    /*adding the 5 digits and the letter in the front the length of the
    id should not be more than 6*/
    if(tmpID.length() != 6) return false;
    for(int i=1; i<tmpID.length(); i++){
        if(!isdigit(tmpID[i])) return false;
    }
    //else it is a valid ID
    return true;
}
