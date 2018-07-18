//
// Created by capi1500 on 11/07/18.
//

#include "entity.hpp"
#include <src/Game/game.hpp>
#include <src/Weapon/weapon.hpp>

EntityProperites::EntityProperites(){
	maxHP = HP = 0;
	jumpHeight = defaultJumpHeight;
}

EntityProperites::EntityProperites(PhysicObjectProperties properties, unsigned maxHP, int HP, Equipment equipment, bool isFacingLeft, int movementSpeed, int jumpHeight) : PhysicObjectProperties(properties){
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
	this->equipment = equipment;
	isDead = (HP <= 0);
}

EntityProperites EntityProperites::getEntityProperties(){
	return EntityProperites(getPhysicObjectProperties(), maxHP, HP, equipment, isFacingLeft, movementSpeed, jumpHeight);
}

void EntityProperites::setPhysicObjectProperties(PhysicObjectProperties physicObjectProperties){
	type = physicObjectProperties.type;
	shape = physicObjectProperties.shape;
	density = physicObjectProperties.density;
	friction = physicObjectProperties.friction;
	angle = physicObjectProperties.angle;
	velocity = physicObjectProperties.velocity;
}

EntityProperites& Entity::getEntityProperties(){
	return entityProperites;
}

std::vector<std::pair<Item*, int>>& Entity::getEquipment(){
	return entityProperites.equipment.getEquipment();
}

Item* Entity::getEquiped(){
	return entityProperites.equipment.getEquiped();
}

std::map<std::string, sf::Time>& Entity::getBoosts(){
	return entityProperites.boosts.getBoosts();
}

bool Entity::haveBoost(std::string name){
	return entityProperites.boosts.getBoosts().find(name) != entityProperites.boosts.getBoosts().end();
}

void Entity::addBoost(std::string name, sf::Time time){
	if(name == "hpUp"){
		entityProperites.maxHP += 5;
		entityProperites.HP += 5;
	}
	else if(name == "heal"){
		entityProperites.HP = entityProperites.maxHP;
	}
	else{
		entityProperites.boosts.addBoost(name, time);
	}
}

void Entity::equip(int id){
	entityProperites.equipment.equip(id);
}



bool Entity::ifCanShot(){
	if(entityProperites.isDead or getEquiped()->getClassName() != ObjectClass::Weapon){
		return false;
	}
	if((not haveBoost("noReload")) and not dynamic_cast<Weapon*>(getEquiped())->canShoot()){
		return false;
	}
	if(haveBoost("fasterShooting")){
		return timeSinceLastShoot >= dynamic_cast<Weapon*>(getEquiped())->getWeaponProperties().attackDelay / 2.f;
	}
	return timeSinceLastShoot >= dynamic_cast<Weapon*>(getEquiped())->getWeaponProperties().attackDelay;
}

void Entity::shot(){
	if(not haveBoost("noReload")){
		dynamic_cast<Weapon*>(getEquiped())->shoot();
	}
	timeSinceLastShoot = sf::milliseconds(0);
}

bool Entity::onGround(){
	for(auto* contact = getBody()->GetContactList(); contact; contact = contact->next){
		for(auto obj = gameRef.getWorld().getObjects().begin(); obj != gameRef.getWorld().getObjects().end(); obj++){
			if(contact->other == obj->second->getBody() and contact->contact->IsTouching()){
				if(obj->second->getClassName() == ObjectClass::PhysicObject or obj->second->getClassName() == ObjectClass::WorldObject){
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

void Entity::setFacing(bool facingLeft){
	entityProperites.isFacingLeft = facingLeft;
}

void Entity::gotHit(int pureDMG){
	entityProperites.HP -= pureDMG;
}

void Entity::equipNext(){
	entityProperites.equipment.equipNext();
}

void Entity::equipPrevious(){
	entityProperites.equipment.equipPrevious();
}

void Entity::pass(sf::Time elapsedTime){
	PhysicObject::pass(elapsedTime);
	timeSinceLastShoot += elapsedTime;
	if(entityProperites.HP <= 0){
		getBody()->SetActive(false);
		entityProperites.isDead = true;
	}
	if(entityProperites.isFacingLeft){
		setScale(sf::Vector2f(1, 1));
	}
	else{
		setScale(sf::Vector2f(-1, 1));
	}
	entityProperites.boosts.pass(elapsedTime);
	for(auto i : getEquipment()){
		i.first->pass(elapsedTime);
	}
	healthBar.setTextureRect(sf::IntRect(0, (7 - static_cast<int>(7 * (static_cast<double>(entityProperites.HP) / entityProperites.maxHP))) * 8, 28, 8));
	healthBar.setPosition(getCentre().x - getGlobalBounds().width / 2 - 14 , getGlobalBounds().top - 12);
}

void Entity::draw(){
	if(not entityProperites.isDead){
		PhysicObject::draw();
		gameRef.getWindow().draw(healthBar);
	}
}

Entity::Entity(Game& gameRef, EntityProperites properites) : entityProperites(properites),
		PhysicObject(gameRef, properites.getPhysicObjectProperties()){
	entityProperites.equipment.init(gameRef);
	// Box2D stuff
	getBody()->SetFixedRotation(true);
	// Coop Shooter stuff
	className = ObjectClass::Entity;
	healthBar.setTexture(gameRef.getTextureManager().getTexture("healthBar"));
}