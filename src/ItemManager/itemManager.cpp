//
// Created by capi1500 on 12/07/18.
//

#include <src/Weapon/weapon.hpp>
#include "itemManager.hpp"

void ItemManager::addItem(Item* item){
	items[item->getName()] = item;
}

Item* ItemManager::getItem(std::string name){
	return items[name];
}

const std::map<std::string, Item*>& ItemManager::getItems() const{
	items;
}

bool ItemManager::exist(std::string name){
	return items.find(name) != items.end();
}