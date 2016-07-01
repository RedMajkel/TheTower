#ifndef _APP_H
#define _APP_H

#include <SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "Player.h"
#include "Level.h"
#include "SpriteGrid.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "HallOfFame.h"
#include "ScoreSubmit.h"
#include "Menu.h"
#include "Options.h"
#include "Sound.h"


#pragma once

///Klasa opisuj¹ca g³ówn¹ pêtlê gry
class App
{
public:
	///Domyœlny konstruktor, ustawia parametry oraz tworzy niezbêdne obiekty
	explicit App(size_t win_width, size_t win_height, bool fullscreen_mode)
		: m_fullscreen(fullscreen_mode), is_paused(false) {
		Engine::Get().setWindowSize(win_width, win_height);
		m_level_view.storeSprite(FT::PlatformLeftEnd,
			SpritePtr(new Sprite(Engine::Get().getSpriteConfig()->Get("platform_left"))));
		m_level_view.storeSprite(FT::PlatformRightEnd,
			SpritePtr(new Sprite(Engine::Get().getSpriteConfig()->Get("platform_right"))));
		m_level_view.storeSprite(FT::PlatformMidPart,
			SpritePtr(new Sprite(Engine::Get().getSpriteConfig()->Get("platform_mid"))));
		m_level_view.storeSprite(FT::PlatformStone,
			SpritePtr(new Sprite(Engine::Get().getSpriteConfig()->Get("platform_stone"))));
		m_sky.reset(new Sprite(Engine::Get().getSpriteConfig()->Get("sky")));
		m_hall_of_fame.reset(new HallOfFame());
		m_menu.reset(new Menu());
		m_options.reset(new Options());
		m_level.reset(new Level());
		m_player.reset(new Player(9, 1, m_level->getWidth()));
		pos = 0.0;
		base_speed = 0.05;
	}

	///Uruchamia grê
	void Run();

	///Zwraca pozycjê "kamery" w œwiecie gry
	double getPos() { return pos; };

	///Uaktualnia pozycjê "kamery" w œwiecie gry
	void updatePos(double dt);

	///Porównuje pozycjê gracza z pozycj¹ "kamery"
	void comparePos(PlayerPtr player);

private:
	///rysowanie
	void Draw();             

	///aktualizacja
	void Update(double dt);  

	/// przetwarzanie zdarzeñ, które przysz³y
	void ProcessEvents();       

	///Reset stanu gry
	void ResetGame() {
		m_level.reset(new Level());
		m_player->Reset();
		pos = 0.0;
		base_speed = 0.05;
	}

private:
	bool m_fullscreen;
	bool in_game;
	bool is_paused;
	double pos;
	double speed;
	double base_speed;
	double delta_time;

	PlayerPtr m_player;
	LevelPtr m_level;
	SpriteGrid m_level_view;
	HallOfFamePtr m_hall_of_fame;
	ScoreSubmitPtr m_score_submit;
	MenuPtr m_menu;
	OptionsPtr m_options;
	SpritePtr m_sky;
};

#endif

