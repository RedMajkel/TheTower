#include "SpriteConfig.h"
#include "Types.h"


SpriteConfig::SpriteConfig() {
	Insert("ninja_right", 
		SpriteConfigData(DL::Player, 6, 0.2, 0, 278, 75, 75, true));
	Insert("ninja_left", 
		SpriteConfigData(DL::Player, 6, 0.2, 0, 353, 75, 75, true));
	Insert("ninja_stop", 
		SpriteConfigData(DL::Player, 4, 0.2, 0, 203, 75, 75, true));

	Insert("samurai_right",
		SpriteConfigData(DL::Player, 6, 0.2, 300, 674, 75, 75, true));
	Insert("samurai_left",
		SpriteConfigData(DL::Player, 6, 0.2, 0, 749, 75, 75, true));
	Insert("samurai_stop",
		SpriteConfigData(DL::Player, 4, 0.2, 0, 674, 75, 75, true));

	Insert("platform_left",
		SpriteConfigData(DL::Foreground, 1, 1, 64, 64, 64, 64, true));
	Insert("platform_mid",
		SpriteConfigData(DL::Foreground, 1, 1, 0, 64, 64, 64, true));
	Insert("platform_right",
		SpriteConfigData(DL::Foreground, 1, 1, 128, 64, 64, 64, true));

	Insert("platform_stone",
		SpriteConfigData(DL::Foreground, 1, 1, 0, 128, 64, 64, true));

	Insert("sky",
		SpriteConfigData(DL::Background, 1, 1, 450, 300, 400, 300, true));

}

SpriteConfigData SpriteConfig::Get(const std::string& name) const {
	if (Contains(name))
		return m_data.find(name)->second;
	throw("Config not found: " + name);
}

bool SpriteConfig::Contains(const std::string& name) const {
	return (m_data.find(name) != m_data.end());
}

void SpriteConfig::Insert(const std::string& name, const SpriteConfigData& data) {
	m_data.insert(std::make_pair(name, data));
}