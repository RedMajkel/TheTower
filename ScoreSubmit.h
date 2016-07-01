#pragma once

#include <utility>
#include <string>
#include <GL\glew.h>
#include <SDL.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <boost\shared_ptr.hpp>

#include "TextRenderer.h"
#include "Engine.h"
#include "ParticleSystem.h"


///Klasa obs�uguj�ca ekran do wpisywania swojej nazwy gracza
class ScoreSubmit
{
private:
	///Struktura opisuj�ca pojedynczy wynik gracza
	struct Entry {
		std::string name;
		size_t points;
	};
public:
	///Domy�lny konstruktor, jako parametr zostaj� przekazane punkty gracza
	explicit ScoreSubmit(size_t points);

	/// przetwarzanie zdarze�, kt�re przysz�y
	void ProcessEvents();

	///rysowanie
	void Draw();

	///czy ju� uko�czono
	bool isDone() const { return m_is_done; }
	

private:
	///Oblicza pozycj� tekstury zadanej litery w atlasie tekstur
	std::pair<double, double> LetterPosition(char ch);

	///Zapisuje wyniki do pliku
	void StoreInFile();

private:
	bool m_is_done;
	std::string m_player_nickname;
	size_t m_next_letter;
	size_t m_points;
	char m_highlighted_char;
	ParticleSystem* Particle;
};

///Wska�nik na obiekt klasy SubmitScore
typedef boost::shared_ptr<ScoreSubmit> ScoreSubmitPtr;

