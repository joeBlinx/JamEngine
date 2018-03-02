//
// Created by stiven on 18-03-02.
//

#include "eventManager.hpp"

namespace JamEngine {

	EventManager EventManager::eventManager;
	void EventManager::execute(float delta) {
		auto & events = eventManager.events;
		for (auto eventIt = events.begin(); eventIt != events.end();){
			auto & [duration, time, function] = *eventIt;
			time += delta;
			function(time);
			if(time >= duration){
				eventIt = events.erase(eventIt);
			}else{
				eventIt++;
			}
		}

	}

}
