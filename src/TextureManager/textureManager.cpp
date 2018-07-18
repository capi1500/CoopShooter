//
// Created by capi1500 on 10/07/18.
//

#include "textureManager.hpp"

void TextureManager::addTexture(std::string path, std::string name, sf::IntRect rect){
	textures[name].loadFromFile(path, rect);
}

sf::Texture& TextureManager::getTexture(std::string name){
	return textures[name];
}