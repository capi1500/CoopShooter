//
// Created by capi1500 on 17/07/18.
//

#ifndef COOPSHOOTER_TEMPLATEMANAGER_HPP
#define COOPSHOOTER_TEMPLATEMANAGER_HPP

#include <src/Object/object.hpp>

struct Template{
	ObjectProperties* properties;
	ObjectClass className;
	
	Template();
};

class TemplateManager{
	private:
		Game& gameRef;
		std::map<std::string, Template> templates;
	public:
		void addTemplate(std::string name, Template properties);
		Template getTemplate(std::string name);
		
		TemplateManager(Game& gameRef);
};

#endif //COOPSHOOTER_TEMPLATEMANAGER_HPP
