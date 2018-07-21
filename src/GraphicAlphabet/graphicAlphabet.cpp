//
// Created by capi1500 on 18/07/18.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <config.h>
#include "graphicAlphabet.hpp"
#include <src/Game/game.hpp>

void GraphicAlphabet::drawChar(char val, sf::Vector2f position, sf::Vector2f localScale, sf::Color color){
	if(val == ' ' or val == '\t' or val == '\n')
		return;
	sf::Texture texture;
	texture.loadFromImage(alphabet, charRectangles[val]);
	Object sprite(gameRef, ObjectProperties());
	sprite.setTexture(texture);
	sprite.setCentre(position);
	sprite.setColor(color);
	sprite.setScale(lettersScaling * localScale.x, lettersScaling * localScale.y);
	gameRef.getWindow().draw(sprite);
}

const unsigned int GraphicAlphabet::getHeight() const{
	return height;
}

const unsigned int GraphicAlphabet::getWidth() const{
	return width;
}

GraphicAlphabet::GraphicAlphabet(Game& gameRef) : gameRef(gameRef){
	if(not alphabet.loadFromFile("Assets/Fonts/font-20x20-RPG.png")){
		throw "Error, can not load font textures\n";
	}
	width = height = 20;
	int i = 0, j = 0;
	for(auto c : std::vector<char>{
			'\t', '!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.',
			'/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
			'>', '?', '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
			'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[',
			'\\', ']', '^', '_', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
			'Z', '{', '|', '}', '~', '\n'
	}){
		charRectangles[c] = sf::IntRect((i % 15) * width, j * height, width, height);
		i++;
		if(i % 15 == 0)
			j++;
	}
}