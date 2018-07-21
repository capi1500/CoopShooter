//
// Created by capi1500 on 19/07/18.
//

#include "label.hpp"
#include <src/Game/game.hpp>

void Label::draw(){
	setPosition(getCentre());
	Object::draw();
	if(displayText){
		GraphicString::draw();
	}
}

Label::Label(Game& gameRef, ObjectProperties objectProperties, bool displayText) : GraphicString(gameRef, objectProperties){
	className = ObjectClass::Label;
	this->displayText = displayText;
}