//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_EVENTMANAGER_HPP
#define COOPSHOOTER_EVENTMANAGER_HPP

#include <queue>
#include <SFML/Window/Event.hpp>
#include <src/Event/event.hpp>

class Game;

class EventManager{
	private:
		Game& gameRef;
		std::queue<Event> events;
	public:
		void addEvent(Event);
		void handleEvents(sf::Event);
		void handleEvents();
		
		EventManager(Game&);
};

#endif //COOPSHOOTER_EVENTMANAGER_HPP
