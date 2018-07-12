//
// Created by capi1500 on 10/07/18.
//

#include "game.hpp"
#include <src/Entity/entity.hpp>
#include <src/Player/player.hpp>
#include <src/Weapon/weapon.hpp>
#include <src/ItemManager/itemManager.hpp>

void Game::main(){
	textureManager.addTexture("Assets/Textures/blueBox.png", "ball");
	textureManager.addTexture("Assets/Textures/blueBoxCrouch.png", "ballCrouch");
	textureManager.addTexture("Assets/Textures/redBox.png", "box");
	textureManager.addTexture("Assets/Textures/redSlab.png", "slab");
	textureManager.addTexture("Assets/Textures/ground.png", "ground");
	textureManager.addTexture("Assets/Textures/yellowBox.png", "bullet");
	textureManager.addTexture("Assets/Textures/wall.png", "wall");
	itemManager.addItem(new Weapon(*this, WeaponProperties(ItemProperties(ObjectProperties(sf::Vector2f(0, 0), "gun", "")), sf::milliseconds(250), 2, 50)));
	loader.load("Default");
	sf::Event event;
	clock.restart();
	while(window.isOpen()){
		while(window.pollEvent(event)){
			eventManager.handleEvents(event);
		}
		eventManager.handleEvents();
		
		time = clock.restart();
		//printf("%lld\n", time.asMicroseconds());
		physicWorld.Step(time.asSeconds(), defVelocityIterations, defPositionIterations);
		physicWorld.ClearForces();
		world.passAll(time);
		
		player1view.setCenter(sf::Vector2f(0, 0));
		player1view.move(world.getObject("player1")->getCentre().x, world.getObject("player1")->getCentre().y - window.getSize().y / 6);
		player2view.setCenter(sf::Vector2f(0, 0));
		player2view.move(world.getObject("player2")->getCentre().x, world.getObject("player2")->getCentre().y - window.getSize().y / 6);
		
		window.clear();
		window.setView(player1view);
		world.drawAll();
		window.setView(player2view);
		world.drawAll();
		window.display();
	}
}

sf::RenderWindow& Game::getWindow(){
	return window;
}

b2World& Game::getPhysicWorld(){
	return physicWorld;
}

ContactListener& Game::getContactListener(){
	return contactListener;
}

World& Game::getWorld(){
	return world;
}

EventManager& Game::getEventManager(){
	return eventManager;
}

SoundManager& Game::getSoundManager(){
	return soundManager;
}

TextureManager& Game::getTextureManager(){
	return textureManager;
}

Loader& Game::getLoader(){
	return loader;
}

ItemManager& Game::getItemManager(){
	return itemManager;
}

sf::View& Game::getPlayer1View(){
	return player1view;
}

sf::View& Game::getPlayer2View(){
	return player2view;
}

Game::Game() : window(sf::VideoMode(500, 500), "Coop Shooter", sf::Style::Fullscreen, sf::ContextSettings(0, 0, ANTIALIASING, versionMajor, versionMinor)),
		physicWorld(b2Vec2(0.0f, 9.97f)),
		eventManager(*this),
		world(*this),
		contactListener(*this),
		loader(*this){
	physicWorld.SetContactListener(&contactListener);
	player1view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 2));
	player2view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 2));
	player1view.setViewport(sf::FloatRect(0, 0, 1, 0.5f));
	player2view.setViewport(sf::FloatRect(0, 0.5, 1, 0.5f));
	window.setFramerateLimit(60);
}
