#ifndef _AABB_H
#define _AABB_H



#pragma once

#include <cassert>
#include <boost\shared_ptr.hpp>

///Klasa opisuj�ca CollidBoxy
class Aabb
{
public:
	///domy�lny konstruktor, tworzy CollidBox'a z podanych parametr�w
	Aabb(double min_x, double min_y, double max_x, double max_y) :
		m_min_x(min_x), m_min_y(min_y), m_max_x(max_x), m_max_y(max_y) {
	}

	///Sprawdzenie czy zachodzi kolizja z CollidBox'em podanym w parametrze
	bool Collides(const Aabb& box) const;

	///Sprawdzenie czy znajduj� si� nad CollidBox'em w parametrze
	bool IsOver(const Aabb& box) const;
	
	///Sprawdzenie czy znajduj� si� pod CollidBox'em w parametrze
	bool IsUnder(const Aabb& box) const;

	///Sprawdzenie czy znajduj� si� na lewo od CollidBox'a w parametrze
	bool IsOnLeftOf(const Aabb& box) const;
	
	///Sprawdzenie czy znajduj� si� na prawo od CollidBox'a w parametrze
	bool IsOnRightOf(const Aabb& box) const;

	///Zwraca pozycj� x lewego dolnego naro�nika
	double GetMinX() const { return m_min_x; }

	///Zwraca pozycj� y lewego dolnego naro�nika
	double GetMinY() const { return m_min_y; }

	///Zwraca pozycj� x prawego g�rnego naro�nika
	double GetMaxX() const { return m_max_x; }

	///Zwraca pozycj� y prawego g�rnego naro�nika
	double GetMaxY() const { return m_max_y; }

	///Przesuwa CollidBox'a o wskazany offset
	Aabb Move(double min_x_offset, double min_y_offset, double max_x_offset, double max_y_offset) {
		return Aabb(m_min_x + min_x_offset, m_min_y + min_y_offset, m_max_x + max_x_offset, m_max_y + max_y_offset);
	}

private:
	/// pozycja lewego dolnego naro�nika
	double m_min_x;
	double m_min_y;

	/// pozycja prawego g�rnego naro�nika
	double m_max_x;
	double m_max_y;
};

typedef boost::shared_ptr<Aabb> AabbPtr;


#endif /// !_AABB_H