//
// Created by capi1500 on 19/07/18.
//

#ifndef MAIN_LABEL_HPP
#define MAIN_LABEL_HPP

#include <src/GraphicString/graphicString.hpp>

class Label : public GraphicString{
	protected:
		bool displayText;
	public:
		void draw();
		
		Label(Game& gameRef, ObjectProperties objectProperties, bool displayText = true);
};

#endif //MAIN_LABEL_HPP
