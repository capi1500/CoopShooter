//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_ITEM_HPP
#define COOPSHOOTER_ITEM_HPP

#include <src/PhysicObject/physicObject.hpp>

struct ItemProperties : public ObjectProperties{
	int amount;
	bool isWorldObject;
	std::string textureOnEquip;
	bool isSpawnable;
	
	ItemProperties getItemProperties();
	void setObjectProperties(ObjectProperties& objectProperties);
	
	ItemProperties();
	ItemProperties(ObjectProperties objectProperties);
};

class Item : public Object{
	protected:
		ItemProperties itemProperties;
	public:
		const ItemProperties& getItemProperties() const;
		
		Item(Game& gameRef, ItemProperties properties);
};

#endif //COOPSHOOTER_ITEM_HPP
