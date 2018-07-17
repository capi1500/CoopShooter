//
// Created by capi1500 on 17/07/18.
//

#include "templateManager.hpp"

Template::Template(){
	properties = new ObjectProperties();
	className = ObjectClass::Object;
}

void TemplateManager::addTemplate(std::string name, Template properties){
	templates[name] = properties;
}

Template TemplateManager::getTemplate(std::string name){
	if(templates.find(name) != templates.end())
		return templates[name];
	printf("lol\n");
	return Template();
}

TemplateManager::TemplateManager(Game& gameRef) : gameRef(gameRef){
}