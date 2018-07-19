//
// Created by capi1500 on 10/07/18.
//

#include "eventManager.hpp"
#include <src/Game/game.hpp>
#include <src/Weapon/weapon.hpp>
#include <src/Collectible/collectible.hpp>

void EventManager::addEvent(Event event){
	events.push(event);
}

void EventManager::handleEvents(sf::Event event){
	if(event.type == sf::Event::Closed){
		gameRef.getWindow().close();
	}
	if(event.type == sf::Event::Resized){
		gameRef.getPlayer1View().setSize(sf::Vector2f(gameRef.getWindow().getSize().x, gameRef.getWindow().getSize().y / 2));
		gameRef.getPlayer2View().setSize(sf::Vector2f(gameRef.getWindow().getSize().x, gameRef.getWindow().getSize().y / 2));
	}
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::Escape){
			gameRef.getWindow().close();
		}
		if(event.key.code == sf::Keyboard::R){
			gameRef.getWorld().removeAll();
			gameRef.getLoader().load("Default");
		}
		if(event.key.code == sf::Keyboard::V){
			gameRef.getLoader().save("Temp");
		}
		if(event.key.code == sf::Keyboard::B){
			gameRef.getWorld().removeAll();
			gameRef.getLoader().load("Temp");
		}
		if(event.key.code == sf::Keyboard::Q){
			addEvent(Event("equipPrevious", "player1"));
		}
		if(event.key.code == sf::Keyboard::E){
			addEvent(Event("equipNext", "player1"));
		}
		if(event.key.code == sf::Keyboard::U){
			addEvent(Event("equipPrevious", "player2"));
		}
		if(event.key.code == sf::Keyboard::O){
			addEvent(Event("equipNext", "player2"));
		}
		if(event.key.code == sf::Keyboard::Z){
			addEvent(Event("remove", "player1"));
		}
		if(event.key.code == sf::Keyboard::M){
			addEvent(Event("remove", "player2"));
		}
		if(event.key.code == sf::Keyboard::X){
			addEvent(Event("throw", "player1"));
		}
		if(event.key.code == sf::Keyboard::Comma){
			addEvent(Event("throw", "player2"));
		}
	}
}

void EventManager::handleEvents(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		addEvent(Event("jump", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
		addEvent(Event("jump", "player2"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		addEvent(Event("moveLeft", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		addEvent(Event("moveLeft", "player2"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		addEvent(Event("moveRight", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
		addEvent(Event("moveRight", "player2"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		addEvent(Event("moveDown", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
		addEvent(Event("moveDown", "player2"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
		addEvent(Event("bulletShot", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
		addEvent(Event("bulletShot", "player2"));
	}
	Event toProcess;
	while(not events.empty()){
		toProcess = events.front();
		
		if(toProcess.what == "jump"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			if(entity->onGround()){
				entity->addVelocity(sf::Vector2f(0, -entity->getEntityProperties().jumpHeight));
			}
		}
		else if(toProcess.what == "moveLeft"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(entity->getEntityProperties().movementSpeed, 0));
			entity->setFacing(true);
		}
		else if(toProcess.what == "moveRight"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(-entity->getEntityProperties().movementSpeed, 0));
			entity->setFacing(false);
		}
		else if(toProcess.what == "moveDown"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(0, entity->getEntityProperties().movementSpeed));
		}
		else if(toProcess.what == "equipNext"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->equipNext();
			}
		}
		else if(toProcess.what == "equipPrevious"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->equipPrevious();
			}
		}
		else if(toProcess.what == "bulletHit"){
			if(gameRef.getWorld().exists(toProcess.object1)){
				if(gameRef.getWorld().exists(toProcess.object2)){
					PhysicObject* object = dynamic_cast<PhysicObject*>(gameRef.getWorld().getObject(toProcess.object2));
					if(dynamic_cast<Bullet*>(gameRef.getWorld().getObject(toProcess.object1))->canHit() and (object->getClassName() == ObjectClass::Player or object->getClassName() == ObjectClass::Entity)){
						dynamic_cast<Entity*>(object)->gotHit(dynamic_cast<Bullet*>(gameRef.getWorld().getObject(toProcess.object1))->getBulletProperties().dmg);
						gameRef.getWorld().removeObject(toProcess.object1);
					}
					else if(object->getClassName() == ObjectClass::WorldObject){
						gameRef.getWorld().removeObject(toProcess.object1);
					}
				}
				else if(toProcess.object2 == ""){
					gameRef.getWorld().removeObject(toProcess.object1);
				}
			}
		}
		else if(toProcess.what == "bulletShot"){
			Entity * object = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			if(object->ifCanShot()){
				object->shot();
				ObjectProperties objectProperties;
				objectProperties.texture = dynamic_cast<Weapon*>(object->getEquiped())->getWeaponProperties().bulletTexture;
				objectProperties.position = sf::Vector2f(object->getPosition().x + (object->getEntityProperties().isFacingLeft ? 1 : -1) * (gameRef.getTextureManager().getTexture(objectProperties.texture).getSize().x + object->getGlobalBounds().width / 2), object->getPosition().y);
				PhysicObjectProperties physicObjectProperties(objectProperties, PhysicObjectType::Dynamic, PhysicObjectShape::Box);
				WeaponProperties weaponProperties = dynamic_cast<Weapon*>(object->getEquiped())->getWeaponProperties();
				float bulletSpeed = dynamic_cast<Weapon*>(object->getEquiped())->getWeaponProperties().bulletSpeed;
				int bulletDmg = weaponProperties.dmg;
				if(object->haveBoost("dmgUp")){
					bulletDmg *= 2;
				}
				if(object->haveBoost("fasterShots")){
					bulletSpeed *= 2;
				}
				physicObjectProperties.velocity = sf::Vector2f((object->getEntityProperties().isFacingLeft ? 1 : -1) * bulletSpeed, 0);
				gameRef.getWorld().addObject(new Bullet(gameRef, BulletProperties(physicObjectProperties, bulletSpeed, bulletDmg, weaponProperties.bulletDistance, objectProperties.position)));
			}
		}
		else if(toProcess.what == "collectSth"){
			if(gameRef.getWorld().exists(toProcess.object1)){
				Collectible * collected = dynamic_cast<Collectible*>(gameRef.getWorld().getObject(toProcess.object1));
				if(collected->canBeCollected()){
					if(gameRef.getWorld().getObject(toProcess.object2)->getClassName() == ObjectClass::Entity or gameRef.getWorld().getObject(toProcess.object2)->getClassName() == ObjectClass::Player){
						if(gameRef.getItemManager().exist(collected->getCollectibleProperties().what)){
							dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object2))->getEntityProperties().equipment.addItem(gameRef.getItemManager().getItem(collected->getCollectibleProperties().what));
						}
						else{
							dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object2))->addBoost(collected->getCollectibleProperties().what, collected->getCollectibleProperties().boostTime);
						}
						gameRef.getWorld().removeObject(toProcess.object1);
					}
				}
			}
		}
		else if(toProcess.what == "remove"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead and dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.canRemove()){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.removeEquiped();
			}
		}
		else if(toProcess.what == "throw"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead and dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.canRemove()){
				sf::Vector2f position = gameRef.getWorld().getObject(toProcess.object1)->getPosition() + sf::Vector2f(5 * (dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isFacingLeft ? 1 : -1), 0);
				std::string what = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.getEquiped()->getName(), itemName = "collectibleW" + std::to_string(id++);
				gameRef.getWorld().addObject(new Collectible(gameRef, CollectibleProperties(PhysicObjectProperties(ObjectProperties(position, itemName, what), PhysicObjectType::Dynamic, PhysicObjectShape::Box, 0.3, 1, sf::Vector2f(100 * (dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isFacingLeft ? 1 : -1), 0)), what)));
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.removeEquiped();
			}
		}
		events.pop();
	}
}

EventManager::EventManager(Game& game) : gameRef(game){
	id = 0;
}