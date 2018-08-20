//
// Created by capi1500 on 10/07/18.
//

#include "game.hpp"
#include <src/Entity/entity.hpp>
#include <src/Player/player.hpp>
#include <src/Weapon/weapon.hpp>
#include <src/ItemManager/itemManager.hpp>
#include <src/Collectible/collectible.hpp>
#include <src/GraphicAlphabet/graphicAlphabet.hpp>
#include <src/GraphicString/graphicString.hpp>
#include <src/Label/label.hpp>
#include <src/Menu/menu.hpp>
#include <src/Button/button.hpp>

void Game::main(){
	sf::Event event;
	clock.restart();
	while(window.isOpen()){
		while(window.pollEvent(event)){
			eventManager.handleEvents(event);
		}
		eventManager.handleEvents();
		
		if(timeSet){
			timeSet = false;
			clock.restart();
		}
		else{
			time = clock.restart();
		}
		if(menuManager.getActive()->getMenuProperties().gameRunning){
			physicWorld.Step(time.asSeconds(), defVelocityIterations, defPositionIterations);
			physicWorld.ClearForces();
			world.passAll(time);
		}
		menuManager.getActive()->pass(time);
		
		player1view.setCenter(sf::Vector2f(0, 0));
		player1view.move(world.getObject("player1")->getPosition().x, world.getObject("player1")->getGlobalBounds().top);
		//player1view.setSize(sf::Vector2f(window.getSize().x / 1.5f, window.getSize().y / 3));
		player2view.setCenter(sf::Vector2f(0, 0));
		player2view.move(world.getObject("player2")->getPosition().x, world.getObject("player2")->getGlobalBounds().top);
		//player2view.setSize(sf::Vector2f(window.getSize().x / 1.5f, window.getSize().y / 3));
		fullScreenView.setSize(window.getSize().x, window.getSize().y);
		fullScreenView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
		window.clear();
		if(menuManager.getActive()->getMenuProperties().gameDraw){
			window.setView(player1view);
			world.drawAll();
			dynamic_cast<Player*>(getWorld().getObject("player1"))->drawAmmo();
			dynamic_cast<Player*>(getWorld().getObject("player1"))->drawEquipment();
			window.setView(player2view);
			world.drawAll();
			dynamic_cast<Player*>(getWorld().getObject("player2"))->drawAmmo();
			dynamic_cast<Player*>(getWorld().getObject("player2"))->drawEquipment();
		}
		window.setView(fullScreenView);
		menuManager.getActive()->setCentre(window.getView().getCenter());
		menuManager.getActive()->draw();
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

TemplateManager& Game::getTemplateManager(){
	return templateManager;
}

sf::View& Game::getPlayer1View(){
	return player1view;
}

sf::View& Game::getPlayer2View(){
	return player2view;
}

sf::View& Game::getFullScreenView(){
	return fullScreenView;
}

GraphicAlphabet& Game::getGraphicAlphabet(){
	return graphicAlphabet;
}

void Game::restartClock(){
	clock.restart();
}

sf::Time Game::getTime(){
	return time;
}

void Game::setTime(sf::Time time){
	this->time = time;
	timeSet = true;
}

MenuManager& Game::getMenuManager(){
	return menuManager;
}

Game::Game() : window(sf::VideoMode(900, 900), "Coop Shooter", sf::Style::Fullscreen, sf::ContextSettings(0, 0, ANTIALIASING, versionMajor, versionMinor)),
		physicWorld(b2Vec2(0.0f, 12.f)),
		eventManager(*this),
		world(*this),
		contactListener(*this),
		loader(*this),
		templateManager(*this),
		graphicAlphabet(*this),
		menuManager(*this),
		soundManager(*this){
	loader.load("Default");
	loader.loadMenu("Saves/menu.sv");
	music.openFromFile("Assets/Audio/The\ Traveller.ogg");
	music.setLoop(true);
	music.setVolume(10);
	music.play();
	physicWorld.SetContactListener(&contactListener);
	player1view.setSize(sf::Vector2f(window.getSize().x * 2, window.getSize().y));
	player2view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 2));
	fullScreenView.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	player1view.setViewport(sf::FloatRect(0, 0, 1, 0.5f));
	player2view.setViewport(sf::FloatRect(0, 0.5, 1, 0.5f));
	fullScreenView.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setFramerateLimit(60);
	srand(std::time(NULL));
}
