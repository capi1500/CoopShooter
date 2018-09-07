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
	templates[name].properties->name = name;
}

Template TemplateManager::getTemplate(std::string name){
	if(templates.find(name) != templates.end())
		return templates[name];
	return Template();
}

std::map<std::string, Template>& TemplateManager::getTemplates(){
	return templates;
}

void TemplateManager::clear(){
	templates.clear();
}

TemplateManager::TemplateManager(Game& gameRef) : gameRef(gameRef){
}