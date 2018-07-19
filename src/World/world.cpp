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
	entities.erase(entities.begin(), entities.end());
	boostSpawnPoint.erase(boostSpawnPoint.begin(), boostSpawnPoint.end());
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

void World::addSpawnPoint(sf::Vector2f position){
	boostSpawnPoint.push_back(position);
}

PhysicObject* World::getObject(std::string name){
	if(name.substr(0, 6) == "bullet"){
		return bullets[name];
	}
	return object[name];
}

std::vector<sf::Vector2f>& World::getSpawns(){
	return boostSpawnPoint;
}

std::map<std::string, Bullet*> World::getBullets(){
	return bullets;
}

bool World::allCollectibleExsits(){
	for(auto i : boostSpawnPoint){
		if(not exists("collectible" + std::to_string(i.x) + "-" + std::to_string(i.y)))
			return false;
	}
	return true;
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
	if(timeSinceLastBoost >= boostSpawnRate){
		timeSinceLastBoost = sf::seconds(0);
		int randPlace = rand() % boostSpawnPoint.size(), random = rand() % 7;
		sf::Vector2f position;
		std::string what, itemName;
		sf::Time boostTime;
		if(not(allCollectibleExsits())){
			while(exists("collectible" + std::to_string(boostSpawnPoint[randPlace].x) + "-" + std::to_string(boostSpawnPoint[randPlace].y))){
				randPlace = rand() % boostSpawnPoint.size();
			}
			position = boostSpawnPoint[randPlace];
			itemName = "collectible" + std::to_string(position.x) + "-" + std::to_string(position.y);
			if(random == 0){
				what = "fasterShooting";
				boostTime = sf::seconds(5);
			}
			else if(random == 1){
				what = "fasterShots";
				boostTime = sf::seconds(5);
			}
			else if(random == 2){
				what = "hpUp";
			}
			else if(random == 3){
				what = "heal";
			}
			else if(random == 4){
				what = "dmgUp";
				boostTime = sf::seconds(5);
			}
			else if(random == 5){
				what = "noReload";
				boostTime = sf::seconds(5);
			}
			else if(random == 6){
				random = rand() % 3;
				if(random == 0){
					what = "rodBrown";
				}
				else if(random == 1){
					what = "bow";
				}
				else if(random == 2){
					what = "staff";
				}
			}
			addObject(new Collectible(gameRef, CollectibleProperties(PhysicObjectProperties(ObjectProperties(position, itemName, what), PhysicObjectType::Kinematic, PhysicObjectShape::Circle), what, boostTime)));
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