#ifndef _HALL_OF_FAME_H
#define _HALL_OF_FAME_H

#pragma once

#include <string>
#include <vector>
#include <GL\glew.h>
#include <SDL.h>
#include <Windows.h>
#include <fstream>
#include <boost\shared_ptr.hpp>

#include "TextRenderer.h"
#include "Engine.h"
#include "ParticleSystem.h"

///Klasa opisuj�ca "Hall of Fame", czyli tablic� najlepszych wynik�w
class HallOfFame
{
private:
	///Struktura opisuj�ca pojedynczy wynik
	struct Entry {
		std::string name;
		size_t points;
	};
public:
	///Domy�lny konstruktor
	explicit HallOfFame();
	
	///Rysowanie
	void draw();

	///Aktualizacja
	void update(double dt);

	/// przetwarzanie zdarze�, kt�re przysz�y
	void proccessEvents();

	///czy wszystko wykonano
	bool isDone() const { return m_is_done; }

	///czy lista wynik�w jest aktualna
	bool isActual() const { return m_is_actual; }
	
	///ustawia aktualno�� tablicy wynik�w
	void setActual(bool is_actual) { m_is_actual = is_actual; }

private:
	///Wczytuje tablic� wynik�w z pliku
	void loadFromFile();

private:
	bool m_is_done;
	bool m_is_actual;
	std::vector<Entry> m_entries;
	ParticleSystem* Particle;
};

///Wska�nik na HallOfFame
typedef boost::shared_ptr<HallOfFame> HallOfFamePtr;

#endif /// !_HALL_OF_FAME_H