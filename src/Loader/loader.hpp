//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_LOADER_HPP
#define COOPSHOOTER_LOADER_HPP

#include <string>

class Game;

class Loader{
	private:
		Game& gameRef;
	public:
		void load(std::string path);
		void save(std::string path);
		
		Loader(Game& gameRef);
};

#endif //COOPSHOOTER_LOADER_HPP
