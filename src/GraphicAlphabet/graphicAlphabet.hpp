//
// Created by capi1500 on 18/07/18.
//

#ifndef MAIN_GRAPHICALPHABET_HPP
#define MAIN_GRAPHICALPHABET_HPP

#include <src/Game/game.hpp>

class GraphicAlphabet{
	private:
		Game& gameRef;
		sf::Image alphabet;
		std::map<char, sf::IntRect> charRectangles;
		unsigned width;
		unsigned height;
	public:
	
};

#endif //MAIN_GRAPHICALPHABET_HPP
