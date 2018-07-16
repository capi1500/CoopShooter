//
// Created by capi1500 on 11/07/18.
//

#include "bullet.hpp"
#include <src/Game/game.hpp>

BulletProperties::BulletProperties(){
}

BulletProperties::BulletProperties(PhysicObjectProperties physicObjectProperties, int bulletSpeed, int dmg) : PhysicObjectProperties(physicObjectProperties), speed(bulletSpeed), dmg(dmg){
}

BulletProperties BulletProperties::getBulletProperties(){
	return BulletProperties(getPhysicObjectProperties(), speed, dmg);
}

BulletProperties& Bullet::getBulletProperties(){
	return bulletProperties;
}

void Bullet::pass(sf::Time elapsedTime){
	PhysicObject::pass(elapsedTime);
	if(getBody()->GetLinearVelocity().x > 0){
		getBody()->SetLinearVelocity(b2Vec2(bulletProperties.speed, 0));
		bulletProperties.isFacingLeft = true;
		setScale(sf::Vector2f(1, 1));
	}
	else{
		getBody()->SetLinearVelocity(b2Vec2(-bulletProperties.speed, 0));
		bulletProperties.isFacingLeft = false;
		setScale(sf::Vector2f(-1, 1));
	}
}

Bullet::Bullet(Game& gameRef, BulletProperties bulletProperties) : PhysicObject(gameRef, bulletProperties), bulletProperties(bulletProperties){
	className = ObjectClass::Bullet;
	getBody()->SetBullet(true);
	getBody()->SetFixedRotation(true);
	b2Filter filter;
	filter.categoryBits = 1;
	filter.maskBits = 2;
	getBody()->GetFixtureList()->SetFilterData(filter);
}