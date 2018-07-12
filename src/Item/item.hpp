//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_ITEM_HPP
#define COOPSHOOTER_ITEM_HPP

#include <src/PhysicObject/physicObject.hpp>

struct ItemProperties : public PhysicObjectProperties{
	int amount;
	bool isWorldObject;
	
	ItemProperties getItemProperties();
	
	ItemProperties();
	ItemProperties(PhysicObjectProperties physicObjectProperties, int amount, bool isWorldObject);
};

class Item : public PhysicObject{
	protected:
		ItemProperties itemProperties;
	public:
		const ItemProperties& getItemProperties() const;
		
		Item(Game& gameRef, ItemProperties properties);
};

#endif //COOPSHOOTER_ITEM_HPP
