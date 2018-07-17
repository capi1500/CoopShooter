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
			Entity* entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			if(entity->onGround()){
				entity->addVelocity(sf::Vector2f(0, -entity->getEntityProperties().jumpHeight));
			}
		}
		else if(toProcess.what == "moveLeft"){
			Entity* entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(entity->getEntityProperties().movementSpeed, 0));
			entity->setFacing(true);
		}
		else if(toProcess.what == "moveRight"){
			Entity* entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(-entity->getEntityProperties().movementSpeed, 0));
			entity->setFacing(false);
		}
		else if(toProcess.what == "moveDown"){
			Entity* entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(0, entity->getEntityProperties().movementSpeed));
		}
		else if(toProcess.what == "bulletHit"){
			if(gameRef.getWorld().exists(toProcess.object1)){
				if(gameRef.getWorld().exists(toProcess.object2)){
					PhysicObject * object = dynamic_cast<PhysicObject*>(gameRef.getWorld().getObject(toProcess.object2));
					if(object->getClassName() == ObjectClass::Player or object->getClassName() == ObjectClass::Entity){
						dynamic_cast<Entity*>(object)->gotHit(dynamic_cast<Bullet*>(gameRef.getWorld().getObject(toProcess.object1))->getBulletProperties().dmg);
					}
				}
				gameRef.getWorld().removeObject(toProcess.object1);
			}
		}
		else if(toProcess.what == "bulletShot"){
			Entity* object = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
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
				gameRef.getWorld().addObject(new Bullet(gameRef, BulletProperties(physicObjectProperties, bulletSpeed, bulletDmg, weaponProperties.bulletDistance)));
			}
		}
		else if(toProcess.what == "collectSth"){
			Collectible* collected = dynamic_cast<Collectible*>(gameRef.getWorld().getObject(toProcess.object1));
			if(gameRef.getWorld().exists(toProcess.object1)){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object2))->addBoost(collected->getCollectibleProperties().what, collected->getCollectibleProperties().boostTime);
				gameRef.getWorld().removeObject(toProcess.object1);
			}
		}
		events.pop();
	}
}

EventManager::EventManager(Game& game) : gameRef(game){

}