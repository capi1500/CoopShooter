//
// Created by capi1500 on 26/07/18.
//

#include "timer.hpp"
#include <src/Game/game.hpp>

TimerProperties::TimerProperties(){
	inverseCount = false;
	ends = false;
	endTime = sf::milliseconds(0);
}

TimerProperties::TimerProperties(LabelProperties labelProperties, bool ends, bool inverseCount, TimerPrecision precision, sf::Time endTime) : LabelProperties(labelProperties){
	this->inverseCount = inverseCount;
	this->ends = ends;
	this->endTime = endTime;
	this->precision = precision;
}

TimerProperties& Timer::getTimerProperties(){
	return timerProperties;
}

void Timer::restart(){
	localTime = sf::milliseconds(0);
}

void Timer::setTime(sf::Time time){
	localTime = time;
}

void Timer::draw(){
	if(timerProperties.precision == TimerPrecision::Millisecond){
		setText("0" + std::to_string(static_cast<int>(localTime.asMilliseconds()) + 1));
	}
	else if(timerProperties.precision == TimerPrecision::Second){
		setText("0" + std::to_string(static_cast<int>(localTime.asSeconds()) + 1));
	}
	Label::draw();
}

Timer::Timer(Game& game, TimerProperties timerProperties) : Label(game, timerProperties.getLabelProperties()), timerProperties(timerProperties){
	restart();
}