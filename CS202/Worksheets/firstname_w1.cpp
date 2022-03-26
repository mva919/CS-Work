#include <iostream>

int main(int argc, char *argv[]){

    //if argument count is greater or less than 3
    if(argc != 3){
        //priting error message
        std::cout << "Usage: ./a.out arg2 arg3\n";
        // quitting the program
        return 0;
    }

    std::string first = argv[1], second = argv[2];

    //if first arg is name and second arg is major then we pring john cse
    if((first == "name" || first == "NAME") && 
    (second == "major" || second == "MAJOR")){
        std::cout << "John CSE\n";
    }
    //ese we print an error
    else{
        std::cout << "Usage: ./a.out arg2 arg3\n";
    }
    
    return 0;
}
