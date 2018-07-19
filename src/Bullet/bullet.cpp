//
// Created by capi1500 on 11/07/18.
//

#include "bullet.hpp"
#include <src/Game/game.hpp>

BulletProperties::BulletProperties(){
}

BulletProperties::BulletProperties(PhysicObjectProperties physicObjectProperties, int bulletSpeed, int dmg, float distance, sf::Vector2f position) : PhysicObjectProperties(physicObjectProperties), speed(bulletSpeed), dmg(dmg), distance(distance), startPosition(position){
}

BulletProperties BulletProperties::getBulletProperties(){
	return BulletProperties(getPhysicObjectProperties(), speed, dmg, distance, startPosition);
}

BulletProperties& Bullet::getBulletProperties(){
	return bulletProperties;
}

void BulletProperties::setPhysicBulletProperties(PhysicObjectProperties physicObjectProperties){
	type = physicObjectProperties.type;
	shape = physicObjectProperties.shape;
	density = physicObjectProperties.density;
	friction = physicObjectProperties.friction;
	angle = physicObjectProperties.angle;
	velocity = physicObjectProperties.velocity;
}

void Bullet::pass(sf::Time elapsedTime){
	PhysicObject::pass(elapsedTime);
	if(getBody()->GetLinearVelocity().x > 0){
		getBody()->SetLinearVelocity(b2Vec2(pixelToMeter(bulletProperties.speed), 0));
		bulletProperties.isFacingLeft = true;
		setScale(sf::Vector2f(1, 1));
	}
	else{
		getBody()->SetLinearVelocity(b2Vec2(-pixelToMeter(bulletProperties.speed), 0));
		bulletProperties.isFacingLeft = false;
		setScale(sf::Vector2f(-1, 1));
	}
	if(std::abs(getCentre().x - bulletProperties.startPosition.x) >= bulletProperties.distance){
		gameRef.getEventManager().addEvent(Event("bulletHit", getName()));
	}
	getBody()->SetTransform(b2Vec2(getBody()->GetPosition().x, pixelToMeter(bulletProperties.startPosition.y)), getBody()->GetAngle());
}

bool Bullet::canHit(){
	return true;
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