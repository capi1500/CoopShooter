//
// Created by capi1500 on 18/07/18.
//

#ifndef MAIN_GRAPHICALPHABET_HPP
#define MAIN_GRAPHICALPHABET_HPP

#include <SFML/Graphics/Image.hpp>
#include <map>

class Game;

class GraphicAlphabet{
	private:
		Game& gameRef;
		sf::Image alphabet;
		std::map<char, sf::IntRect> charRectangles;
		unsigned width;
		unsigned height;
	public:
		void drawChar(char val, sf::Vector2f position, sf::Vector2f localScale, sf::Color color = sf::Color(255, 255, 255));
		const unsigned int getHeight() const;
		const unsigned int getWidth() const;
		
		GraphicAlphabet(Game& gameRef);
};

#endif //MAIN_GRAPHICALPHABET_HPP
