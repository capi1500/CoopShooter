//
// Created by capi1500 on 26/07/18.
//

#ifndef MAIN_TIMER_HPP
#define MAIN_TIMER_HPP

#include <src/Label/label.hpp>

struct TimerProperties : public LabelProperties{
	sf::Time endTime;
	bool ends;
	bool inverseCount;
	TimerPrecision precision;
	
	TimerProperties();
	TimerProperties(LabelProperties labelProperties, bool ends, bool inverseCount, TimerPrecision precision = TimerPrecision::Second, sf::Time endTime = sf::milliseconds(0));
};

class Timer : public Label{
	protected:
		TimerProperties timerProperties;
	public:
		TimerProperties& getTimerProperties();
		
		void draw();
		void restart();
		void setTime(sf::Time time);
		
		Timer(Game& game, TimerProperties timerProperties);
};

#endif //MAIN_TIMER_HPP
