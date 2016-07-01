#ifndef _SPRITE_GRID_H
#define _SPRITE_GRID_H

#pragma once

#include "Level.h"
#include "Sprite.h"

///Klasa opisuj¹ca siatkê gry
class SpriteGrid
{
public:
	///Domyœlny konstruktor
	explicit SpriteGrid();

	///Ustawia zadany poziom w siatce
	void setLevel(const LevelPtr lvl, double dx);

	///rysowanie
	void draw(double dx) const;

	///Przechowanie sprite'ów poziomu
	void storeSprite(FT::FieldType ft, SpritePtr p);

private:
	///Ustawia Sprite'a w zadanym miejscu
	void setSprite(size_t x, size_t y, SpritePtr sprite) {
		m_grid.at(y).at(x) = sprite;
	}
	
private:
	std::vector<std::vector<SpritePtr>> m_grid;
	std::vector<SpritePtr> m_sprites;
};

#endif /// !_SPRITE_GRID_H