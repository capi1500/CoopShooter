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
	sf::Time reloadSpeed;
	int maxAmmo;
	int ammo;
	bool reloading;
	
	WeaponProperties getWeaponProperties();
	
	WeaponProperties();
	WeaponProperties(ItemProperties itemProperties, sf::Time delay, int dmg, int bulletSpeed, int ammo, sf::Time reloadSpeed);
};

class Weapon : public Item{
	protected:
		sf::Time timeSinceReloadStarted;
		WeaponProperties weaponProperties;
	public:
		const WeaponProperties& getWeaponProperties() const;
		
		void pass(sf::Time elapsedTime);
		bool canShoot();
		void shoot();
		
		Weapon(Game& gameRef, WeaponProperties weaponProperties);
};

#endif //COOPSHOOTER_WEAPON_HPP
