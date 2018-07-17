//
// Created by capi1500 on 12/07/18.
//

#include "equipment.hpp"
#include <src/Item/item.hpp>

bool Equipment::addItem(Item* item, int ammount){
	equipmentSize++;
	equipment.push_back({item, ammount});
	return true;
}

bool Equipment::equip(int id){
	if(id >= equipment.size())
		return false;
	equiped = id;
	return true;
}

void Equipment::equipNext(){
	equiped++;
	equiped %= equipmentSize;
}

void Equipment::equipPrevious(){
	equiped += equipmentSize;
	equiped--;
	equiped %= equipmentSize;
}

Item* Equipment::getEquiped(){
	return equipment[equiped].first;
}

std::vector<std::pair<Item*, int>>& Equipment::getEquipment(){
	return equipment;
}

Equipment::Equipment(){
	equipmentSize = 0;
	equiped = 0;
}