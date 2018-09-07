//
// Created by capi1500 on 12/07/18.
//

#include "item.hpp"

ItemProperties::ItemProperties(){
	textureOnEquip = "nothing";
	isSpawnable = false;
	amount = 0;
	isWorldObject = false;
}

ItemProperties::ItemProperties(ObjectProperties objectProperties) : ObjectProperties(objectProperties){
	textureOnEquip = "nothing";
	isSpawnable = false;
	amount = 0;
	isWorldObject = false;
}

ItemProperties ItemProperties::getItemProperties(){
	ItemProperties itemProperties = ItemProperties(getObjectProperties());
	itemProperties.textureOnEquip = textureOnEquip;
	itemProperties.isSpawnable = isSpawnable;
	itemProperties.amount = amount;
	itemProperties.isWorldObject = isWorldObject;
	return itemProperties;
}

void ItemProperties::setObjectProperties(ObjectProperties& objectProperties){
	position = objectProperties.position;
	name = objectProperties.name;
	texture = objectProperties.texture;
}

const ItemProperties& Item::getItemProperties() const{
	return itemProperties;
}

Item::Item(Game& gameRef, ItemProperties properties) : Object(gameRef, properties.getObjectProperties()), itemProperties(properties){
	className = ObjectClass::Item;
}