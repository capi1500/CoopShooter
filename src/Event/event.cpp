//
// Created by capi1500 on 11/07/18.
//

#include "event.hpp"

Event::Event(){
}

Event::Event(std::string what, std::string object1Name, std::string object2Name, sf::Vector2f position) : what(what), object1(object1Name), object2(object2Name), position(position){
}