//
// Created by capi1500 on 12/07/18.
//

#include "itemManager.hpp"

void ItemManager::addItem(Item* item){
	items[item->getName()] = item;
}

Item* ItemManager::getItem(std::string name){
	return items[name];
}