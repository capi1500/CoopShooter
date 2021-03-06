//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_TEXTUREMANAGER_HPP
#define COOPSHOOTER_TEXTUREMANAGER_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager{
	private:
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, std::string> paths;
		std::map<std::string, sf::IntRect> areas;
	public:
		void addTexture(std::string path, std::string name, sf::IntRect rect);
		sf::Texture& getTexture(std::string name);
		sf::IntRect& getArea(std::string name);
		const std::map<std::string, std::string>& getTexturePaths() const;
		void clear();
};

#endif //COOPSHOOTER_TEXTUREMANAGER_HPP
