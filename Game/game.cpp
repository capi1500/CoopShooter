//
// Created by capi1500 on 10/07/18.
//

#include "game.hpp"
#include <src/Entity/entity.hpp>
#include <src/Player/player.hpp>

void Game::main(){
	textureManager.addTexture("Assets/Textures/blueBox.png", "ball");
	textureManager.addTexture("Assets/Textures/blueBoxCrouch.png", "ballCrouch");
	textureManager.addTexture("Assets/Textures/redBox.png", "box");
	textureManager.addTexture("Assets/Textures/ground.png", "ground");
	textureManager.addTexture("Assets/Textures/yellowBox.png", "bullet");
	PlayerProperties prop;
	prop.texture = "ball";
	prop.name = "player1";
	prop.position = sf::Vector2f(20, 10);
	prop.shape = PhysicObjectShape::Circle;
	prop.type = PhysicObjectType::Dynamic;
	prop.maxHP = 1;
	prop.HP = 1;
	PhysicObjectProperties prop2;
	prop2.shape = PhysicObjectShape::Box;
	prop2.texture = "ground";
	prop2.type = PhysicObjectType::Static;
	world.addObject(new Player(*this, prop));
	prop.name = "player2";
	prop.position = sf::Vector2f(430, 10);
	world.addObject(new Player(*this, prop));
	prop2.position = sf::Vector2f(75, 200);
	prop2.name = "ground";
	world.addObject(new PhysicObject(*this, prop2));
	prop2.position = sf::Vector2f(75 + 150, 200);
	prop2.name = "ground2";
	world.addObject(new PhysicObject(*this, prop2));
	prop2.position = sf::Vector2f(75 + 300, 200);
	prop2.name = "ground3";
	world.addObject(new PhysicObject(*this, prop2));
	prop2.angle = 90;
	prop2.name = "ground4";
	prop2.position = sf::Vector2f(5, 150);
	world.addObject(new PhysicObject(*this, prop2));
	prop2.name = "ground5";
	prop2.position = sf::Vector2f(455, 150);
	world.addObject(new PhysicObject(*this, prop2));
	
	sf::Event event;
	clock.restart();
	while(window.isOpen()){
		while(window.pollEvent(event)){
			eventManager.handleEvents(event);
		}
		eventManager.handleEvents();
		
		time = clock.restart();
		physicWorld.Step(time.asSeconds(), defVelocityIterations, defPositionIterations);
		physicWorld.ClearForces();
		world.passAll(time);
		
		window.clear();
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

Game::Game() : window(sf::VideoMode(500, 500), "Coop Shooter", sf::Style::Default, sf::ContextSettings(0, 0, ANTIALIASING, versionMajor, versionMinor)),
		physicWorld(b2Vec2(0.0f, 9.97f)),
		eventManager(*this),
		world(*this),
		contactListener(*this){
	physicWorld.SetContactListener(&contactListener);
}

sf::View& Game::getView(){
	return view;
}
