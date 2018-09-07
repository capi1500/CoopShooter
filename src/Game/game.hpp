//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_GAME_HPP
#define COOPSHOOTER_GAME_HPP

#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <src/World/world.hpp>
#include <src/Loader/loader.hpp>
#include <src/Entity/entity.hpp>
#include <src/PhysicObject/physicObject.hpp>
#include <src/Object/object.hpp>
#include <src/TextureManager/textureManager.hpp>
#include <src/EventManager/eventManager.hpp>
#include <src/SoundManager/soundManager.hpp>
#include <src/Enum/enum.hpp>
#include <config.h>
#include <src/ContactListener/contactListener.hpp>
#include <src/ItemManager/itemManager.hpp>
#include <src/TemplateManager/templateManager.hpp>
#include <src/GraphicAlphabet/graphicAlphabet.hpp>
#include <src/GraphicString/graphicString.hpp>
#include <src/MenuManager/menuManager.hpp>
#include <src/Editor/editor.hpp>

class Game{
	private:
		GameState state;
		
		sf::RenderWindow window;
		b2World physicWorld;
		ContactListener contactListener;
		World world;
		EventManager eventManager;
		SoundManager soundManager;
		TextureManager textureManager;
		TemplateManager templateManager;
		ItemManager itemManager;
		Loader loader;
		GraphicAlphabet graphicAlphabet;
		MenuManager menuManager;
		Editor editor;
		
		sf::Clock clock;
		sf::Time time;
		sf::View player1view;
		sf::View player2view;
		sf::View cameraView;
		float cameraZoom;
		sf::View fullScreenView;
		sf::Music music;
		bool timeSet;
	public:
		sf::RenderWindow& getWindow();
		b2World& getPhysicWorld();
		ContactListener& getContactListener();
		World& getWorld();
		EventManager& getEventManager();
		SoundManager& getSoundManager();
		TextureManager& getTextureManager();
		Loader& getLoader();
		ItemManager& getItemManager();
		TemplateManager& getTemplateManager();
		sf::View& getPlayer1View();
		sf::View& getPlayer2View();
		sf::View& getCameraView();
		sf::View& getFullScreenView();
		GraphicAlphabet& getGraphicAlphabet();
		MenuManager& getMenuManager();
		Editor& getEditor();
		
		void zoom(float value);
		float getZoom();
		sf::Vector2i pixelToCoord(sf::Vector2f pos);
		sf::Vector2f coordToPixel(sf::Vector2i pos);
		void restartClock();
		sf::Time getTime();
		void setTime(sf::Time time);
		
		void main();
		
		Game();
};

#endif //COOPSHOOTER_GAME_HPP
