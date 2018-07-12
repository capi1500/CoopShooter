//
// Created by capi1500 on 12/07/18.
//

#include "equipment.hpp"
#include <src/Item/item.hpp>

bool Equipment::addItem(Item* item, int ammount){
	if(equipment.size() == equipmentSize){
		return false;
	}
	equipment.push_back({item, ammount});
	return true;
}

bool Equipment::equip(unsigned id){
	if(id >= equipment.size())
		return false;
	equiped = id;
	return true;
}

Item* Equipment::getEquiped(){
	return equipment[equiped].first;
}

std::vector<std::pair<Item*, int>>& Equipment::getEquipment(){
	return equipment;
}

Equipment::Equipment(){
	equipmentSize = 5;
	equiped = 0;
}