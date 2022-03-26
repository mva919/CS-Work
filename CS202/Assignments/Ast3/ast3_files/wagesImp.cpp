/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_3
Description: This is the implementation for the wages class.This class
has crucial information for all employees includes tax rate, pay rate, 
and hours worked. Since the employee class will use composition with 
this class. This class will store and have features that concern the pay
of the employee and their taxes. The class has getters and setter 
functions to retrieve and update data.
Input: This class does not take direct input from the user. 
Output: This class only ouputs error messages for invalid paramaters
that were passed in to setter functions.
*/
#include "wages.h"

//wages class parametrized contructor to initialize valid values
wages::wages(double payRateTmp, double taxRateTmp, 
double hoursWorkedTmp){
    /*if there is an invalid value given the varibable stays unchaged
    since it intialized to 0 in the header file*/
    //checking if the payrate is positive and less then max value
    if(payRateTmp >= 0 && payRateTmp <= MAX_PAY_RATE) 
        payRate = payRateTmp;
    else //displaying error message
       std::cout << "Error:- invalid pay rate.\n";
    //checking if the taxrate is positive and less then max value
    if(taxRateTmp >= 0 && taxRateTmp <= MAX_TAX_RATE) 
        taxRate = taxRateTmp;
    else //displaying error message
        std::cout << "Error:- invalid tax rate.\n";
    //checking if the hoursworked is positivee and less then max value
    if(hoursWorkedTmp >= 0 && hoursWorkedTmp <= MAX_HOURS) 
        hoursWorked = hoursWorkedTmp;
    else //displaying error message
        std::cout << "Error:- invalid Hours worked.\n";
}

//GETTER FUNCTIONS
//this getter function returns the pay rate
double wages::getPayData() const{ return payRate; }
//this getter function returns the tax rate
double wages::getTaxRate() const{ return taxRate; }
//this getter function returns the hours worked
double wages::getHoursWorked() const{ return hoursWorked; }

//SETTER FUNCTIONS
//this setter functions sets the pay rate if it's valid
void wages::setPayData(double payRateTmp){
    //checking if the payrate is positive and less then max value
    if(payRateTmp >= 0 && payRateTmp <= MAX_PAY_RATE) 
        payRate = payRateTmp;
    else //displaying error message
        std::cout << "Error:- invalid pay rate.\n";
}
//this setter function sets the tax rate if it's valid
void wages::setTaxRate(double taxRateTmp){
    //checking if the taxrate is positive and less then max value
    if(taxRateTmp >= 0 && taxRateTmp <= MAX_TAX_RATE) 
        taxRate = taxRateTmp;
    else //displaying error message
        std::cout << "Error:- invalid tax rate.\n";
}
//this setter function sets the hours work if it's valid
void wages::setHoursWorked(double hoursWorkedTmp){
    //checking if the hoursworked is positivee and less then max value
    if(hoursWorkedTmp >= 0 && hoursWorkedTmp <= MAX_HOURS)
        hoursWorked = hoursWorkedTmp;
    else //displaying error message
        std::cout << "Error:- invalid Hours worked.\n";
}
