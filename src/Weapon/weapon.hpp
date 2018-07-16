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
	std::string bulletTexture;
	
	WeaponProperties getWeaponProperties();
	void setItemProperties(ItemProperties itemProperties);
	
	WeaponProperties();
	WeaponProperties(ItemProperties itemProperties, sf::Time delay, int dmg, int bulletSpeed, int ammo, sf::Time reloadSpeed, std::string bulletTexture);
};

class Weapon : public Item{
	protected:
		sf::Time timeSinceReloadStarted;
		WeaponProperties weaponProperties;
	public:
		WeaponProperties& getWeaponProperties();
		
		void pass(sf::Time elapsedTime);
		bool canShoot();
		void shoot();
		
		Weapon(Game& gameRef, WeaponProperties weaponProperties);
};

#endif //COOPSHOOTER_WEAPON_HPP
