//
// Created by capi1500 on 12/07/18.
//

#include <src/Weapon/weapon.hpp>
#include "itemManager.hpp"

void ItemManager::addItem(Item* item){
	items[item->getName()] = item;
	if(item->getItemProperties().isSpawnable){
		spawnableItems.push_back(item);
	}
}

Item* ItemManager::getItem(std::string name){
	return items[name];
}

const std::map<std::string, Item*>& ItemManager::getItems() const{
	return items;
}

const std::vector<Item*> ItemManager::getSpawnables() const{
	return spawnableItems;
}

bool ItemManager::exist(std::string name){
	return items.find(name) != items.end();
}

void ItemManager::clear(){
	spawnableItems.clear();
	items.clear();
}