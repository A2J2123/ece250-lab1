// include libraries here (STL not allowed)
//./game.out < inputs/gigantica.in
#include <iostream>
#include <string>
#include "game.h"


int main(){

    game g{};

    std::string command{};
    double x{};
    double y{};

    while(true){
        std::cin >> command;
        if(command=="SPAWN"){ //spawning a player
            std::cin >> x;
            std::cin >> y;
            if(x<=0 || y<=0){ //if x, y coordinates are invalid, print failure and don't spawn player
                std::cout << "failure" <<std::endl;
            }else{ //if x, y coordinates are valid, print success and spawn a player node in linked list
                g.spawn(x, y);
                std::cout << "success" << std::endl;
            }
        }else if(command=="TIME"){ //allowing time to pass
            std::cin >> x;
            g.time(x); //calls game function time with value x
        }else if(command=="LUNCH"){ 
            g.lunch(); //calls game function lunch
        }else if(command=="NUM"){
            g.num(); //get number of players and prints it
        }else if(command=="PRT"){
            std::cin >> x; 
            g.prt(x); //calls game funciton prt
        }else if(command == "OVER"){
            g.over();
            break;
        }
    }
    return 0;
}