//
// Created by capi1500 on 19/07/18.
//

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <vector>
#include <src/Label/label.hpp>

struct MenuProperties : public ObjectProperties{
	bool gameRunning;
	bool gameDraw;
	float opacity;
	bool splitScreen;
	int menuHeight;
	std::vector<Label*> labels;
	
	MenuProperties();
};

class Menu : public Object{
	protected:
		MenuProperties menuProperties;
	public:
		MenuProperties& getMenuProperties();
		
		void addLabel(Label* label);
		void draw();
		void pass(sf::Time elapsedTime);
		void mouseClicked(sf::Vector2f mousePos);
		
		Menu(Game& game, MenuProperties menuProperties = MenuProperties());
};

#endif //MAIN_MENU_HPP
