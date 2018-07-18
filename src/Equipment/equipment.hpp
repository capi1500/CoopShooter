//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_EQUIPMENT_HPP
#define COOPSHOOTER_EQUIPMENT_HPP

#include <vector>
#include <src/Item/item.hpp>

class Equipment{
	protected:
		Item* defaultItem;
		int equipmentSize;
		int equiped;
		int maxEquipmentSize;
		std::vector<std::pair<Item*, int>> equipment;
	public:
		std::vector<std::pair<Item*, int>>& getEquipment();
		Item* getEquiped();
		
		bool addItem(Item* item, int ammount = 1);
		void removeEquiped();
		bool canRemove();
		bool equip(int id);
		void equipNext();
		void equipPrevious();
		
		void draw(Game& gameRef);
		void init(Game& gameRef);
		
		Equipment();
};

#endif //COOPSHOOTER_EQUIPMENT_HPP
