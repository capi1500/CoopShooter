//
// Created by capi1500 on 10/07/18.
//

#include "textureManager.hpp"

void TextureManager::addTexture(std::string path, std::string name, sf::IntRect rect){
	textures[name].loadFromFile(path, rect);
	areas[name] = rect;
	paths[name] = path;
}

sf::Texture& TextureManager::getTexture(std::string name){
	return textures[name];
}

sf::IntRect& TextureManager::getArea(std::string name){
	return areas[name];
}

void TextureManager::clear(){
	textures.clear();
	areas.clear();
	paths.clear();
}

const std::map<std::string, std::string>& TextureManager::getTexturePaths() const{
	return paths;
}