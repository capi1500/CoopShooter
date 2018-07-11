//
// Created by capi1500 on 11/07/18.
//

#include "entity.hpp"
#include <src/Game/game.hpp>

EntityProperites::EntityProperites(){
	maxHP = HP = 0;
	jumpHeight = defaultJumpHeight;
}

EntityProperites::EntityProperites(PhysicObjectProperties properties, unsigned maxHP, int HP, bool isFacingLeft, int movementSpeed, int jumpHeight) : PhysicObjectProperties(properties){
	this->maxHP = maxHP;
	if(HP != -1){
		this->HP = HP;
	}
	else{
		this->HP = this->maxHP;
	}
	this->jumpHeight = jumpHeight;
	this->movementSpeed = movementSpeed;
	this->isFacingLeft = isFacingLeft;
}

EntityProperites EntityProperites::getEntityProperties(){
	return EntityProperites(getPhysicObjectProperties(), maxHP, HP);
}

const EntityProperites& Entity::getEntityProperties() const{
	return entityProperites;
}

bool Entity::ifCanShot(){
	return timeSinceLastShoot >= defaultShotDelay;
}

void Entity::shot(){
	timeSinceLastShoot = sf::milliseconds(0);
}

bool Entity::onGround(){
	for(auto* contact = getBody()->GetContactList(); contact; contact = contact->next){
		for(auto obj = gameRef.getWorld().getObjects().begin(); obj != gameRef.getWorld().getObjects().end(); obj++){
			if(contact->other == obj->second->getBody() and contact->contact->IsTouching()){
				if(obj->second->getClassName() == ObjectClass::PhysicObject){
					sf::FloatRect o1 = getGlobalBounds(), o2 = obj->second->getGlobalBounds();
					if(o1.top + o1.height - 1 <= o2.top and o1.left + o1.width > o2.left and o1.left < o2.left + o2.width){
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Entity::pass(sf::Time elapsedTime){
	PhysicObject::pass(elapsedTime);
	timeSinceLastShoot += elapsedTime;
	if(getBody()->GetLinearVelocity().x > 0)
		entityProperites.isFacingLeft = true;
	if(getBody()->GetLinearVelocity().x < 0)
		entityProperites.isFacingLeft = false;
}

Entity::Entity(Game& gameRef, EntityProperites properites) : entityProperites(properites),
		PhysicObject(gameRef, properites.getPhysicObjectProperties()){
	// Box2D stuff
	getBody()->SetFixedRotation(true);
	// Coop Shooter stuff
	className = ObjectClass::Entity;
}