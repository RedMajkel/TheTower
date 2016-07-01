#pragma once

#include <SDL.h>
#include <boost\shared_ptr.hpp>

#include "TextRenderer.h"
#include "Types.h"
#include "Engine.h"

///Klasa opisuj�ca menu gry
class Menu
{
public:
	///Domy�lny konstruktor
	Menu();

	/// przetwarzanie zdarze�, kt�re przysz�y
	void ProcessEvents();

	/// rysowanie
	void Draw();

private:
	MO::MenuOptions m_selected_option;
};

///Wska�nik na obiekt menu gry
typedef boost::shared_ptr<Menu> MenuPtr;

