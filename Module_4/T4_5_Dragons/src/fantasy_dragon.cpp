#include "fantasy_dragon.hpp"

// Define FantasyDragon's methods here


void FantasyDragon::Eat(std::list<Food> &foodList) {
    for(auto i = foodList.begin(); i != foodList.end();){
        if(i->type == People or i->type == PeopleFood){
            size_ = size_ + 1;
            std::cout << "Fantasy dragon ate: ";
            std::cout << i->name << std::endl;
            //delete (*i);
            i = foodList.erase(i);
        }
        else i++;
    }
}

void FantasyDragon::Hoard(std::list<Treasure> &treasureList) {
    for(auto i = treasureList.begin(); i != treasureList.end();){
        if(i->type == Jewellery){
            treasures_.push_back(*i);
            std::cout << "Fantasy dragon received: ";
            std::cout << i->name << std::endl;
            i = treasureList.erase(i);
        }
        else i++;
    }
}
