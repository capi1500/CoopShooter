//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_PLAYER_HPP
#define COOPSHOOTER_PLAYER_HPP

#include <src/Entity/entity.hpp>

struct PlayerProperties : public EntityProperites{
	PlayerProperties getPlayerProperties();
	void setEntityProperties(EntityProperites entityProperites);
	
	PlayerProperties();
	PlayerProperties(EntityProperites);
};

class Player : public Entity{
	protected:
		PlayerProperties playerProperties;
		sf::Sprite ammoBar;
	public:
		void pass(sf::Time elapsedTime);
		void drawAmmo();
		
		Player(Game&, PlayerProperties);
};

#endif //COOPSHOOTER_PLAYER_HPP
