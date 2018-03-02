//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_EVENT_HPP
#define INC_2DENGINE_EVENT_HPP

#include <functional>

namespace JamEngine {
	struct Event {

		float duration;
		float currentTime;
		std::function<void(float)> function;

		template <class Function>
		Event(float duration, Function && function):duration(duration),
													function(std::forward<Function>(function))
		{

		}
	};
}


#endif //INC_2DENGINE_EVENT_HPP
