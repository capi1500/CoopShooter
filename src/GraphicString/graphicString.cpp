//
// Created by capi1500 on 19/07/18.
//

#include <config.h>
#include "graphicString.hpp"
#include <src/Game/game.hpp>

void GraphicStringProperties::reset(){
	lines = 0;
	length.resize(0);
}

void GraphicString::updateStringProperties(){
	graphicStringProperties.reset();
	unsigned h = 0;
	for(auto i : text){
		if(i == '\n'){
			graphicStringProperties.lines++;
			graphicStringProperties.length.push_back(h);
			h = 0;
		}
		else{
			h++;
		}
	}
	if(text[text.size() - 1] != '\n'){
		graphicStringProperties.lines++;
		graphicStringProperties.length.push_back(h);
	}
}

void GraphicString::setCentre(sf::Vector2f centre){
	Object::setCentre(centre);
	startCentre = centre;
}

void GraphicString::draw(){
	unsigned h = 0;
	startCentre = getCentre();
	setCentre(getCentre());
	sf::Vector2f deltaMove = sf::Vector2f(static_cast<float>(gameRef.getGraphicAlphabet().getWidth()) * lettersScaling * getScale().x, static_cast<float>(gameRef.getGraphicAlphabet().getHeight()) * lettersScaling * getScale().y);
	move(sf::Vector2f(-deltaMove.x * graphicStringProperties.length[h] / 2, -deltaMove.y * graphicStringProperties.lines / 2));
	for(auto it = text.begin(); it != text.end(); it++){
		gameRef.getGraphicAlphabet().drawChar(*it, getCentre(), getScale(), color);
		if(*it == '\n'){
			h++;
			setPosition(sf::Vector2f(startCentre.x, getCentre().y));
			move(sf::Vector2f(-deltaMove.x * graphicStringProperties.length[h] / 2, deltaMove.y));
		}
		else{
			move(sf::Vector2f(deltaMove.x, 0));
		}
	}
	setPosition(startCentre);
}

sf::FloatRect GraphicString::getTextRect(){
	sf::FloatRect out;
	out.height = graphicStringProperties.lines * gameRef.getGraphicAlphabet().getHeight() * lettersScaling;
	for(auto i : graphicStringProperties.length){
		out.width = std::max(static_cast<unsigned>(out.width), i * gameRef.getGraphicAlphabet().getWidth()) * lettersScaling;
	}
	out.left = getCentre().x - out.width / 2;
	out.top = getCentre().y - out.height / 2;
	return out;
}

void GraphicString::setText(std::string text){
	this->text = text;
	updateStringProperties();
}

void GraphicString::setTextColor(sf::Color color){
	this->color = color;
}

GraphicString::GraphicString(Game& gameRef, ObjectProperties objectProperties) : Object(gameRef, objectProperties){
	this->color = sf::Color(255, 255, 255);
	className = ObjectClass::GraphicString;
	setText(objectProperties.name);
}