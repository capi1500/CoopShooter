//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_OBJECT_HPP
#define COOPSHOOTER_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <src/Enum/enum.hpp>
#include <string>

class Game;

struct ObjectProperties{
	sf::Vector2f position;
	std::string name;
	std::string texture;
	
	virtual void PolymorficNothing(){}
	
	ObjectProperties getObjectProperties();
	
	ObjectProperties(sf::Vector2f, std::string, std::string);
	ObjectProperties();
};

class Object : public sf::Sprite{
	protected:
		Game& gameRef;
		ObjectProperties objectProperties;
		ObjectClass className;
		sf::Time localTime;
	public:
		const ObjectProperties& getObjectProperties() const;
		const ObjectClass getClassName() const;
		std::string getName();
		void setName(std::string name);
		
		sf::Vector2f getCentre();
		void setCentre(sf::Vector2f centre);
		void setCentre(float x, float y);
		void setTexture(std::string file);
		
		virtual void draw();
		virtual void pass(sf::Time);
		
		Object(Game&, ObjectProperties);
};

#endif //COOPSHOOTER_OBJECT_HPP
