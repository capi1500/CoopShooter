//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_WORLD_HPP
#define COOPSHOOTER_WORLD_HPP

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <src/Player/player.hpp>
#include <src/Bullet/bullet.hpp>

class World{
	private:
		sf::Time timeSinceLastBoost;
		Game& gameRef;
		unsigned long long bulletID;
		std::map<std::string, Bullet*> bullets;
		std::map<std::string, Entity*> entities;
		std::map<std::string, PhysicObject*> object;
		std::vector<sf::Vector2f> boostSpawnPoint;
		bool allCollectibleExsits();
	public:
		void removeAll();
		void addObject(PhysicObject*);
		void addSpawnPoint(sf::Vector2f position);
		void removeObject(std::string);
		PhysicObject* getObject(std::string);
		std::map<std::string, PhysicObject*>& getObjects();
		std::map<std::string, Entity*>& getEntities();
		std::vector<sf::Vector2f>& getSpawns();
		bool exists(std::string name);
		
		void pass(std::string, sf::Time);
		void passAll(sf::Time);
		void draw(std::string);
		void drawAll();
		
		World(Game& gameRef);
};

#endif //COOPSHOOTER_WORLD_HPP
