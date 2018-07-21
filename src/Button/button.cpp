//
// Created by capi1500 on 21/07/18.
//

#include <src/Event/event.hpp>
#include <src/Game/game.hpp>
#include "button.hpp"

ButtonProperties::ButtonProperties(){
	isClicked = false;
}

ButtonProperties::ButtonProperties(ObjectProperties objectProperties, Event event, bool clicked) : onClick(event), isClicked(clicked), ObjectProperties(objectProperties){
}

void Button::onClick(){
	gameRef.getEventManager().addEvent(buttonProperties.onClick);
}

ButtonProperties& Button::getButtonProperties(){
	return buttonProperties;
}

void Button::pass(sf::Time elapsedTime){
	Label::pass(elapsedTime);
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(gameRef.getWindow()).x, sf::Mouse::getPosition(gameRef.getWindow()).y);
	if(localTime <= sf::milliseconds(100)){
		setTextColor(sf::Color(128, 128, 128));
	}
	else if(getGlobalBounds().contains(mousePos) or getTextRect().contains(mousePos)){
		setTextColor(sf::Color(127, 127, 127));
		if(not buttonProperties.isClicked){
			buttonProperties.isClicked = true;
		}
	}
	else{
		setTextColor(sf::Color(255, 255, 255));
		buttonProperties.isClicked = false;
	}
}

Button::Button(Game& gameRef, ButtonProperties buttonProperties) : Label(gameRef, buttonProperties.getObjectProperties()), buttonProperties(buttonProperties){
	localTime = sf::milliseconds(101);
	className = ObjectClass::Button;
}