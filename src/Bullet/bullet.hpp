//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_BULLET_HPP
#define COOPSHOOTER_BULLET_HPP

#include <src/PhysicObject/physicObject.hpp>

struct BulletProperties : PhysicObjectProperties{
	int speed;
	int dmg;
	bool isFacingLeft;
	
	BulletProperties getBulletProperties();
	BulletProperties();
	BulletProperties(PhysicObjectProperties physicObjectProperties, int bulletSpeed, int dmg);
};

class Bullet : public PhysicObject{
	protected:
		BulletProperties bulletProperties;
	public:
		BulletProperties& getBulletProperties();
		
		void pass(sf::Time elapsedTime);
		
		Bullet(Game& gameRef, BulletProperties bulletProperties);
};

#endif //COOPSHOOTER_BULLET_HPP
