//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_BULLET_HPP
#define COOPSHOOTER_BULLET_HPP

#include <src/PhysicObject/physicObject.hpp>

struct BulletProperties : PhysicObjectProperties{
	
	BulletProperties getBulletProperties();
	
	BulletProperties();
	BulletProperties(PhysicObjectProperties physicObjectProperties);
};

class Bullet : public PhysicObject{
	protected:
		BulletProperties bulletProperties;
	public:
		const BulletProperties getBulletProperties() const;
		
		void pass(sf::Time elapsedTime);
		
		Bullet(Game& gameRef, BulletProperties bulletProperties);
};

#endif //COOPSHOOTER_BULLET_HPP
