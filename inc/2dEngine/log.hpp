//
// Created by joe on 2/17/19.
//

#ifndef INC_2DENGINE_LOG_HPP
#define INC_2DENGINE_LOG_HPP

#include <iostream>

namespace JamEngine
{
	template<class ...Ts>
	void printFatalError(Ts && ...arg)
	{
		(std::cerr << ... << arg);
		std::cerr << "The program can't continue with this error, abort"<< std::endl;
		exit(1);
	}
}
#endif //INC_2DENGINE_LOG_HPP
