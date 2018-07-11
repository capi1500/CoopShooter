//
// Created by capi1500 on 11/07/18.
//

#include "bullet.hpp"
#include <src/Game/game.hpp>

BulletProperties::BulletProperties(){
}

BulletProperties::BulletProperties(PhysicObjectProperties physicObjectProperties) : PhysicObjectProperties(physicObjectProperties){
}

BulletProperties BulletProperties::getBulletProperties(){
	return BulletProperties(getPhysicObjectProperties());
}

const BulletProperties Bullet::getBulletProperties() const{
	return bulletProperties;
}

void Bullet::pass(sf::Time elapsedTime){
	PhysicObject::pass(elapsedTime);
	if(getBody()->GetLinearVelocity().x > 0){
		getBody()->SetLinearVelocity(b2Vec2(bulletSpeed, 0));
	}
	else{
		getBody()->SetLinearVelocity(b2Vec2(-bulletSpeed, 0));
	}
	for(auto obj = gameRef.getWorld().getEntities().begin(); obj != gameRef.getWorld().getEntities().end(); obj++){
		if(obj->second->getGlobalBounds().intersects(getGlobalBounds())){
			gameRef.getEventManager().addEvent(Event("bulletHit", getName(), obj->second->getName()));
		}
	}
}

Bullet::Bullet(Game& gameRef, BulletProperties bulletProperties) : PhysicObject(gameRef, bulletProperties){
	className = ObjectClass::Bullet;
	getBody()->SetBullet(true);
	getBody()->SetFixedRotation(true);
}