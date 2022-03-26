#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "wages.h"

using namespace std;

// common function
/**
 * @brief
 *
 */
enum eStats
{
    FULLTIME,
    PARTTIME,
    CASUAL,
    NONE
};

/**
 * @brief
 *
 */
class employee
{
    string lastName, firstName;
    string employeeID;
    eStats employementStatus;
    bool checkID(string) const;

public:
    wages wagesObj;

    employee(string lst = "", string frst = "", double pyRt = 0.0,
             string rmpID = "", eStats es = NONE, double taxRt = 0.0);

    string getLastName() const;
    string getFirstName() const;
    double getPayRate() const;
    string getEmployeeID() const;
    eStats getEmploymentStatus() const;
    double getTaxRate() const;
    double getHoursWorked() const;
    void setEmployeeName(string lst, string frst);
    void setPayRate(double newPayRate);
    void setEmployeeID(string newID);
    void setEmploymentStatus(eStats newStat);
    void setTaxRate(double newRate);
    void setHoursWorked(double hrs);
    double grossPay() const;
    double takeHomePay() const;
    void showPayStub() const;
};

#endif // EMPLOYEE_H