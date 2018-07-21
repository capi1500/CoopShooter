//
// Created by capi1500 on 19/07/18.
//

#ifndef MAIN_GRAPHICSTRING_HPP
#define MAIN_GRAPHICSTRING_HPP

#include <src/Object/object.hpp>

struct GraphicStringProperties{
	unsigned lines;
	std::vector<unsigned> length;
	
	void reset();
};

class GraphicString : public Object{
	protected:
		sf::Vector2f startCentre;
		std::string text;
		sf::Color color;
		GraphicStringProperties graphicStringProperties;
		
		void updateStringProperties();
	public:
		void setText(std::string text);
		void setTextColor(sf::Color color);
		void setCentre(sf::Vector2f center);
		sf::FloatRect getTextRect();
		
		virtual void draw();
		
		GraphicString(Game& gameRef, ObjectProperties objectProperties = ObjectProperties());
};

#endif //MAIN_GRAPHICSTRING_HPP
