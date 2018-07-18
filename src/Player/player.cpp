//
// Created by capi1500 on 11/07/18.
//

#include "player.hpp"
#include <src/Game/game.hpp>

PlayerProperties::PlayerProperties(){
	movementSpeed = playerMovement;
	jumpHeight = playerJumpHeight;
	textureBase = "nothing";
	textureHair = "nothing";
	textureBoots = "nothing";
	textureLegs = "nothing";
	textureGloves = "nothing";
	textureBody = "nothing";
	textureHandRight = "nothing";
	textureCloack = "nothing";
	textureBeard = "nothing";
}

PlayerProperties::PlayerProperties(EntityProperites properites) : EntityProperites(properites){
	textureBase = "nothing";
	textureHair = "nothing";
	textureBoots = "nothing";
	textureLegs = "nothing";
	textureGloves = "nothing";
	textureBody = "nothing";
	textureHandRight = "nothing";
	textureCloack = "nothing";
	textureBeard = "nothing";
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
	if(not entityProperites.isDead){
		if(getEquiped()->getClassName() == ObjectClass::Weapon){
			gameRef.getWindow().draw(ammoBar);
		}
	}
}

void Player::drawEquipment(){
	entityProperites.equipment.draw(gameRef);
}

void Player::draw(){
	if(not entityProperites.isDead){
		Entity::draw();
		Object drawHelp(gameRef, ObjectProperties(sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top), "help", ""));
		if(entityProperites.isFacingLeft){
			drawHelp.setScale(sf::Vector2f(1, 1));
		}
		else{
			drawHelp.setScale(sf::Vector2f(-1, 1));
			drawHelp.move(sf::Vector2f(getGlobalBounds().width, 0));
		}
		playerProperties.textureHandRight = getEquiped()->getItemProperties().textureOnEquip;
		//printf("'%s'\n", playerProperties.textureHandRight.c_str());
		std::vector<std::string> toDraw = {playerProperties.textureCloack, playerProperties.textureBeard,
										   playerProperties.textureHair, playerProperties.textureBoots,
										   playerProperties.textureLegs, playerProperties.textureGloves,
										   playerProperties.textureBody};
		for(auto i : toDraw){
			if(i != "nothing"){
				drawHelp.setTexture(i);
				drawHelp.draw();
			}
		}
		if(playerProperties.textureHandRight != "nothing"){
			if(entityProperites.isFacingLeft){
				drawHelp.setScale(sf::Vector2f(-1, 1));;
				drawHelp.move(sf::Vector2f(getGlobalBounds().width, 0));
			}
			else{
				drawHelp.setScale(sf::Vector2f(1, 1));
				drawHelp.move(sf::Vector2f(-getGlobalBounds().width, 0));
			}
			drawHelp.setTexture(playerProperties.textureHandRight);
			drawHelp.draw();
		}
	}
}

Player::Player(Game& gameRef, PlayerProperties properties) : playerProperties(properties),
		Entity(gameRef, properties.getEntityProperties()){
	ammoBar.setTexture(gameRef.getTextureManager().getTexture("ammoBar"));
	className == ObjectClass::Player;
}