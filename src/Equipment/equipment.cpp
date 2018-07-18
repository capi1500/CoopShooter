//
// Created by capi1500 on 12/07/18.
//

#include "equipment.hpp"
#include <src/Object/object.hpp>
#include <src/Item/item.hpp>
#include <src/Game/game.hpp>

bool Equipment::addItem(Item* item, int ammount){
	if(equipmentSize == maxEquipmentSize){
		return false;
	}
	equipmentSize++;
	for(unsigned i = 0; i < maxEquipmentSize; i++){
		if(equipment[i].first->getName() == "nothing"){
			equipment[i] = {item, ammount};
			return true;
		}
	}
	return false;
}

void Equipment::removeEquiped(){
	equipment[equiped].first = defaultItem;
	equipment[equiped].second = 1;
	equipmentSize--;
}

bool Equipment::canRemove(){
	return equipment[equiped].first->getName() != "nothing";
}

bool Equipment::equip(int id){
	if(id >= equipment.size())
		return false;
	equiped = id;
	return true;
}

void Equipment::equipNext(){
	equiped++;
	equiped %= maxEquipmentSize;
}

void Equipment::equipPrevious(){
	equiped += maxEquipmentSize;
	equiped--;
	equiped %= maxEquipmentSize;
}

Item* Equipment::getEquiped(){
	return equipment[equiped].first;
}

std::vector<std::pair<Item*, int>>& Equipment::getEquipment(){
	return equipment;
}

void Equipment::draw(Game& gameRef){
	sf::Vector2f position = sf::Vector2f(48 + gameRef.getWindow().getView().getCenter().x - gameRef.getWindow().getSize().x / 2, 48 + gameRef.getWindow().getView().getCenter().y - gameRef.getWindow().getSize().y / 4);
	for(unsigned i = 0; i < maxEquipmentSize; i++){
		Object shape(gameRef, ObjectProperties(position, "", "eqItem"));
		if(i == equiped){
			shape.setTexture("eqItemSelected");
		}
		shape.setScale(2, 2);
		shape.draw();
		if(equipment[i].first->getName() != "nothing"){
			Object sprite(gameRef, ObjectProperties(position, "", equipment[i].first->getObjectProperties().texture));
			sprite.setScale(2, 2);
			sprite.draw();
		}
		position.x += 64;
	}
}

void Equipment::init(Game& gameRef){
	defaultItem = new Item(gameRef, ItemProperties(ObjectProperties(sf::Vector2f(0, 0), "nothing", "")));
	equipment.resize(maxEquipmentSize, {defaultItem, 0});
}

Equipment::Equipment(){
	equipmentSize = 0;
	maxEquipmentSize = 5;
	equiped = 0;
}