#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include <SDL_mixer.h>

///Klasa obs�uguj�ca d�wi�k w grze
class Sound {
public:
	///Domy�lny konstruktor
	Sound();

	///Wczytanie d�wi�k�w z dysku
	void LoadSounds();

	///Granie muzyki
	void PlayMusic(const std::string& name);

	///Granie efekt�w d�wi�kowych
	void PlaySfx(const std::string& name);

private:
	///Wczytaj muzyk�
	void LoadMusic(const std::string& name, const std::string& filename);

	///Wczytaj efekty d�wiekowe
	void LoadSfx(const std::string& name, const std::string& filename);

private:
	std::map<std::string, Mix_Chunk*> m_sfx;
	std::map<std::string, Mix_Music*> m_music;
	///static Sound* instance;
};

///Wska�nikk na klas� Sound
typedef boost::shared_ptr<Sound> SoundPtr;

#endif /* __SOUND_H__ */