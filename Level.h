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


///Klasa opisuj�ca map� poziomu
class Level
{
public:

	///Domy�lny konstruktor
	explicit Level();
	
	///Wczytuje "map�" gry
	void load();

	///Tworzy nowy rz�d p�l na zadanej wysoko�ci
	std::vector<FT::FieldType> generateNewRow(size_t y);

	///Zwraca typ pola na zadanych wsp�rz�dnych
	FT::FieldType Field(size_t x, size_t y);

	///Zwraca szeroko�� mapy
	size_t getWidth() const { return m_width; };

	///Zwraca wysoko�� mapy
	size_t getHeigth() const { return m_height; };

	///Zwraca CollidBox'a zadanego pola
	Aabb GetFieldAabb(size_t x, size_t y) const;

private:
	size_t m_width;
	size_t m_height;
	std::vector<std::vector<FT::FieldType>> m_data;
};

///Wska�nik na map�
typedef boost::shared_ptr<Level> LevelPtr;
#endif /// !_LEVEL_H
