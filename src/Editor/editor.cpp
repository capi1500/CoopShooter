//
// Created by capi1500 on 05/09/18.
//

#include <string>
#include <src/Object/object.hpp>
#include "editor.hpp"
#include <Game/game.hpp>

void Editor::draw(){
	Object object(gameRef, ObjectProperties(gameRef.coordToPixel(gameRef.pixelToCoord(sf::Vector2f(sf::Mouse::getPosition(gameRef.getWindow()).x, sf::Mouse::getPosition(gameRef.getWindow()).y))), std::string("DEBUG"), std::string("red")));
	object.setColor(sf::Color(255, 255, 255, 127));
	object.draw();
}

Editor::Editor(Game& game) : gameRef(game){

}