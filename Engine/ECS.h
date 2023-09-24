#pragma once

#include <array>
#include <bitset>
#include <iostream>

class Entity;
class Component;
class Level;

using ComponentTypeID = std::size_t;
//using Group = std::size_t;

inline ComponentTypeID GetUniqueComponentID()
{
	static ComponentTypeID lastID = 0u;
	return lastID++;
}

template <typename T>
inline ComponentTypeID GetComponentTypeID() noexcept {
	static_assert(std::is_base_of<Component, T>::value, "Type not base on component!"); //check if child is based on component
	static const ComponentTypeID typeID = GetUniqueComponentID();
	return typeID;
}

constexpr std::size_t MAX_ENTITIES = 5000;
constexpr std::size_t MAX_COMPONENTS = 32;
//constexpr std::size_t maxGroups = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
//using GroupBitset = std::bitset<maxGroups>;
using ComponentList = std::array<Component*, MAX_COMPONENTS>;
