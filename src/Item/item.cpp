//
// Created by capi1500 on 12/07/18.
//

#include "item.hpp"

ItemProperties::ItemProperties(){
}

ItemProperties::ItemProperties(PhysicObjectProperties physicObjectProperties, int amount, bool isWorldObject) : PhysicObjectProperties(physicObjectProperties),
		amount(amount),
		isWorldObject(isWorldObject){
}

ItemProperties ItemProperties::getItemProperties(){
	return ItemProperties(getPhysicObjectProperties(), amount, isWorldObject);
}

const ItemProperties& Item::getItemProperties() const{
	return itemProperties;
}

Item::Item(Game& gameRef, ItemProperties properties) : PhysicObject(gameRef, properties.getPhysicObjectProperties()), itemProperties(properties){
	className = ObjectClass::Item;
}