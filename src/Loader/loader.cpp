//
// Created by capi1500 on 10/07/18.
//

#include "loader.hpp"
#include <src/Game/game.hpp>
#include <fstream>

void Loader::objectload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "position"){
			file >> objectProperties.position.x >> objectProperties.position.y;
			objectProperties.position.x += startingPos.x;
			objectProperties.position.y += startingPos.y;
			objectProperties.position.x *= blockSize.x;
			objectProperties.position.y *= blockSize.y;
		}
		else if(input == "name"){
			file >> objectProperties.name;
		}
		else if(input == "texture"){
			file >> objectProperties.texture;
		}
		file >> input;
	}
}

void Loader::physicObjectload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "type"){
			file >> input;
			if(input == "dynamic"){
				physicObjectProperties.type = PhysicObjectType::Dynamic;
			}
			else if(input == "kinematic"){
				physicObjectProperties.type = PhysicObjectType::Kinematic;
			}
			else if(input == "static"){
				physicObjectProperties.type = PhysicObjectType::Static;
			}
		}
		else if(input == "shape"){
			file >> input;
			if(input == "box"){
				physicObjectProperties.shape = PhysicObjectShape::Box;
			}
			else if(input == "circle"){
				physicObjectProperties.shape = PhysicObjectShape::Circle;
			}
		}
		else if(input == "density"){
			file >> physicObjectProperties.density;
		}
		else if(input == "friction"){
			file >> physicObjectProperties.friction;
		}
		else if(input == "angle"){
			file >> physicObjectProperties.angle;
		}
		else if(input == "velocity"){
			file >> physicObjectProperties.velocity.x >> physicObjectProperties.velocity.y;
		}
		file >> input;
	}
}

void Loader::entityload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "maxHP"){
			file >> entityProperites.maxHP;
		}
		else if(input == "HP"){
			file >> entityProperites.HP;
		}
		else if(input == "jumpHeight"){
			file >> entityProperites.jumpHeight;
		}
		else if(input == "movementSpeed"){
			file >> entityProperites.movementSpeed;
		}
		else if(input == "isFacingLeft"){
			file >> input;
			if(input == "true"){
				entityProperites.isFacingLeft = true;
			}
			else{
				entityProperites.isFacingLeft = false;
			}
		}
		else if(input == "EQ{"){
			file >> input;
			int ammount;
			while(input != "}"){
				file >> ammount;
				entityProperites.equipment.addItem(new Weapon(*dynamic_cast<Weapon*>(gameRef.getItemManager().getItem(input))), ammount);
				file >> input;
			}
		}
		file >> input;
	}
}

void Loader::playerload(){

}

void Loader::itemload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "ammount"){
			file >> itemProperties.amount;
		}
		else if(input == "worldObject"){
			file >> input;
			if(input == "true"){
				itemProperties.isWorldObject = true;
			}
			else{
				itemProperties.isWorldObject = false;
			}
		}
		file >> input;
	}
}

void Loader::weaponload(){
	std::string input;
	int time;
	file >> input;
	while(input != "}"){
		if(input == "attackDelay"){
			file >> time;
			weaponProperties.attackDelay = sf::milliseconds(time);
		}
		else if(input == "reloadSpeed"){
			file >> time;
			weaponProperties.reloadSpeed = sf::milliseconds(time);
		}
		else if(input == "bulletSpeed"){
			file >> weaponProperties.bulletSpeed;
		}
		else if(input == "dmg"){
			file >> weaponProperties.dmg;
		}
		else if(input == "maxAmmo"){
			file >> weaponProperties.maxAmmo;
		}
		else if(input == "ammo"){
			file >> weaponProperties.ammo;
		}
		else if(input == "reloading"){
			file >> input;
			if(input == "true"){
				weaponProperties.reloading = true;
			}
			else{
				weaponProperties.reloading = false;
			}
		}
		else if(input == "bulletTexture"){
			file >> weaponProperties.bulletTexture;
		}
		file >> input;
	}
}

void Loader::worldObjectload(){

}

void Loader::loadProperties(bool clean){
	if(clean){
		objectProperties = ObjectProperties();
		physicObjectProperties = PhysicObjectProperties();
		itemProperties = ItemProperties();
		weaponProperties = WeaponProperties();
		worldObjectProperties = WorldObjectProperties();
		entityProperites = EntityProperites();
		playerProperties = PlayerProperties();
	}
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "ObjectProperties{"){
			objectload();
		}
		else if(input == "PhysicObjectProperties{"){
			physicObjectload();
		}
		else if(input == "EntityProperties{"){
			entityload();
		}
		else if(input == "ItemProperties{"){
			itemload();
		}
		else if(input == "WeaponProperties{"){
			weaponload();
		}
		file >> input;
	}
}

void Loader::loadTemplate(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "name"){
			file >> templateName;
		}
		else if(input == "PhysicObject{"){
			loadProperties();
			physicObjectProperties.setObjectProperties(objectProperties);
			temp.className = ObjectClass::PhysicObject;
			temp.properties = new PhysicObjectProperties(physicObjectProperties);
		}
		else if(input == "WorldObject{"){
			loadProperties();
			worldObjectProperties.setObjectProperties(objectProperties);
			worldObjectProperties.setPhysicObjectProperties(physicObjectProperties);
			worldObjectProperties.type = PhysicObjectType::Static;
			temp.className = ObjectClass::WorldObject;
			temp.properties = new WorldObjectProperties(worldObjectProperties);
		}
		file >> input;
	}
}

void Loader::loadLevel(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	std::string input;
	while(file >> input){
		if(input == "blockSize"){
			file >> blockSize.x >> blockSize.y;
		}
		else if(input == "startPos"){
			file >> startingPos.x >> startingPos.y;
		}
		else if(input == "PhysicObject{"){
			loadProperties();
			physicObjectProperties.setObjectProperties(objectProperties);
			gameRef.getWorld().addObject(new PhysicObject(gameRef, physicObjectProperties));
		}
		else if(input == "WorldObject{"){
			loadProperties();
			worldObjectProperties.setObjectProperties(objectProperties);
			worldObjectProperties.setPhysicObjectProperties(physicObjectProperties);
			worldObjectProperties.type = PhysicObjectType::Static;
			gameRef.getWorld().addObject(new WorldObject(gameRef, worldObjectProperties));
		}
		else if(input == "Temp"){
			file >> input;
			temp = gameRef.getTemplateManager().getTemplate(input);
			objectProperties = ObjectProperties();
			physicObjectProperties = PhysicObjectProperties();
			itemProperties = ItemProperties();
			weaponProperties = WeaponProperties();
			worldObjectProperties = WorldObjectProperties();
			entityProperites = EntityProperites();
			playerProperties = PlayerProperties();
			switch(temp.className){
				case ObjectClass::PhysicObject:
					objectProperties = *temp.properties;
					physicObjectProperties = *(dynamic_cast<PhysicObjectProperties*>(temp.properties));
					break;
				case ObjectClass::WorldObject:
					objectProperties = *temp.properties;
					physicObjectProperties = *(dynamic_cast<PhysicObjectProperties*>(temp.properties));
					worldObjectProperties = *(dynamic_cast<WorldObjectProperties*>(temp.properties));
					break;
			}
			objectProperties.name = temp.properties->name + std::to_string(objectLoadedID++);
			loadProperties(false);
			switch(temp.className){
				case ObjectClass::PhysicObject:
					physicObjectProperties.setObjectProperties(objectProperties);
					gameRef.getWorld().addObject(new PhysicObject(gameRef, physicObjectProperties));
					break;
				case ObjectClass::WorldObject:
					worldObjectProperties.setObjectProperties(objectProperties);
					worldObjectProperties.setPhysicObjectProperties(physicObjectProperties);
					worldObjectProperties.type = PhysicObjectType::Static;
					gameRef.getWorld().addObject(new WorldObject(gameRef, worldObjectProperties));
					break;
			}
		}
	}
	file.close();
}

void Loader::loadPlayer(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	std::string input;
	file >> input;
	loadProperties();
	playerProperties.setObjectProperties(objectProperties);
	playerProperties.setPhysicObjectProperties(physicObjectProperties);
	playerProperties.setEntityProperties(entityProperites);
	gameRef.getWorld().addObject(new Player(gameRef, playerProperties));
	file.close();
}

void Loader::loadTextures(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	std::string input, name;
	while(file >> input){
		file >> name;
		gameRef.getTextureManager().addTexture("Assets/Textures/" + input, name);
	}
	file.close();
}

void Loader::loadItems(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	std::string input, name;
	while(file >> input){
		if(input == "Item{"){
			loadProperties();
			itemProperties.setObjectProperties(objectProperties);
			gameRef.getItemManager().addItem(new Item(gameRef, itemProperties));
		}
		else if(input == "Weapon{"){
			loadProperties();
			weaponProperties.setObjectProperties(objectProperties);
			weaponProperties.setItemProperties(itemProperties);
			if(weaponProperties.ammo == -1){
				weaponProperties.ammo = weaponProperties.maxAmmo;
			}
			gameRef.getItemManager().addItem(new Weapon(gameRef, weaponProperties));
		}
	}
	file.close();
}

void Loader::loadTemplate(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	std::string input, name;
	while(file >> input){
		if(input == "Template{"){
			loadTemplate();
			gameRef.getTemplateManager().addTemplate(templateName, temp);
		}
	}
	file.close();
}

void Loader::load(std::string path){
	objectLoadedID = 0;
	try{
		loadTextures("Saves/" + path + "/textures.sv");
		loadTemplate("Saves/" + path + "/template.sv");
		loadItems("Saves/" + path + "/items.sv");
		loadLevel("Saves/" + path + "/level.sv");
		loadPlayer("Saves/" + path + "/player1.sv");
		loadPlayer("Saves/" + path + "/player2.sv");
		loadLevel("Saves/" + path + "/levelMid.sv");
		loadLevel("Saves/" + path + "/level2.sv");
	} catch(std::string err){
		printf("%s\n", err.c_str());
	}
}

void Loader::save(std::string path){

}

Loader::Loader(Game& gameRef) : gameRef(gameRef){
}