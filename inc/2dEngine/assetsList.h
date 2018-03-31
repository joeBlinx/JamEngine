//
// Created by stiven on 17-10-10.
//

#ifndef GLENGINE_ASSETSLIST_H
#define GLENGINE_ASSETSLIST_H

#include <string>
#include <map>
#include <vector>
#include <type_traits>
#include <memory>

template<class T>
class AssetsList {
protected:
	int id = 0;
	std::map<std::string, int> keys;
	std::vector<T> ids;
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;

public:

	T const &operator[](int i) const;

	T& operator[](int i);

	decltype(auto) begin();

	decltype(auto) begin() const;

	decltype(auto) end();

	decltype(auto) end() const;

	T const &last() const;

	template<class Function>
	int get(std::string &&path, Function &&function);

	int add(std::string &&key, T &&elem) {
		int thisId = id;
		keys[std::move(key)] = id++;
		ids.emplace_back(std::forward<T>(elem));
		return thisId;
	}

	void clear() {
		ids.clear();
		keys.clear();
	}


};


template<class T>
T const &AssetsList<T>::operator[](int i)const {
	return ids[i];
}
template <class T>
T& AssetsList<T>::operator[](int i) {
	return ids[i];
}

template<class T>
decltype(auto) AssetsList<T>::begin() {
	return ids.begin();
}

template<class T>
decltype(auto) AssetsList<T>::begin() const {
	return ids.cbegin();
}

template<class T>
decltype(auto) AssetsList<T>::end() {
	return ids.begin();
}

template<class T>
decltype(auto) AssetsList<T>::end() const {
	return ids.cbegin();
}

template<class T>
template<class Function>
int AssetsList<T>::get(std::string &&path, Function &&function) {
	auto it = keys.find(path);
	std::string a = path;
	if (it == keys.end()) {
		T ret;
		function(path, ret);
		keys[path] = id++;

		ids.emplace_back(std::move(ret));

	}
	return keys[std::move(path)];

}

template<class T>
T const &AssetsList<T>::last() const {
	return ids.back();
}

#endif //GLENGINE_ASSETSLIST_H
