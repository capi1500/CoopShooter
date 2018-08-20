//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_ENUM_HPP
#define COOPSHOOTER_ENUM_HPP

enum class GameState{
		Play,
		InGameMenu,
		Menu
};

enum class ObjectClass{
		Object,
		PhysicObject,
		Entity,
		Player,
		Bullet,
		Item,
		Weapon,
		WorldObject,
		Collectible,
		GraphicString,
		Label,
		Button,
		Menu
};

enum class PhysicObjectShape{
		Box,
		Circle
};

enum class PhysicObjectType{
		Static,
		Dynamic,
		Kinematic
};

enum class TimerPrecision{
		Millisecond,
		Second,
};

#endif //COOPSHOOTER_ENUM_HPP
