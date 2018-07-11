//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_ENTITY_HPP
#define COOPSHOOTER_ENTITY_HPP

#include <src/PhysicObject/physicObject.hpp>

struct EntityProperites : public PhysicObjectProperties{
	unsigned maxHP;
	int HP;
	int jumpHeight;
	int movementSpeed;
	bool isFacingLeft;
	
	EntityProperites getEntityProperties();
	
	EntityProperites();
	EntityProperites(PhysicObjectProperties properties, unsigned maxHP, int HP = -1, bool isFacingLeft = true, int movementSpeed = defaultMovement, int jumpHeight = defaultJumpHeight);
};

class Entity : public PhysicObject{
	protected:
		EntityProperites entityProperites;
		sf::Time timeSinceLastShoot;
	public:
		const EntityProperites& getEntityProperties() const;
		
		bool ifCanShot();
		void shot();
		
		bool onGround();
		void pass(sf::Time elapsedTime);
		
		Entity(Game&, EntityProperites);
};

#endif //COOPSHOOTER_ENTITY_HPP
