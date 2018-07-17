//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_EQUIPMENT_HPP
#define COOPSHOOTER_EQUIPMENT_HPP

#include <vector>
#include <src/Item/item.hpp>

class Equipment{
	protected:
		int equipmentSize;
		int equiped;
		std::vector<std::pair<Item*, int>> equipment;
	public:
		std::vector<std::pair<Item*, int>>& getEquipment();
		Item* getEquiped();
		
		bool addItem(Item* item, int ammount = 1);
		bool equip(int id);
		void equipNext();
		void equipPrevious();
		
		Equipment();
};

#endif //COOPSHOOTER_EQUIPMENT_HPP
