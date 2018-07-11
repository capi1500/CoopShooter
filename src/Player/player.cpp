//
// Created by capi1500 on 11/07/18.
//

#include "player.hpp"

PlayerProperties::PlayerProperties(){
	movementSpeed = playerMovement;
	jumpHeight = playerJumpHeight;
}

PlayerProperties::PlayerProperties(EntityProperites properites) : EntityProperites(properites){
}

PlayerProperties PlayerProperties::getPlayerProperties(){
	return PlayerProperties(getEntityProperties());
}

void Player::pass(sf::Time elapsedTime){
	Entity::pass(elapsedTime);
	if(getBody()->GetLinearVelocity().x > playerVelocityMaxX){
		getBody()->SetLinearVelocity(b2Vec2(playerVelocityMaxX, getBody()->GetLinearVelocity().y));
	}
	if(getBody()->GetLinearVelocity().y > playerVelocityMaxY){
		getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, playerVelocityMaxY));
	}
	if(getBody()->GetLinearVelocity().x < -playerVelocityMaxX){
		getBody()->SetLinearVelocity(b2Vec2(-playerVelocityMaxX, getBody()->GetLinearVelocity().y));
	}
	if(getBody()->GetLinearVelocity().y < -playerVelocityMaxY){
		getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, -playerVelocityMaxY));
	}
}

Player::Player(Game& gameRef, PlayerProperties properties) : playerProperties(properties),
		Entity(gameRef, properties.getEntityProperties()){
	className == ObjectClass::Player;
}