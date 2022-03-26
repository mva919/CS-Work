/*
Name: Kishore Chidella, NSHE, CLASS-SECTION, ASSIGNMENT 2
Description: <Craps Game Simulation>
Input: <bet amount>
Output: <Game log for the game play>
*/

#ifndef CRAPSTYPE_H
#define CRAPSTYPE_H
#include <string>

using namespace std;

/**
 * @brief crapsType Class
 *
 */
class crapsType
{
public:
    crapsType();
    void readStake();
    int getStake() const;
    void setStake(int);
    int getCurrentBalance() const;
    void setDisplay(bool);
    bool playCraps(int);

private:
    int originalStake;
    int cashOnHand;
    bool display;
    int die1, die2;
    string nickName;
    static const int MINSTAKE = 50;
    static const int MAXSTAKE = 10000;
    static const int MINBET = 10;
    static const int MAXBET = 1000;
    void displayRoll(int die1, int die2);
};

#endif // CRAPSTYPE_H