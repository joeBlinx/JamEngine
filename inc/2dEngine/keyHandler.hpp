//
// Created by stiven on 18-01-20.
//

#ifndef ALLPROJECT_KEYHANDLER_HPP
#define ALLPROJECT_KEYHANDLER_HPP

#include <utility>
#include <map>
#include <string>

namespace JamEngine {
	class KeyHandler {

		using typeMap = std::pair<std::string, std::pair<int, int>>;
		using mapKeys = std::map<std::string, std::pair<int, int>>;
		using iterator = mapKeys::iterator;

		using const_iterator = mapKeys::const_iterator;

		mapKeys keys;

	public:
		KeyHandler() = default;

		void mapKey(std::string &&configFile);

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		std::pair<int, int>  & operator[](std::string const & i );



	};

}


#endif //ALLPROJECT_KEYHANDLER_HPP
