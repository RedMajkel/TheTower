#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include <SDL_mixer.h>

///Klasa obs³uguj¹ca dŸwiêk w grze
class Sound {
public:
	///Domyœlny konstruktor
	Sound();

	///Wczytanie dŸwiêków z dysku
	void LoadSounds();

	///Granie muzyki
	void PlayMusic(const std::string& name);

	///Granie efektów dŸwiêkowych
	void PlaySfx(const std::string& name);

private:
	///Wczytaj muzykê
	void LoadMusic(const std::string& name, const std::string& filename);

	///Wczytaj efekty dŸwiekowe
	void LoadSfx(const std::string& name, const std::string& filename);

private:
	std::map<std::string, Mix_Chunk*> m_sfx;
	std::map<std::string, Mix_Music*> m_music;
	///static Sound* instance;
};

///WskaŸnikk na klasê Sound
typedef boost::shared_ptr<Sound> SoundPtr;

#endif /* __SOUND_H__ */