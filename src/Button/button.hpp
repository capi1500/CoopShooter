//
// Created by capi1500 on 21/07/18.
//

#ifndef MAIN_BUTTON_HPP
#define MAIN_BUTTON_HPP

#include <src/Label/label.hpp>

struct ButtonProperties : public LabelProperties{
	Event onClick;
	bool isClicked;
	
	ButtonProperties(LabelProperties labelProperties, Event onClick, bool clicked = false);
	ButtonProperties();
};

class Button : public Label{
	protected:
		ButtonProperties buttonProperties;
	public:
		ButtonProperties& getButtonProperties();
		
		void pass(sf::Time elapsedTime);
		void onClick();
		
		Button(Game& gameRef, ButtonProperties buttonProperties);
};

#endif //MAIN_BUTTON_HPP
