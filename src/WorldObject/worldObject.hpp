//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_WORLDOBJECT_HPP
#define COOPSHOOTER_WORLDOBJECT_HPP

#include <src/PhysicObject/physicObject.hpp>

struct WorldObjectProperties : public PhysicObjectProperties{
	
	WorldObjectProperties getWorldObjectProperties();
	void setPhysicObjectProperties(PhysicObjectProperties physicObjectProperties);
	
	WorldObjectProperties();
	WorldObjectProperties(PhysicObjectProperties physicObjectProperties);
};

class WorldObject : public PhysicObject{
	protected:
		WorldObjectProperties worldObjectProperties;
	public:
		WorldObjectProperties& getWorldObjectProperties();
		
		WorldObject(Game& gameRef, WorldObjectProperties worldObjectProperties);
};

#endif //COOPSHOOTER_WORLDOBJECT_HPP
