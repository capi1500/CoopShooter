//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_GAME_HPP
#define COOPSHOOTER_GAME_HPP

#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <src/World/world.hpp>
#include <src/Loader/loader.hpp>
#include <src/Entity/entity.hpp>
#include <src/PhysicObject/physicObject.hpp>
#include <src/Object/object.hpp>
#include <src/TextureManager/textureManager.hpp>
#include <src/EventManager/eventManager.hpp>
#include <src/SoundManager/soundManager.hpp>
#include <src/Enum/enum.hpp>
#include <config.h>
#include <src/ContactListener/contactListener.hpp>

class Game{
	private:
		GameState state;
		
		sf::RenderWindow window;
		b2World physicWorld;
		ContactListener contactListener;
		World world;
		EventManager eventManager;
		SoundManager soundManager;
		TextureManager textureManager;
		Loader loader;
		
		sf::Clock clock;
		sf::Time time;
		sf::View view;
	public:
		sf::RenderWindow& getWindow();
		b2World& getPhysicWorld();
		ContactListener& getContactListener();
		World& getWorld();
		EventManager& getEventManager();
		SoundManager& getSoundManager();
		TextureManager& getTextureManager();
		Loader& getLoader();
		sf::View& getView();
		
		void main();
		
		Game();
};

#endif //COOPSHOOTER_GAME_HPP
