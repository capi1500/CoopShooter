//
// Created by capi1500 on 05/09/18.
//

#ifndef MAIN_EDITOR_HPP
#define MAIN_EDITOR_HPP

class Game;

class Editor{
	private:
		Game& gameRef;
	public:
		void draw();
		
		Editor(Game& game);
};

#endif //MAIN_EDITOR_HPP
