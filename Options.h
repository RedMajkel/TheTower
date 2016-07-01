#pragma once

#include <SDL.h>
#include <boost/shared_ptr.hpp>

#include "Engine.h"
#include "TextRenderer.h"
#include "Types.h"


///Klasa opisuj¹ca menu z opcjami gry
class Options
{
public:
	///Domyœlny konstruktor
	Options();

	///Rysowanie
	void draw();

	/// przetwarzanie zdarzeñ, które przysz³y
	void processEvents();


private:
	///Zapisuje ustawienia do pliku
	void saveConfigToFile();

private:
	RS::Resolution m_resolution;
	PT::PlayerTexture m_player_sprite;
	bool m_sound_on;
	OO::OptionsOptions m_selected_option;
};

///WskaŸnik na obiekt opcji gry
typedef boost::shared_ptr<Options> OptionsPtr;

