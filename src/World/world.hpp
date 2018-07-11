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
		Game& gameRef;
		unsigned long long bulletID;
		std::map<std::string, Bullet*> bullets;
		std::map<std::string, Entity*> entities;
		std::map<std::string, PhysicObject*> object;
	public:
		void addObject(PhysicObject*);
		void removeObject(std::string);
		PhysicObject* getObject(std::string);
		std::map<std::string, PhysicObject*>& getObjects();
		std::map<std::string, Entity*>& getEntities();
		
		void pass(std::string, sf::Time);
		void passAll(sf::Time);
		void draw(std::string);
		void drawAll();
		
		World(Game& gameRef);
};

#endif //COOPSHOOTER_WORLD_HPP