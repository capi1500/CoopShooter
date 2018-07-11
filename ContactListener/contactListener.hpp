//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_CONTACTLISTENER_HPP
#define COOPSHOOTER_CONTACTLISTENER_HPP

#include <Box2D/Box2D.h>

class Game;

class ContactListener : public b2ContactListener{
	private:
		Game& gameRef;
	public:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		
		ContactListener(Game& gameRef);
};

#endif //COOPSHOOTER_CONTACTLISTENER_HPP
