/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_5
Description: This program has a chocolate box that contains various
types of chocolates. When a user inputs a seed value, the program will
proceed to fill out the box with random chocolates. The program will 
then pick out random spot from the chocolate box and dispalying special
messages depending on the type of chocolate it picked. The spot that was
picked will be eaten and the program will continue to pick another 
spot in the chocolate box. If the program picks a spot that has been
picked before, then the program ends. 
Input: This program takes in a seed value from the user as a command
line argument.
Output: This program outputs a quote from Forrest Gump and it also
outputs the special message each different type of chocolate has when 
the chocolates are selected from the box. If the user did not input
a seed value as a command line argument or if there are too many
arguments, the program will display an error showing a sample seed 
input.
*/
#include <iostream>

//the base or super class
class chocolate{
    public:
        virtual std::string whatamI() = 0; //pure virtual function
        virtual ~chocolate() = 0;//pure virtual destructor for codegrade
};

//derived classes that represents the different types of chocolates
//dark chocolate derived class
class dark: public chocolate{
    public:
        void feelBitter(){
            std::cout << "Dark Chocolate: oof that was bitter!\n";
        }
        std::string whatamI() { return "dark"; }
};
//milk chocolate dervied class
class milk: public chocolate{
    public:
        void feelSoft(){
            std::cout << "Milk Chocolate: " << 
            "Too soft, no chocolate taste!\n";
        }
        std::string whatamI() { return "milk"; }
};
//hazelnut chocolate dervied class
class hazelnut: public chocolate{
    public:
        void getAllergy(){
            std::cout << "Hazelnut Chocolate: I don't feel so good.\n"; 
        }
        std::string whatamI() { return "hazelnut"; }
};
//raspberry chocolate derived class
class raspberry: public chocolate{
    public:
        void telljoke(){
            std::cout << "Raspberry Chocolate: " << 
            "I don't always Raspberry, but when I do, I Raspberry Pi\n";
        }
        std::string whatamI() { return "raspberry"; }
};
//white chocolate derived class
class white: public chocolate{
    public:
        void feelScammed(){
            std::cout << "White Chocolate: " <<
            "Is this even real chocolate?\n"; 
        }
        std::string whatamI() { return "white"; }
};
//mint chocolate derived class
class mint: public chocolate{
    public:
        void feelInquisitive(){ 
            std::cout << "Mint Chocolate: Am I still eating chocolate" 
            << " or am I brushing my teeth?\n"; 
        }
        std::string whatamI() { return "mint"; }
};

class boxOfChocolates{
    public:
        //constructor
        boxOfChocolates(int length=6, int width=5);
        //destructor
        ~boxOfChocolates();
        void fillBox();
        bool takeChocolate();
    private:
        //allocate 2d array of pointers
        chocolate ***box;
        //variables to keep track of dimensions
        int boxLength;
        int boxWidth;
};

//boxOfChocolates parametrized constructor
boxOfChocolates::boxOfChocolates(int length, int width){
    boxLength = length;
    boxWidth = width;
    //creating a double pointer array type chocolate of size width
    box = new chocolate **[length];
    for(int i=0; i<length; i++)
        box[i] = new chocolate *[width]; //making an array for length
    //calling fill box to fill each box spot with a random chocolate
    fillBox();
}

//boxOfChocolates destructor
boxOfChocolates::~boxOfChocolates(){
    for(int i=0; i<boxLength; i++){
        for(int j=0; j<boxWidth; j++){
            // checking if the spot is not null before deleting
            if(box[i][j] != NULL) {
                delete box[i][j];
                box[i][j] = NULL;
            }
        }
        //deleting the pointer array
        delete [] box[i];
    }
    //deleting the double pointer array
    delete [] box;
    box = NULL;
}

//function to fill the box with different types of chocolates
void boxOfChocolates::fillBox(){
    //going over the entire box and filling it with chocolates
    for(int i=0; i<boxLength; i++)
        for(int j=0; j<boxWidth; j++){
            //using upcasting
            //using rand to randomly select a chocolate type
            switch (rand() % 6)
            {
            case 0:
                box[i][j] = new dark;
                break;
            case 1:
                box[i][j] = new milk;
                break;
            case 2:
                box[i][j] = new hazelnut;
                break;
            case 3:
                box[i][j] = new raspberry;
                break;
            case 4:
                box[i][j] = new white;
                break;
            case 5:
                box[i][j] = new mint;
                break;
            }
        }
}

/*function picks a random chocolate from the box and returns wheter the
the picked spot is empty or not*/
bool boxOfChocolates::takeChocolate(){
    //getting a random location in the box
    int length = rand() % boxLength;
    int width = rand() % boxWidth;

    //if the chocolate was been eaten already then we return false
    if(box[length][width] == NULL) return false;
    //using downcasting
    if(box[length][width]->whatamI() == "dark"){
        dark *temp = dynamic_cast<dark *>(box[length][width]);
        temp->feelBitter();
    }
    else if(box[length][width]->whatamI() ==  "milk"){
        milk *temp = dynamic_cast<milk *>(box[length][width]);
        temp->feelSoft();
    } 
    else if(box[length][width]->whatamI() == "hazelnut"){
        hazelnut *temp = dynamic_cast<hazelnut *>(box[length][width]);
        temp->getAllergy();
    } 
    else if(box[length][width]->whatamI() == "raspberry"){
        raspberry *temp = dynamic_cast<raspberry *>(box[length][width]);
        temp->telljoke();
    } 
    else if(box[length][width]->whatamI() == "white"){
        white *temp = dynamic_cast<white *>(box[length][width]);
        temp->feelScammed();
    } 
    else if(box[length][width]->whatamI() == "mint"){
        mint *temp = dynamic_cast<mint *>(box[length][width]);
        temp->feelInquisitive();
    } 
    //deallocating and setting it to null
    delete box[length][width];
    box[length][width] = NULL;
    //returning true if the chocolate was not null
    return true;
}

//pure virtual destructor for code grade clang tidy
chocolate::~chocolate(){}

int main(int argc, char *argv[]){
    //error message when a seed or invalid amount of arguments are given
    if(argc != 2){
        std::cout << "Enter Seed as argument: ./a.out 42\n";
        return 0;
    }
    //getting the  seed 
    int seed = 0;
    //string to store the input number
    std::string number = argv[1];
    /*interating over every char and taking the difference of ASCII
    codes to find the int digit*/
    for(int i=0; i<number.length(); i++)
        seed = (seed * 10) + (number[i] - '0');
    //setting the seed from the input value
    srand(seed);
    //displaying message
    std::cout << "\"My mom always said life was like a box" <<
    " of chocolates. You never know what you're gonna get.\"" <<
    "- Forrest Gump\n";
    //allocating box of chococlate objcet
    boxOfChocolates box;
    //iterating until false
    while(box.takeChocolate()){}
    //terminating program
    return 0;
}
