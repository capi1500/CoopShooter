//
// Created by capi1500 on 11/07/18.
//

#include "contactListener.hpp"
#include <src/Game/game.hpp>

void ContactListener::BeginContact(b2Contact* contact){
	std::string* nameA = static_cast<std::string*>(contact->GetFixtureA()->GetBody()->GetUserData());
	std::string* nameB = static_cast<std::string*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if(nameA->substr(0, 6) == "bullet"){
		gameRef.getEventManager().addEvent(Event("bulletHit", *nameA, *nameB));
	}
	if(nameB->substr(0, 6) == "bullet"){
		gameRef.getEventManager().addEvent(Event("bulletHit", *nameB, *nameA));
	}
	if(nameA->substr(0, 12) == "collectibleW"){
		gameRef.getEventManager().addEvent(Event("collectSth", *nameA, *nameB));
	}
	if(nameB->substr(0, 12) == "collectibleW"){
		gameRef.getEventManager().addEvent(Event("collectSth", *nameB, *nameA));
	}
}

void ContactListener::EndContact(b2Contact* contact){

}

ContactListener::ContactListener(Game& gameRef) : gameRef(gameRef){
}