/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_4
Description: This program similuates a battle in Star Wars and uses
various classes to similaute it. The first base class is the entity
class which the infantry, armor, and artillary class are derived from.
The next is the point type class which holds all of the differnt types
of entities in a single spot in the battefield. The map type class has
a point type 2d array to represent the battlefield. There are also
two attack function which allows artillery to fire at a specific spot 
and the other allows armory to move from one spot to the other.
Input: This funciton does not take direct input from the user, there are
only function calls.
Output: This function prints the battlefield in a board format. It 
prints messages when there is no armor or artillery available when 
trying to attack a spot. It also shows when an armory is destroyed.
When a point is fired at, all the squads in that point are deleted
and it prints outs all the squads that were contained in that single 
point. 
*/
#include<iostream>
#include <cstdlib>
using namespace std;

//Superclass, keeps track of name 
class ent_t {
  public:
    ent_t(string n = "None") : id(ent_cnt++) {
        name = new string;
        *name = n;
    }
     //Destructor
    ~ent_t(){
        //checking if the name pointer is null before deleting
        if(name != NULL){
            delete name;
            name = NULL;
        }
    }
    ent_t(const ent_t &old){ //Copy Constructor
        /*allocating space for a new string and setting it to the old
        ent_t name value*/
        name = new string;
        *name = *(old.name);
        id = ent_cnt++; //don't copy old id, just keep increasing it.
    }
    //setter function
    void setName(string n){ *name = n; }
    //getter function to return name value
    string getName() const{ return *name; }
    int getID() const {return id;}
  protected:
    string *name;
    int id;
    static int ent_cnt;
};

int ent_t::ent_cnt = 0; //initialize static

class infantrySquad_t : public ent_t {
  public:
    infantrySquad_t(string name = "Infantry Squad") : ent_t(name){}
};

class armorSquad_t : public ent_t {
  public:
    armorSquad_t(string name = "Armor Squad") : ent_t(name) {}
};

class artillerySquad_t : public ent_t {
  public:
    artillerySquad_t(string name = "Artillery Squad") : ent_t(name) {}
};

//Class to represent each point on the map and what it holds. 
//Can hold up to 1 armor and artillery squad,
//but can also hold a variable amount of infantry squads (dynamic array)
class point_t {
  public:
    point_t(int x = 0, int y = 0) : 
    arm(NULL), art(NULL), inf(NULL), x(x), y(y) {}
    //Cleanup all the pointers. also de-allocate the inf array
    ~point_t() { 
        //deallocationg the single pointers
        if(arm != NULL){
            delete arm;
            arm = NULL;
        }
        if(art != NULL){
            delete art; 
            art = NULL;
        }
        if(inf != NULL){
            /*creating a temp double pointer and assign it the value at 
            inf*/
            infantrySquad_t** temp = inf;
            /*iteration over the inf pointer array and deleting each 
            pointer*/
            while(*temp != NULL){
                delete *temp;
                //incrementing temp to the next index
                temp++;
            }
            //deallocating the acutal 2d array
            delete [] inf; 
            //setting the pointer to null
            inf = NULL;
        }
    }
    void print(){
        cout << "Point (" << x << ", " << y << ") contains:\n";
        if(arm != NULL) cout << arm->getName() << endl;
        if(art != NULL) cout << art->getName() << endl;
        if(inf != NULL){
            /*loop to print the array. 
            The inf array MUST be null terminated or this breaks!*/
            infantrySquad_t** temp = inf;
            while(*temp != NULL){
                cout << (*temp)->getName() << ", ";
                temp++;
            } 
        }
    }
    char getChar(){
        /* getting the character depeing on what type of infantry is in 
        the point*/
        if(arm == NULL && art == NULL && inf == NULL) return '0';
        if(arm == NULL && art == NULL && inf != NULL) return 'I';
        if(arm == NULL && art != NULL && inf == NULL) return 'A';
        if(arm == NULL && art != NULL && inf != NULL) return 'D';
        if(arm != NULL && art == NULL && inf == NULL) return 'T';
        if(arm != NULL && art == NULL && inf != NULL) return 'C';
        if(arm != NULL && art != NULL && inf == NULL) return 'B';
        if(arm != NULL && art != NULL && inf != NULL) return '!';
        return ' ';
    }
    string getInfantryCount(){
        /*if the infantry pointer is null that means there are no 
        infantry at this point*/
        if(inf == NULL) return "  ";
        int count = 0;
        infantrySquad_t **temp = inf;
        /*iterating over every index in the infantry pointer array and
        counting how many pointers there are that are not pointing to 
        null*/
        while(*temp != NULL){
            count++;
            temp++;
        }
        return to_string(count);
    }
    armorSquad_t*     arm;
    artillerySquad_t* art;
    infantrySquad_t** inf;
    int x;
    int y;
};

//Holds map, adds and removes entities
class map_t {
  public:
    map_t(int x = 10, int y = 9) : x(x), y(y) {
        point = new point_t*[y];
        for(int i=0; i<y; i++)
            point[i] = new point_t[x];
        //setting the points values of x and y for each point
        for(int i=0; i<y; i++){
            for(int j=0; j<x; j++){
                point[i][j].x = j;
                point[i][j].y = i;
            }
        }
        loadData();
    }
    ~map_t(){ //cleanup
        for(int i=0; i<y; i++)
            delete [] point[i];
        
        delete [] point;
        point = NULL;
    }
    void draw();
    void attackMove(point_t* origin, point_t* dest){
        if(origin->arm == NULL) cout << "No armor available.\n";
        else{
            cout << origin->arm->getName() << " moving to (" <<
            dest->x << ", " << dest->y << ")\n";
            /*If there is existing armor in the destination point’s 
            location then it will be de-allocated and a print message
            will show that it was destroyed*/
            if(dest->arm != NULL){
                cout << "Destroyed " << dest->arm->getName() << endl;
                delete dest->arm;
            }
            dest->arm = origin->arm;
            //delete origin->arm;
            origin->arm = NULL;
        }
    }
    //Fires at a point, destroys everything there.
    void fireAt(point_t *origin, point_t *target){
        //if there is no artillery at the origin we don't do anything
        if(origin->art == NULL){
            cout << "No artillery available\n";
            return;
        }
        cout << origin->art->getName() << " fires at (" <<
        target->x << ", " << target->y << ")!!!\n";
        //showing what is contained at the point
        target->print();
        cout << "All units destroyed!\n";
        //deallocating all the units at the target points
        target->~point_t();
    }
    void addInfantry(point_t* location, int amount,
                     const string &n = "501st Infantry Squad "){
                          //add + 1 for the null spot
        if(location->inf == NULL){
            //Creating an array of new size
            location->inf = new infantrySquad_t*[amount+1];
            //setting the values for the array
            for(int i=0; i<amount; i++)
                location->inf[i]=new infantrySquad_t(n+to_string(i+1));
            //setting the last pointer to NULL
            location->inf[amount] = NULL;
        }
        else{ //deep copy practice
            //counting how big the array is
            int count = 0;
            infantrySquad_t** ptr = location->inf;
            /*going over the infantry array and counting the length of
            it*/
            while(*ptr != NULL){
                count++;
                ptr++;
            }
            //the new size is the current size plus the added amount
            int newCount = count + amount + 1;
            //creating a new temporary array of new size
            infantrySquad_t** temp = new infantrySquad_t*[newCount];
            /*copying old values with the values and not address since 
            it would be shallow copy if we just assinged it normally*/
            for(int i=0; i<count; i++)
                temp[i] = new infantrySquad_t(*(location->inf[i]));
            //adding new values
            for(int i=count; i<newCount-1; i++)
                temp[i] = new infantrySquad_t(n + to_string(i+1));
            //making last spot to null
            temp[newCount-1] = NULL;
            //deleting the old array
            //using for loop since we removed the null spot
            for(int i=0; i<count+1; i++)
                delete location->inf[i];
            delete [] location->inf;
            //assigning the inf to the temp array
            location->inf = temp;
            //making the temp pointer to null
            temp = NULL;
        }
    }
    point_t** point;
  private:
    void loadData();
    int x;
    int y;
};

void map_t::draw(){
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++)
            cout << point[i][j].getChar() <<
            point[i][j].getInfantryCount() << " ";
        cout << endl;
    }
    cout << endl;
}

void map_t::loadData(){
    cout << "The First Order is the best order..." << endl;
}

int main(int argc, char *argv[]) {
    map_t *Crait = new map_t;
    //The First Order
    Crait->addInfantry(&Crait->point[2][8], 13, "Stormtrooper Squads");
    Crait->addInfantry(&Crait->point[2][6], 22, "Stormtrooper Squads");
    Crait->point[1][7].arm = new armorSquad_t("AT-ATs");
    Crait->point[1][5].arm = new armorSquad_t("AT-ATs");
    Crait->point[8][6].arm = new armorSquad_t("AT-ATs");
    Crait->addInfantry(&Crait->point[8][6], 11, "Stormtrooper Squads");
    Crait->point[4][8].art = new artillerySquad_t("AT-MA");
    Crait->point[6][8].art = new artillerySquad_t("AT-MA");
    Crait->point[6][8].arm = new armorSquad_t("AT-ATs");
    Crait->addInfantry(&Crait->point[6][8], 11,
    "Kylo Ren's Private Army");
    Crait->addInfantry(&Crait->point[7][8], 33, "Stormtrooper Squads");
    Crait->point[7][8].art = new artillerySquad_t("AT-MA");
     //MOAARRR
    Crait->addInfantry(&Crait->point[8][6], 14, "Stormtrooper Squads");
    //The Resitance
    Crait->point[6][2].art = new artillerySquad_t();
    Crait->point[6][2].arm = new armorSquad_t();
    Crait->point[4][2].arm = new armorSquad_t("Speeders");
    Crait->addInfantry(&Crait->point[5][3], 22, "The Resistance");
    Crait->point[1][4].arm = new armorSquad_t("Speeders");
    Crait->point[2][3].art = new artillerySquad_t("Damaged Artillery");
    Crait->point[2][3].arm = 
    new armorSquad_t("Some rusty tanks acting as decoys");
    Crait->addInfantry(&Crait->point[2][3],12,
    "Decoy Resistance Soldiers");
    Crait->draw();
    //The Action!
    Crait->attackMove(&Crait->point[2][4], &Crait->point[1][5]);
    Crait->attackMove(&Crait->point[1][4], &Crait->point[1][5]);
    Crait->fireAt(&Crait->point[4][8], &Crait->point[2][3]);
    Crait->draw();
    delete Crait; //lol
    return 0;
}
