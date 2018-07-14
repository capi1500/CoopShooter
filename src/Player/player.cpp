//
// Created by capi1500 on 11/07/18.
//

#include "player.hpp"
#include <src/Game/game.hpp>

PlayerProperties::PlayerProperties(){
	movementSpeed = playerMovement;
	jumpHeight = playerJumpHeight;
}

PlayerProperties::PlayerProperties(EntityProperites properites) : EntityProperites(properites){
}

PlayerProperties PlayerProperties::getPlayerProperties(){
	return PlayerProperties(getEntityProperties());
}

void PlayerProperties::setEntityProperties(EntityProperites entityProperites){
	maxHP = entityProperites.maxHP;
	HP = entityProperites.HP;
	jumpHeight = entityProperites.jumpHeight;
	movementSpeed = entityProperites.movementSpeed;
	isFacingLeft = entityProperites.isFacingLeft;
	isDead = entityProperites.isDead;
	equipment = entityProperites.equipment;
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
	if(getEquiped()->getClassName() == ObjectClass::Weapon){
		if(dynamic_cast<Weapon*>(getEquiped())->getWeaponProperties().ammo == 0){
			ammoBar.setTextureRect(sf::IntRect(0, 56, 28, 8));
		}
		else{
			ammoBar.setTextureRect(sf::IntRect(0, (7 - static_cast<int>(7 * std::max(1.0 / 7, (static_cast<double>(dynamic_cast<Weapon*>(getEquiped())->getWeaponProperties().ammo) / dynamic_cast<Weapon*>(getEquiped())->getWeaponProperties().maxAmmo)))) * 8, 28, 8));
		}
	}
	ammoBar.setPosition(getCentre().x - getGlobalBounds().width / 2 - 14, getGlobalBounds().top - 24);
}

void Player::drawAmmo(){
	if(entityProperites.HP != 0 and getEquiped()->getClassName() == ObjectClass::Weapon){
		gameRef.getWindow().draw(ammoBar);
	}
}

Player::Player(Game& gameRef, PlayerProperties properties) : playerProperties(properties),
		Entity(gameRef, properties.getEntityProperties()){
	ammoBar.setTexture(gameRef.getTextureManager().getTexture("ammoBar"));
	className == ObjectClass::Player;
}