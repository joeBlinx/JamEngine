//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_EVENTMANAGER_HPP
#define INC_2DENGINE_EVENTMANAGER_HPP

#include <2dEngine/event.hpp>
#include <vector>
#include <utility>
namespace JamEngine {
	class EventManager {
		std::vector<Event> events;
		static EventManager eventManager;
	public:
		template <class Function>
		static void addEvent(float duration, Function && function){
			eventManager.events.push_back(Event(duration, std::forward<Function>(function)));
		}

		static void execute(float delta);
	};


}
#endif //INC_2DENGINE_EVENTMANAGER_HPP
