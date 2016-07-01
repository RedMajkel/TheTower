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

///Klasa opisuj¹ca "Hall of Fame", czyli tablicê najlepszych wyników
class HallOfFame
{
private:
	///Struktura opisuj¹ca pojedynczy wynik
	struct Entry {
		std::string name;
		size_t points;
	};
public:
	///Domyœlny konstruktor
	explicit HallOfFame();
	
	///Rysowanie
	void draw();

	///Aktualizacja
	void update(double dt);

	/// przetwarzanie zdarzeñ, które przysz³y
	void proccessEvents();

	///czy wszystko wykonano
	bool isDone() const { return m_is_done; }

	///czy lista wyników jest aktualna
	bool isActual() const { return m_is_actual; }
	
	///ustawia aktualnoœæ tablicy wyników
	void setActual(bool is_actual) { m_is_actual = is_actual; }

private:
	///Wczytuje tablicê wyników z pliku
	void loadFromFile();

private:
	bool m_is_done;
	bool m_is_actual;
	std::vector<Entry> m_entries;
	ParticleSystem* Particle;
};

///WskaŸnik na HallOfFame
typedef boost::shared_ptr<HallOfFame> HallOfFamePtr;

#endif /// !_HALL_OF_FAME_H