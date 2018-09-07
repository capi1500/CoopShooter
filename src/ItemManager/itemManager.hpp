//
// Created by capi1500 on 12/07/18.
//

#ifndef COOPSHOOTER_ITEMMANAGER_HPP
#define COOPSHOOTER_ITEMMANAGER_HPP

#include <string>
#include <src/Item/item.hpp>

class ItemManager{
	private:
		std::map<std::string, Item*> items;
		std::vector<Item*> spawnableItems;
	public:
		void addItem(Item* item);
		Item* getItem(std::string name);
		const std::vector<Item*> getSpawnables() const;
		const std::map<std::string, Item*>& getItems() const;
		bool exist(std::string name);
		void clear();
};

#endif //COOPSHOOTER_ITEMMANAGER_HPP
