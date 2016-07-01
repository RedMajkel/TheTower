#ifndef _SPRITE_H
#define _SPRITE_H

#pragma once

#include "SpriteConfig.h"
#include <boost\shared_ptr.hpp>

///KLasa opisuj�ca Sprite'y
class Sprite
{
public:
	///Domy�lny konstruktor, tworzy obiekt z danych przekzanych w parametrze
	Sprite(const SpriteConfigData& data);

	///Ustawia aktualn� klatk� animacji sprite'a
	void SetCurrentFrame(size_t frame_num);

	///aktualizacja w zale�no�ci od czasu dt
	void Update(double dt);

	///Rysowanie aktualnej klatki
	void DrawCurrentFrame(double x, double y, double width, double heigth);

private:
	SpriteConfigData m_data;
	size_t m_current_frame;
	double m_current_frame_duration;
};

///Wska�nik na Sprite'a
typedef boost::shared_ptr<Sprite> SpritePtr;

#endif

