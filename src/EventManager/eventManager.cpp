//
// Created by capi1500 on 10/07/18.
//

#include "eventManager.hpp"
#include <src/Game/game.hpp>

void EventManager::addEvent(Event event){
	events.push(event);
}

void EventManager::handleEvents(sf::Event event){
	if(event.type == sf::Event::Closed){
		gameRef.getWindow().close();
	}
	if(event.type == sf::Event::Resized){
		gameRef.getView().setSize(static_cast<sf::Vector2f>(gameRef.getWindow().getSize()));
		gameRef.getView().setCenter(gameRef.getWindow().getSize().x / 2, gameRef.getWindow().getSize().y / 2);
		gameRef.getWindow().setView(gameRef.getView());
	}
}

void EventManager::handleEvents(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		addEvent(Event("jump", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
		addEvent(Event("jump", "player2"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		addEvent(Event("moveLeft", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
		addEvent(Event("moveLeft", "player2"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		addEvent(Event("moveRight", "player1"));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		addEvent(Event("moveRight", "player2"));
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
			entity->addVelocity(sf::Vector2f(-entity->getEntityProperties().movementSpeed, 0));
		}
		else if(toProcess.what == "moveRight"){
			Entity* entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(entity->getEntityProperties().movementSpeed, 0));
		}
		else if(toProcess.what == "bulletHit"){
			gameRef.getWorld().removeObject(toProcess.object1);
			printf("bullet '%s' just hit '%s'\n", toProcess.object1.c_str(), toProcess.object2.c_str());
		}
		else if(toProcess.what == "bulletShot"){
			Entity* object = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			if(object->ifCanShot()){
				object->shot();
				ObjectProperties objectProperties;
				objectProperties.texture = "bullet";
				objectProperties.position = sf::Vector2f(object->getPosition().x + (object->getEntityProperties().isFacingLeft ? 1 : -1) * (gameRef.getTextureManager().getTexture(objectProperties.texture).getSize().x + object->getGlobalBounds().width / 2), object->getPosition().y);
				PhysicObjectProperties physicObjectProperties(objectProperties, PhysicObjectType::Dynamic, PhysicObjectShape::Circle);
				physicObjectProperties.velocity = sf::Vector2f((object->getEntityProperties().isFacingLeft ? 1 : -1) * bulletSpeed, 0);
				gameRef.getWorld().addObject(new Bullet(gameRef, BulletProperties(physicObjectProperties)));
			}
		}
		events.pop();
	}
}

EventManager::EventManager(Game& game) : gameRef(game){

}