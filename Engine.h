#ifndef _ENGINE_H
#define _ENGINE_H

#pragma once

#define NOMINMAX

#include <Windows.h>

#include "Sound.h"
#include "Renderer.h"
#include "SpriteConfig.h"
#include "Types.h"


///Klasa typu Singleton, opisuj�ca silnik gry zawieraj�cy w sobie m. in. renderer
class Engine
{
public:
	///Statyczna metoda, zwracaj�ca instancj� klasy
	static Engine& Get() {
		static Engine engine;
		return engine;
	}

	///Wczytanie niezb�dnych zasob�w z dysku
	void Load() {
		m_spriteConfig.reset(new SpriteConfig());
		m_renderer.reset(new Renderer());
		m_sound.reset(new Sound());
		loadConfigFromFile();
	}

	///Zwraca konfiguracj� Sprite'�w
	SpriteConfigPtr getSpriteConfig() {
		return m_spriteConfig;
	}

	///Zwraca Renderer
	RendererPtr getRenderer() {
		return m_renderer;
	}

	///Zwraca aktualny stan gry
	GS::GameState getState() {
		return m_game_state;
	}

	///Ustawia stan gry
	void setGameState(GS::GameState state) {
		m_game_state = state;
	}

	///Zwraca powierzchni� ekranu
	SDL_Surface* getScreen() {
		return m_screen;
	}

	///Ustawia rozmiar okna
	void setWindowSize(size_t w, size_t h) {
		m_window_width = w;
		m_window_height = h;
	}

	///Zwraca szeroko�� okna
	size_t getWindowWidth(){
		return m_window_width;
	}

	///Zwraca wysoko�� okna
	size_t getWindowHeigth() {
		return m_window_height;
	}

	///Zmienia rozmiar okna
	void Resize(size_t width, size_t height) {
		m_screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_RESIZABLE | SDL_HWSURFACE);
		if (m_screen == NULL) {
			MessageBox(NULL, L"Can't setup window", L"Error", MB_ICONWARNING | MB_OK);
			exit(1);
		}
		m_window_width = width;
		m_window_height = height;

		getRenderer()->setProjection(width, height);
	}

	///Zwraca wska�nik na obiekt obs�uguj�cy d�wi�k gry
	SoundPtr getSound() {
		return m_sound;
	}

	///Ustawia rozdzielczo�� gry
	void setResolution(RS::Resolution res) {
		m_resolution = res;
		
		switch (m_resolution) {
		case RS::_640x480:
			Resize(640, 480);
			return;
		case RS::_800x600:
			Resize(800, 600);
			return;
		case RS::_1024x768:
			Resize(1024, 768);
			return;
		case RS::_1280x1024:
			Resize(1280, 1024);
			return;
		case RS::_1280x800:
			Resize(1280, 800);
			return;
		case RS::_1366x768:
			Resize(1366, 768);
			return;
		case RS::_1680x1050:
			Resize(1680, 1050);
			return;
		case RS::_1920x1080:
			Resize(1920, 1080);
			return;
		}
	}

	///Zwraca rozdzielczo�� gry
	RS::Resolution getResolution() {
		return m_resolution;
	}

	///Zwraca informacj� o Spricie gracza
	PT::PlayerTexture getPlayerSprite() {
		return m_player_sprite;
	}
	
	///Czy d�wi�k jest w��czony
	bool isSoundOn() {
		return m_sound_on;
	}

	///Wczytuje konfiguracj� z pliku
	void loadConfigFromFile() {
		std::string resolution, character;
		size_t sound;
		std::fstream config("Data/config.txt");

		config >> resolution >> character >> sound >> fps;

		if (resolution == "640x480")
			setResolution(RS::_640x480);
		else if (resolution == "800x600")
			setResolution(RS::_800x600);
		else if (resolution == "1024x768")
			setResolution(RS::_1024x768);
		else if (resolution == "1280x1024")
			setResolution(RS::_1280x1024);
		else if (resolution == "1280x800")
			setResolution(RS::_1280x800);
		else if (resolution == "1366x768")
			setResolution(RS::_1366x768);
		else if (resolution == "1680x1050")
			setResolution(RS::_1680x1050);
		else if (resolution == "1920x1080")
			setResolution(RS::_1920x1080);

		if (character == "ninja") {
			m_player_sprite = PT::Ninja;
		}
		else if (character == "samurai") {
			m_player_sprite = PT::Samurai;
		}

		if (sound == 1) {
			m_sound->LoadSounds();
			m_sound->PlayMusic("game");
			m_sound_on = true;
		}
		else {
			m_sound_on = false;
			Mix_HaltMusic();
		}
		config.close();
	}

private:
	SpriteConfigPtr m_spriteConfig;
	RendererPtr m_renderer;
	GS::GameState m_game_state;
	SDL_Surface* m_screen;

	size_t m_window_width;
	size_t m_window_height;
	SoundPtr m_sound;

	RS::Resolution m_resolution;
	PT::PlayerTexture m_player_sprite;
	bool m_sound_on;
public:
	///Ilo�� klatek na sekund�
	double fps;
};


#endif