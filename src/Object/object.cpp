//
// Created by capi1500 on 10/07/18.
//

#include "object.hpp"
#include <src/Game/game.hpp>

ObjectProperties::ObjectProperties(sf::Vector2f position, std::string name, std::string texture) : position(position), name(name), texture(texture){}

ObjectProperties::ObjectProperties(){}

ObjectProperties ObjectProperties::getObjectProperties(){
	return ObjectProperties(position, name, texture);
}

ObjectProperties& Object::getObjectProperties(){
	objectProperties.position = this->getPosition();
	return objectProperties;
}

const ObjectClass Object::getClassName() const{
	return className;
}

std::string Object::getName(){
	return objectProperties.name;
}

void Object::setName(std::string name){
	objectProperties.name = name;
}

sf::Vector2f Object::getCentre(){
	return getPosition() + sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}

void Object::setCentre(sf::Vector2f centre){
	setPosition(centre.x - getGlobalBounds().width / 2, centre.y - getGlobalBounds().height / 2);
}

void Object::setTexture(std::string file){
	objectProperties.texture = file;
	Sprite::setTexture(gameRef.getTextureManager().getTexture(objectProperties.texture));
}

void Object::setTexture(sf::Texture& texture){
	Sprite::setTexture(texture);
}

void Object::setCentre(float x, float y){
	setCentre(sf::Vector2f(x, y));
}

void Object::draw(){
	gameRef.getWindow().draw(*this);
}

void Object::pass(sf::Time elapsedTime){
	localTime += elapsedTime;
}

Object::Object(Game& game, ObjectProperties properties) : gameRef(game), objectProperties(properties){
	if(properties.texture != ""){
		setTexture(properties.texture);
	}
	setCentre(properties.position);
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	className = ObjectClass::Object;
}