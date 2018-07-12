//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_PHYSICOBJECT_HPP
#define COOPSHOOTER_PHYSICOBJECT_HPP

#include <src/Enum/enum.hpp>
#include <config.h>
#include <Box2D/Box2D.h>
#include <src/Object/object.hpp>

struct PhysicObjectProperties : public ObjectProperties{
	PhysicObjectType type;
	PhysicObjectShape shape;
	float density;
	float friction;
	float angle;
	sf::Vector2f velocity;
	
	PhysicObjectProperties getPhysicObjectProperties();
	void setObjectProperties(ObjectProperties& objectProperties);
	
	PhysicObjectProperties();
	PhysicObjectProperties(ObjectProperties objectProperties, PhysicObjectType objectType, PhysicObjectShape objectShape, float friction = 0.3, float density = 1, sf::Vector2f velocity = sf::Vector2f(0, 0), float angle = 0.f);
};

class PhysicObject : public Object{
	protected:
		PhysicObjectProperties physicObjectProperties;
		b2Body* bodyPtr;
	public:
		PhysicObjectProperties& getPhysicObjectProperties();
		b2Body* getBody();
		
		void pass(sf::Time elapsedTime);
		void addVelocity(sf::Vector2f velocity);
		
		void setName(std::string name);
		
		PhysicObject(Game&, PhysicObjectProperties);
		~PhysicObject();
};

#endif //COOPSHOOTER_PHYSICOBJECT_HPP
