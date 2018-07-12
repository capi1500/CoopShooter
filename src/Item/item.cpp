//
// Created by capi1500 on 12/07/18.
//

#include "item.hpp"

ItemProperties::ItemProperties(){
}

ItemProperties::ItemProperties(ObjectProperties objectProperties) : ObjectProperties(objectProperties){
}

ItemProperties ItemProperties::getItemProperties(){
	return ItemProperties(getObjectProperties());
}

const ItemProperties& Item::getItemProperties() const{
	return itemProperties;
}

Item::Item(Game& gameRef, ItemProperties properties) : Object(gameRef, properties.getObjectProperties()), itemProperties(properties){
	className = ObjectClass::Item;
}