//
// Created by capi1500 on 12/07/18.
//

#include "weapon.hpp"

WeaponProperties::WeaponProperties(){
	reloading = false;
	ammo = -1;
	bulletTexture = "bullet";
	bulletDistance = 10;
	shotSound = "";
}

WeaponProperties::WeaponProperties(ItemProperties itemProperties, sf::Time delay, int dmg, int bulletSpeed, int ammo, sf::Time reloadSpeed, std::string bulletTexture, float bulletDistance) : ItemProperties(itemProperties), attackDelay(delay), dmg(dmg), bulletSpeed(bulletSpeed), maxAmmo(ammo), reloadSpeed(reloadSpeed), bulletTexture(bulletTexture), bulletDistance(bulletDistance){
	this->ammo = this->maxAmmo;
	reloading = false;
}

WeaponProperties WeaponProperties::getWeaponProperties(){
	return WeaponProperties(getItemProperties(), attackDelay, dmg, bulletSpeed, ammo, reloadSpeed, bulletTexture, bulletDistance);
}

void WeaponProperties::setItemProperties(ItemProperties itemProperties){
	amount = itemProperties.amount;
	isWorldObject = itemProperties.isWorldObject;
	textureOnEquip = itemProperties.textureOnEquip;
}

WeaponProperties& Weapon::getWeaponProperties(){
	return weaponProperties;
}

bool Weapon::canShoot(){
	if(weaponProperties.reloading or weaponProperties.ammo <= 0){
		return false;
	}
	return true;
}

void Weapon::shoot(){
	weaponProperties.ammo -= 1;
}

void Weapon::pass(sf::Time elapsedTime){
	Item::pass(elapsedTime);
	weaponProperties.timeSinceReloadStarted += elapsedTime;
	if(weaponProperties.ammo == 0 and not weaponProperties.reloading){
		weaponProperties.timeSinceReloadStarted = sf::seconds(0);
		weaponProperties.reloading = true;
	}
	if(weaponProperties.reloading and weaponProperties.timeSinceReloadStarted >= weaponProperties.reloadSpeed){
		weaponProperties.reloading = false;
		weaponProperties.ammo = weaponProperties.maxAmmo;
	}
}

Weapon::Weapon(Weapon weapon, int ammo, int time) : Item(weapon.gameRef, weapon.getItemProperties()), weaponProperties(weapon.getWeaponProperties()){
	weaponProperties.ammo = ammo;
	weaponProperties.timeSinceReloadStarted = sf::milliseconds(time);
	if(weaponProperties.ammo == 0 and not weaponProperties.reloading){
		weaponProperties.reloading = true;
	}
	className = ObjectClass::Weapon;
}

Weapon::Weapon(Game& gameRef, WeaponProperties weaponProperties) : Item(gameRef, weaponProperties.getItemProperties()), weaponProperties(weaponProperties){
	className = ObjectClass::Weapon;
}