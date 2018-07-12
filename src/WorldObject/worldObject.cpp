//
// Created by capi1500 on 12/07/18.
//

#include "worldObject.hpp"

WorldObjectProperties::WorldObjectProperties(){
}

WorldObjectProperties::WorldObjectProperties(PhysicObjectProperties physicObjectProperties) : PhysicObjectProperties(getPhysicObjectProperties()){
}

WorldObjectProperties WorldObjectProperties::getWorldObjectProperties(){
	return WorldObjectProperties(getPhysicObjectProperties());
}

void WorldObjectProperties::setPhysicObjectProperties(PhysicObjectProperties physicObjectProperties){
	type = physicObjectProperties.type;
	shape = physicObjectProperties.shape;
	density = physicObjectProperties.density;
	friction = physicObjectProperties.friction;
	angle = physicObjectProperties.angle;
	velocity = physicObjectProperties.velocity;
}

WorldObjectProperties& WorldObject::getWorldObjectProperties(){
	return worldObjectProperties;
}

WorldObject::WorldObject(Game& gameRef, WorldObjectProperties worldObjectProperties) : PhysicObject(gameRef, worldObjectProperties.getPhysicObjectProperties()), worldObjectProperties(worldObjectProperties){
	className = ObjectClass::WorldObject;
}