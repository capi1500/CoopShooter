//
// Created by capi1500 on 19/07/18.
//

#include <src/Game/game.hpp>
#include <src/Button/button.hpp>
#include "menu.hpp"

MenuProperties::MenuProperties(){
	gameRunning = false;
	gameDraw = false;
	opacity = 0.f;
	splitScreen = false;
	menuHeight = 0;
}

MenuProperties::MenuProperties(const MenuProperties& menuProperties){
	gameRunning = menuProperties.gameRunning;
	opacity = menuProperties.opacity;
	splitScreen = menuProperties.splitScreen;
	menuHeight = menuProperties.menuHeight;
	gameDraw = menuProperties.gameDraw;
	labels = menuProperties.labels;
}

MenuProperties& Menu::getMenuProperties(){
	return menuProperties;
}

void MenuProperties::addLabel(Label* label){
	labels.push_back(label);
	menuHeight += std::max(label->getGlobalBounds().height, label->getTextRect().height);
}

void Menu::addLabel(Label* label){
	menuProperties.addLabel(label);
}

void Menu::draw(){
	sf::Vector2f center = getCentre();
	center.y -= menuProperties.menuHeight / 2;
	Object::draw();
	for(auto i : menuProperties.labels){
		i->setCentre(center);
		i->draw();
		center += sf::Vector2f(0, std::max(i->getGlobalBounds().height, i->getTextRect().height));
	}
}

void Menu::pass(sf::Time elapsedTime){
	for(auto i : menuProperties.labels){
		i->pass(elapsedTime);
	}
}

void Menu::mouseClicked(sf::Vector2f mousePos){
	for(auto i : menuProperties.labels){
		if(i->getClassName() == ObjectClass::Button){
			if(i->getGlobalBounds().contains(mousePos) or i->getTextRect().contains(mousePos)){
				dynamic_cast<Button*>(i)->onClick();
			}
		}
	}
}

Menu::Menu(Game& game, MenuProperties menuProperties) : Object(gameRef, menuProperties.getObjectProperties()){
}