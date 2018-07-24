//
// Created by capi1500 on 19/07/18.
//

#ifndef MAIN_LABEL_HPP
#define MAIN_LABEL_HPP

#include <src/GraphicString/graphicString.hpp>
#include <src/Object/object.hpp>

struct LabelProperties : public ObjectProperties{
	bool displayText;
	
	LabelProperties();
	LabelProperties(ObjectProperties objectProperties, bool displayText = true);
};

class Label : public GraphicString{
	protected:
		LabelProperties labelProperties;
	public:
		LabelProperties& getLabelProperties();
		
		void draw();
		
		Label(Game& gameRef, LabelProperties labelProperties);
};

#endif //MAIN_LABEL_HPP
