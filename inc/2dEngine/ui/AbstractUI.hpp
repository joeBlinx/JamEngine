//
// Created by joe on 3/6/19.
//

#ifndef INC_2DENGINE_ABSTRACTUI_HPP
#define INC_2DENGINE_ABSTRACTUI_HPP
#include <tuple>
#include <utils/tupleUtils.hpp>

namespace JamEngine
{
	struct AbstractUI
	{
		virtual void update() = 0;
		virtual void display()   = 0;
	};

	template<class ...Ts>
	struct UI
	{
		void update() ;
		void display() ;
		template<class ... Us>
		UI(int const &width, int const &height, Us && ...component)
		: window_width(width), window_height(height), components(std::forward<Us>(component)...){}
	private:

		int const &window_width;
		int const &window_height;
		std::tuple<Ts...> components;
	};

	template<class... Ts>
	void UI<Ts...>::update() {
		utils::for_each_tuple(components, [](auto &element)
		{
			element.update();
		});
	}

	template<class... Ts>
	void UI<Ts...>::display() {

		utils::for_each_tuple(components, [this](auto &element)
		{
			element.display(window_width, window_height);
		});
	}

}
#endif //INC_2DENGINE_ABSTRACTUI_HPP
