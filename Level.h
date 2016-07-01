#ifndef _LEVEL_H
#define _LEVEL_H

#pragma once

#include <string>
#include <vector>
#include <boost\shared_ptr.hpp>

#include "Types.h"
#include "Aabb.h"
#include "Renderer.h"
#include "Engine.h"


///Klasa opisuj¹ca mapê poziomu
class Level
{
public:

	///Domyœlny konstruktor
	explicit Level();
	
	///Wczytuje "mapê" gry
	void load();

	///Tworzy nowy rz¹d pól na zadanej wysokoœci
	std::vector<FT::FieldType> generateNewRow(size_t y);

	///Zwraca typ pola na zadanych wspó³rzêdnych
	FT::FieldType Field(size_t x, size_t y);

	///Zwraca szerokoœæ mapy
	size_t getWidth() const { return m_width; };

	///Zwraca wysokoœæ mapy
	size_t getHeigth() const { return m_height; };

	///Zwraca CollidBox'a zadanego pola
	Aabb GetFieldAabb(size_t x, size_t y) const;

private:
	size_t m_width;
	size_t m_height;
	std::vector<std::vector<FT::FieldType>> m_data;
};

///WskaŸnik na mapê
typedef boost::shared_ptr<Level> LevelPtr;
#endif /// !_LEVEL_H
