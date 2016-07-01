#ifndef _SPRITE_CONFIG_H
#define _SPRITE_CONFIG_H



#pragma once
#include <string>
#include <map>
#include <boost\shared_ptr.hpp>

///Struktura opisuj¹ca konfiguracjê sprite'ów
struct SpriteConfigData
{
	///Domyœlnny konstruktor
	explicit SpriteConfigData(size_t level, size_t frame_count, double frame_duration, double left, double bottom, 
		double width, double height, bool loop) :
		level(level), frame_count(frame_count), frame_duration(frame_duration),  left(left), bottom(bottom),
		width(width), height(height), loop(loop)
	{
	}

	size_t level, frame_count;
	double frame_duration, left, right, bottom, width, height;
	bool loop;
};

///Klasa przechowuj¹ca konfiguracjê wszystkich sprite'ów
class SpriteConfig
{
public:
	///Domyœlny konstruktor
	explicit SpriteConfig();

	///Zwraca konfiguracjê sprite'a o zadanej nazwie
	SpriteConfigData Get(const std::string& name) const;

	///Sprawdza czy istnieje konfigurcja o zadanej nazwie
	bool Contains(const std::string& name) const;

private:
	std::map<std::string, SpriteConfigData> m_data;

	///Wi¹¿e konfiguraacjê sprite z zadan¹ nazw¹ i umieszcza j¹ w mapie
	void Insert(const std::string& name, const SpriteConfigData& data);
};

///WskaŸnik na konfiguracjê sprite'ów
typedef boost::shared_ptr<SpriteConfig> SpriteConfigPtr;

#endif 