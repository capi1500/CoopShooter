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
	float distance;
	
	BulletProperties getBulletProperties();
	BulletProperties();
	BulletProperties(PhysicObjectProperties physicObjectProperties, int bulletSpeed, int dmg, float distance);
};

class Bullet : public PhysicObject{
	protected:
		BulletProperties bulletProperties;
		sf::Vector2f startPostion;
	public:
		BulletProperties& getBulletProperties();
		
		void pass(sf::Time elapsedTime);
		bool canHit();
		
		Bullet(Game& gameRef, BulletProperties bulletProperties);
};

#endif //COOPSHOOTER_BULLET_HPP
