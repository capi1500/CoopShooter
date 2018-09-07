//
// Created by capi1500 on 19/07/18.
//

#ifndef MAIN_MENUMANAGER_HPP
#define MAIN_MENUMANAGER_HPP

#include <string>
#include <src/Menu/menu.hpp>

class Game;

class MenuManager{
	private:
		Game& gameRef;
		std::string active;
		std::map<std::string, Menu*> menus;
	public:
		void addMenu(std::string name);
		void addMenu(std::string name, Menu* menu);
		Menu* getMenu(std::string name);
		bool exitst(std::string name);
		Menu* getActive();
		bool setActive(std::string name);
		std::string getActiveName();
		void clear();
		
		MenuManager(Game& game);
};

#endif //MAIN_MENUMANAGER_HPP
