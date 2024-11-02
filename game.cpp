#include <iostream>
#include <string>
#include <cmath>
#include "game.h"



/*player functions*/
//initializes player node
player::player(double set_x, double set_y, player *set_next_player): x{set_x}, y{set_y}, next_player{set_next_player} {
}

//moves player and changes coordinates according to lab document
void player::move(double t){
    double newX = x - t * cos(atan2(y,x));
    double newY = y - t * sin(atan2(y,x)); 
    x = newX;
    y = newY;
}

//returns x coordinate
double player::get_x(){
    return x;
}

//returns y coordinate
double player::get_y(){
    return y;
}

//returns next player node
player* player::get_next(){
    return next_player;
}

//sets the next player node to input
void player::set_next(player *set_next_player){
    next_player = set_next_player;
}


/*game functions*/
//initializes game linked list
game::game():player_head{nullptr}{
}

//decontructs game linked list
game::~game(){
    while (player_head != nullptr){ //interates through linked list and deletes each node
        player* temp = player_head;
        player_head = player_head->get_next();
        delete temp;
        num_players--;
    }
}

//creates a new player node with given coordinates
void game::spawn(double new_x, double new_y){
    player_head = new player{new_x, new_y, player_head};
    num_players++; //increases number of players by 1
}

//interates through each player node and moves them by time t
void game::time(double t){
    player* current = player_head;
    while (current !=nullptr) {
        current->move(t);
        current= current->get_next();
    }

    //after moving each character, any players with negative x or y coordinates are deleted
    //deletes any head nodes that need to be deleted and sets the new head
    while (player_head != nullptr && (player_head->get_x()<0 || player_head->get_y()<0)){
        player* temp = player_head;
        player_head = player_head->get_next();
        delete temp;
        num_players--; //reduces number of players by 1
    }

    current = player_head;
    //iterates through each node after to see if they need to be deleted
    while (current !=nullptr) {
        //after deleting current and setting the new current, checks if new current needs to be deleted
       while(current->get_next() != nullptr && (current->get_next()->get_x()<0 || current->get_next()->get_y()<0)){
            player* temp = current->get_next();
            current->set_next(current->get_next()->get_next());
            delete temp;
            num_players--; //reduces number of players by 1
       }
       current = current->get_next();
    }

    num(); //prints number of player left
}

//interates through each player node and deletes them if distance is less than one
void game::lunch(){
    //deletes any head nodes that need to be deleted and sets the new head
    while (player_head != nullptr && (sqrt(pow(player_head->get_x(),2) + pow(player_head->get_y(),2)))<1){
        player* temp = player_head;
        player_head = player_head->get_next();
        delete temp;
        num_players--; //reduces number of players by 1
    }

    player* current = player_head;
    //iterates through each node after to see if they need to be deleted
    while (current != nullptr) {
        //after deleting current and setting the new current, checks if new current needs to be deleted
       while(current->get_next() != nullptr && (sqrt(pow(current->get_next()->get_x(),2) + pow(current->get_next()->get_y(),2)))<1){
            player* temp = current->get_next();
            current->set_next(current->get_next()->get_next());
            delete temp;
            num_players--; //reduces number of players by 1
       }
       current = current->get_next();
    }

    num(); //prints number of player left
}

//prints number of player left
void game::num(){
    std::cout << "num of players: " << num_players << std::endl;
}

//prints the coordinates of players with distance less than the given distance
void game::prt(double d){
    player* current = player_head;
    bool found = false;
    while (current != nullptr) { //iterates through linked list
        double distance = sqrt(pow(current->get_x(), 2) + pow(current->get_y(), 2)); //calculates distance given x, y coordinates
        if(distance < d) {//checks if distance is less than given d
            std::cout << current->get_x() << " " << current->get_y() << " "; //prints coordinates
            found = true; //if even a single player found with distance<d don't print no players found
        }
        current = current->get_next();
    }
    if(!found) { //if no player within distance d were found, then print no players found
        std::cout << "no players found";
    }
    std::cout << std::endl;
}

//once the game is over, the winner is printed
void game::over(){
    if(num_players<=0){ //If no players are left, the wolf wins
        std::cout << "wolf wins" << std::endl;
    }else{ //If there are one or more players, the players win
        std::cout << "players wins" << std::endl;
    }
}