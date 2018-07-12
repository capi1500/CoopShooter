//
// Created by capi1500 on 12/07/18.
//

#include "weapon.hpp"

WeaponProperties::WeaponProperties(){
}

WeaponProperties::WeaponProperties(ItemProperties itemProperties, sf::Time delay, int dmg, int bulletSpeed) : ItemProperties(itemProperties), attackDelay(delay), dmg(dmg), bulletSpeed(bulletSpeed){
}

WeaponProperties WeaponProperties::getWeaponProperties(){
	return WeaponProperties(getItemProperties(), attackDelay, dmg, bulletSpeed);
}

const WeaponProperties& Weapon::getWeaponProperties() const{
	return weaponProperties;
}

Weapon::Weapon(Game& gameRef, WeaponProperties weaponProperties) : Item(gameRef, weaponProperties.getItemProperties()), weaponProperties(weaponProperties){
	className = ObjectClass::Weapon;
}