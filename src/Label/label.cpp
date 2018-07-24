//
// Created by capi1500 on 19/07/18.
//

#include "label.hpp"
#include <src/Game/game.hpp>

LabelProperties::LabelProperties(ObjectProperties objectProperties, bool displayText) : ObjectProperties(objectProperties){
	this->displayText = displayText;
}

LabelProperties::LabelProperties(){
	displayText = true;
}

void Label::draw(){
	setPosition(getCentre());
	Object::draw();
	if(labelProperties.displayText){
		GraphicString::draw();
	}
}

LabelProperties& Label::getLabelProperties(){
	return labelProperties;
}

Label::Label(Game& gameRef, LabelProperties labelProperties) : GraphicString(gameRef, labelProperties.getObjectProperties()), labelProperties(labelProperties){
	className = ObjectClass::Label;
}