//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_WEAPON_HPP
#define COOPSHOOTER_WEAPON_HPP

#include <src/Item/item.hpp>

struct WeaponProperties : public ItemProperties{
	sf::Time attackDelay;
	int bulletSpeed;
	int dmg;
	
	WeaponProperties getWeaponProperties();
	
	WeaponProperties();
	WeaponProperties(ItemProperties itemProperties, sf::Time delay, int dmg, int bulletSpeed);
};

class Weapon : public Item{
	protected:
		WeaponProperties weaponProperties;
	public:
		const WeaponProperties& getWeaponProperties() const;
		
		Weapon(Game& gameRef, WeaponProperties weaponProperties);
};

#endif //COOPSHOOTER_WEAPON_HPP
