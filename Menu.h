#pragma once

#include <SDL.h>
#include <boost\shared_ptr.hpp>

#include "TextRenderer.h"
#include "Types.h"
#include "Engine.h"

///Klasa opisuj¹ca menu gry
class Menu
{
public:
	///Domyœlny konstruktor
	Menu();

	/// przetwarzanie zdarzeñ, które przysz³y
	void ProcessEvents();

	/// rysowanie
	void Draw();

private:
	MO::MenuOptions m_selected_option;
};

///WskaŸnik na obiekt menu gry
typedef boost::shared_ptr<Menu> MenuPtr;

