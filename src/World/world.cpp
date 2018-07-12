//
// Created by capi1500 on 10/07/18.
//

#include "world.hpp"
#include <src/Game/game.hpp>
#include <src/PhysicObject/physicObject.hpp>
#include <src/Collectible/collectible.hpp>

void World::addObject(PhysicObject * obj){
	if(obj->getClassName() == ObjectClass::Bullet){
		dynamic_cast<PhysicObject*>(obj)->setName("bullet" + std::to_string(bulletID++));
		bullets[obj->getName()] = dynamic_cast<Bullet*>(obj);
		return;
	}
	object[obj->getName()] = obj;
	if(obj->getClassName() == ObjectClass::Entity or obj->getClassName() == ObjectClass::Player){
		entities[obj->getName()] = dynamic_cast<Entity*>(obj);
	}
}

void World::removeAll(){
	for(auto it = bullets.begin(); it != bullets.end(); it++){
		delete it->second;
	}
	for(auto it = object.begin(); it != object.end(); it++){
		delete it->second;
	}
	bullets.erase(bullets.begin(), bullets.end());
	object.erase(object.begin(), object.end());
}

void World::removeObject(std::string name){
	if(name.substr(0, 6) == "bullet"){
		if(bullets.find(name) != bullets.end()){
			bullets[name]->getBody()->DestroyFixture(bullets[name]->getBody()->GetFixtureList());
			gameRef.getPhysicWorld().DestroyBody(bullets[name]->getBody());
			bullets.erase(name);
		}
	}
	else{
		if(object.find(name) != object.end()){
			if(getObject(name)->getClassName() == ObjectClass::Entity or getObject(name)->getClassName() == ObjectClass::Player){
				entities.erase(name);
			}
			object[name]->getBody()->DestroyFixture(object[name]->getBody()->GetFixtureList());
			gameRef.getPhysicWorld().DestroyBody(object[name]->getBody());
			object.erase(name);
		}
	}
}

PhysicObject* World::getObject(std::string name){
	if(name.substr(0, 6) == "bullet"){
		return bullets[name];
	}
	return object[name];
}

bool World::exists(std::string name){
	if(name.substr(0, 6) == "bullet"){
		return bullets.find(name) != bullets.end();
	}
	return object.find(name) != object.end();
}

std::map<std::string, PhysicObject*>& World::getObjects(){
	return object;
}

std::map<std::string, Entity*>& World::getEntities(){
	return entities;
}

void World::pass(std::string name, sf::Time elapsedTime){
	getObject(name)->pass(elapsedTime);
}

void World::passAll(sf::Time elapsedTime){
	timeSinceLastBoost += elapsedTime;
	for(auto it = object.begin(); it != object.end(); it++){
		it->second->pass(elapsedTime);
	}
	for(auto it = bullets.begin(); it != bullets.end(); it++){
		it->second->pass(elapsedTime);
	}
	if(timeSinceLastBoost >= sf::seconds(10)){
		timeSinceLastBoost = sf::seconds(0);
		int randPlace = rand() % 4, randBoost = rand() % 6;
		sf::Vector2f position;
		std::string boost, boostName;
		sf::Time boostTime;
		if(not(exists("collectible0") and exists("collectible1") and exists("collectible2") and exists("collectible3"))){
			while(exists("collectible" + std::to_string(randPlace))){
				randPlace = rand() % 4;
			}
			boostName = "collectible" + std::to_string(randPlace);
			if(randPlace == 0){
				position = sf::Vector2f(100, -80);
			}
			else if(randPlace == 1){
				position = sf::Vector2f(1100, -80);
			}
			else if(randPlace == 2){
				position = sf::Vector2f(420, -100);
			}
			else if(randPlace == 3){
				position = sf::Vector2f(780, -100);
			}
			if(randBoost == 0){
				boost = "fasterShooting";
				boostTime = sf::seconds(5);
			}
			else if(randBoost == 1){
				boost = "fasterShots";
				boostTime = sf::seconds(5);
			}
			else if(randBoost == 2){
				boost = "hpUp";
			}
			else if(randBoost == 3){
				boost = "heal";
			}
			else if(randBoost == 4){
				boost = "dmgUp";
				boostTime = sf::seconds(5);
			}
			else if(randBoost == 5){
				boost = "noReload";
				boostTime = sf::seconds(10);
			}
			addObject(new Collectible(gameRef, CollectibleProperties(PhysicObjectProperties(ObjectProperties(position, boostName, boost + "Collect"), PhysicObjectType::Kinematic, PhysicObjectShape::Circle), boost, boostTime)));
		}
	}
}

void World::draw(std::string name){
	getObject(name)->draw();
}

void World::drawAll(){
	for(auto it = object.begin(); it != object.end(); it++){
		it->second->draw();
	}
	for(auto it = bullets.begin(); it != bullets.end(); it++){
		it->second->draw();
	}
}

World::World(Game& gameRef) : gameRef(gameRef){
	bulletID = 0;
}