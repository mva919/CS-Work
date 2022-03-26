/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_2
Description: This program implements the crapsType class. The program
reads an input stake and input bet and validates in they are both in
range of the minimum and maximum values. It sets which display mode
the user wants and then it proceeds to play the game until the player 
wins or loses. The play craps function will only play one round at a 
time and it will show the nicknames of each roll if the display mode
is on. When the player wins or loses the cash on hand is either 
incremented or decremented based on the input bet.
Input: This program takes a stake amount and a bet ammount as inputs.
Output: This program has two modes, one that is display mode which 
shows all the rolls and player points and displays the current balance
when a player wins. It also has the without display mode which does not
show anything to the user.
*/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "crapsType.h"

/* Default constructore for the crapsType class, the contrcutor will
initialzie all interger values to zero and it will set display to 
true by default, the user can change that value later if they wish*/
crapsType::crapsType(){
    originalStake = 0;
    cashOnHand = 0;
    display = true;
    die1 = 0;
    die2 = 0;
}

/*This function reads the stake amount and checks that it is between
the minimum and MaxStake, if the stake is out of bounds it prompts 
the user again for input*/
void crapsType::readStake(){
    int inputStake;
    do{
        std::cout << "Enter Stake Amount: ";
        std::cin >> inputStake;
        if(inputStake <= MINSTAKE || inputStake >= MAXSTAKE){
            std::cout << "Error, invalid entry.Must be between " <<
            MINSTAKE << "and " << MAXSTAKE << 
            "inclusive.\nPlease re-enter.\n";
        }
    } while (inputStake <= MINSTAKE || inputStake >= MAXSTAKE);
    setStake(inputStake);
}

/*This function verifies that the input stake is between the Minimum and
Maximum stake, and sets cash on hand and original stake to the input
stake if a valid stake is given*/ 
void crapsType::setStake(int inputStake){
    if(inputStake <= MINSTAKE || inputStake >= MAXSTAKE) 
        std::cout << "Error, Invalid Stake Amount\n";
    else{
        /*If the value is valid, the 
        originalStake and cashOnHand variables should be set.*/
        cashOnHand = inputStake;
        originalStake = inputStake;
    }
}

//this function retursn teh orginial stake
int crapsType::getStake() const{ return originalStake; }

//This function returns the cash on hand
int crapsType::getCurrentBalance() const{ return cashOnHand; }

//This functiuon sets the display status for the game
void crapsType::setDisplay(bool status){ display = status; }

//This function acts as the main driver for the game
bool crapsType::playCraps(int inputBet){
    //verifies is the input bet is in between the range of valid bet
    if(inputBet < MINBET || inputBet > MAXBET){
        std::cout << "Error, Invalid Bet\n";
        return false;
    }
    //rolling the dices
    die1 = rand() % 6 + 1;
    die2 = rand() % 6 + 1;
    int diceSum = die1 + die2;
    /*If the game is displayed, each roll 
    (die1, die2, sum, and nickname) should be displayed. */
    if(display) displayRoll(die1, die2);
    //If the sum is 7 or 11 on the first throw, it is a “win”
    if(diceSum == 7 || diceSum == 11){
        //win
        cashOnHand += inputBet;
        return true;
    }
    /*If the sum is 2, 3, or 12 (called “craps”) on the first throw, 
    it is a loss*/
    else if(diceSum == 2 || diceSum == 3 || diceSum == 12){
        //loss
        cashOnHand -= inputBet;
        return false;
    }
    /*If the sum is 4, 5, 6, 8, 9, or 10 that becomes the players 
    “point”.*/
    else if(diceSum != 7 && diceSum >= 4 && diceSum <= 10){
        //setting the player points as the diceSum
        int playerPoints = diceSum;
        /*If user has display turned on we need to show the points
        that need to be rolled*/
        if(display) std::cout << "Point: " << playerPoints << '\n';
        
        do{
            //rolling the dice
            die1 = rand() % 6 + 1;
            die2 = rand() % 6 + 1;
            /*if the player has displayed turned on we will show 
            each roll that the program took*/
            if(display) displayRoll(die1, die2);
            diceSum = die1 + die2;
            /*if the sum of both dice is 7 while trying to make points
            the player will lose*/
            if(diceSum == 7){
                cashOnHand -= inputBet;
                /*if the user has display on then we show a message
                when they lose*/
                if(display) std::cout << "Loss";
                return false;
            }
            if(diceSum == playerPoints){
                cashOnHand += inputBet;
                /*if user has displayed turned on we show the balance
                and a message showing the user won*/
                if(display){
                    std::cout << "Won\n";
                    std::cout << "Current Balance: $" <<
                    getCurrentBalance() << std::endl;
                    std::cout << "---------------------------\n";
                }
                return true;
            }
        /*To win, the player continues to roll dice until he/she 
        “makes point” (i.e., rolls the same point value).*/
        } while (diceSum != playerPoints);
    }   
    //return false as a placeholder
    cashOnHand -= inputBet;
    return false;
}

/*This function displayst he value of dice 1 and dice 2 and it displays
the sum of both the dice as well as the nickname*/
void crapsType::displayRoll(int die1, int die2){
    //checking for special case nicknames
    if(die1 == 1 && die2 == 1) nickName = "Snake Eyes";
    if(die1 == 6 && die2 == 6) nickName = "Boxcars";
    //checking for nicknames when the dices are equal to each other
    else if(die1 == die2){
        switch (die1+die2){
        case 4:
            nickName = "Hard Four";
            break;
        case 6:
            nickName = "Hard Six";
            break;
        case 8:
            nickName = "Hard Eight";
            break;
        case 10:
            nickName = "Hard Ten";
            break;
        }
    } 
    //checking all other possibilites of nicknames
    else{
        switch (die1 + die2) {
        case 3:
            nickName = "Ace Deuce";
            break;
        case 4:
            nickName = "Easy Four";
            break;
        case 5:
            nickName = "Fever Five";
            break;
        case 6:
            nickName = "Easy Six";
            break;
        case 7:
            nickName = "Seven Out";
            break;
        case 8:
            nickName = "Easy Eight";
            break;
        case 9:
            nickName = "Nina";
            break;
        case 10:
            nickName = "Easy Ten";
            break;
        case 11:
            nickName = "Yo-Eleven";
            break;
        }
    }
    /*displayin the roll with the value of each dice, the sum of the
    two dice and the nickname that was calculated for the sum*/
    std::cout << "Die 1: " << die1 << std::setw(5) <<
    std::setfill(' ') << 'D' << "ie 2: " << die2 << std::setw(5) <<
    'S' << "um: " << die1 + die2 << "    " << nickName << std::endl;
}
