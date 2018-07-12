//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_EQUIPMENT_HPP
#define COOPSHOOTER_EQUIPMENT_HPP

#include <vector>
#include <src/Item/item.hpp>

class Equipment{
	protected:
		unsigned equipmentSize;
		unsigned equiped;
		std::vector<Item*> equipment;
	public:
		std::vector<Item*>& getEquipment();
		Item* getEquiped();
		
		bool addItem(Item* item);
		bool equip(unsigned id);
		
		Equipment();
};

#endif //COOPSHOOTER_EQUIPMENT_HPP
