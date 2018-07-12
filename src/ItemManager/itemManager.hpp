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
	public:
		void addItem(Item* item);
		Item* getItem(std::string name);
};

#endif //COOPSHOOTER_ITEMMANAGER_HPP
