//
// Created by capi1500 on 19/07/18.
//

#include "menuManager.hpp"

void MenuManager::addMenu(std::string name){
	menus[name] = new Menu(gameRef);
}

void MenuManager::addMenu(std::string name, Menu* menu){
	menus[name] = menu;
}

bool MenuManager::exitst(std::string name){
	return menus.find(name) != menus.end();
}

Menu* MenuManager::getMenu(std::string name){
	return menus[name];
}

Menu* MenuManager::getActive(){
	return menus[active];
}

bool MenuManager::setActive(std::string name){
	if(exitst(name)){
		active = name;
		return true;
	}
	return false;
}

std::string MenuManager::getActiveName(){
	return active;
}

void MenuManager::clear(){
	menus.clear();
}

MenuManager::MenuManager(Game& game) : gameRef(game){
}