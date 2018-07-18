//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_ENTITY_HPP
#define COOPSHOOTER_ENTITY_HPP

#include <src/PhysicObject/physicObject.hpp>
#include <src/Equipment/equipment.hpp>
#include <src/Boosts/boosts.hpp>

struct EntityProperties : public PhysicObjectProperties{
	unsigned maxHP;
	int HP;
	int jumpHeight;
	int movementSpeed;
	bool isFacingLeft;
	bool isDead;
	Equipment equipment;
	Boosts boosts;
	
	EntityProperties getEntityProperties();
	void setPhysicObjectProperties(PhysicObjectProperties physicObjectProperties);
	
	EntityProperties();
	EntityProperties(PhysicObjectProperties properties, unsigned maxHP, int HP = -1, Equipment equipment = Equipment(), bool isFacingLeft = true, int movementSpeed = defaultMovement, int jumpHeight = defaultJumpHeight);
};

class Entity : public PhysicObject{
	private:
		Sprite healthBar;
	protected:
		EntityProperties entityProperites;
		sf::Time timeSinceLastShoot;
	public:
		EntityProperties& getEntityProperties();
		std::vector<std::pair<Item*, int>>& getEquipment();
		std::map<std::string, sf::Time>& getBoosts();
		Item* getEquiped();
		bool haveBoost(std::string name);
		
		void addBoost(std::string name, sf::Time time);
		bool ifCanShot();
		void shot();
		void setFacing(bool facingLeft);
		void equip(int id);
		bool onGround();
		void gotHit(int pureDMG);
		void equipNext();
		void equipPrevious();
		
		void pass(sf::Time elapsedTime);
		void draw();
		
		Entity(Game&, EntityProperties);
};

#endif //COOPSHOOTER_ENTITY_HPP
