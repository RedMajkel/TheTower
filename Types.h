#pragma once

#ifndef __TYPES_H__
#define __TYPES_H__

namespace DL {
	///Warstwa do rysowania (im mniejsza wartoœæ, tym bli¿ej ekranu)
	enum DisplayLayer {
		Background = 4,
		Foreground = 3,
		Player = 2,
		Text = 1
	};
}

namespace PS {
	///stan gracza
	enum PlayerState {
		Stand,
		GoLeft,
		GoRight
	};
}

namespace FT {
	///Rodzaj pola
	enum FieldType {
		None = 0,
		PlatformLeftEnd = 1,
		PlatformMidPart = 2,
		PlatformRightEnd = 3,
		PlatformStone = 4
	};
}

namespace GS {
	///Stan gry
	enum GameState {
		Menu,
		HallOfFame,
		ScoreSubmit,
		Options,
		InGame,
		Quit
	};
}

namespace MO {
	///Opcje menu
	enum MenuOptions {
		NewGame = 0, 
		HallOfFame = 1,
		Options = 2,
		Quit = 3
	};

	///inkrementacja opcji gry
	inline MenuOptions& operator++(MenuOptions& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<MenuOptions>((i + 1) % 4);
		return option;
	}

	///dekrementacja opcji gry
	inline MenuOptions& operator--(MenuOptions& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<MenuOptions>((i - 1) % 4);
		if (static_cast<int>(option) < 0)
			option = static_cast<MenuOptions>(3);
		return option;
	}
}

namespace RS {
	///Rozdzielczoœci
	enum Resolution {
		_640x480 = 0,
		_800x600 = 1,
		_1024x768 = 2,
		_1280x800 = 3,
		_1280x1024 = 4,
		_1366x768 = 5,
		_1680x1050 = 6,
		_1920x1080 = 7
	};
	///inkrementacja
	inline Resolution& operator++(Resolution& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<Resolution>((i + 1) % 8);
		return option;
	}
	///dekrementacja
	inline Resolution& operator--(Resolution& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<Resolution>((i - 1) % 8);
		if (static_cast<int>(option) < 0)
			option = static_cast<Resolution>(7);
		return option;
	}
}

namespace PT {
	enum PlayerTexture {
		Ninja = 0,
		Samurai = 1
	};
	inline PlayerTexture& operator++(PlayerTexture& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<PlayerTexture>((i + 1) % 2);
		return option;
	}
	inline PlayerTexture& operator--(PlayerTexture& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<PlayerTexture>((i - 1) % 2);
		if (static_cast<int>(option) < 0)
			option = static_cast<PlayerTexture>(1);
		return option;
	}
}

namespace OO {
	///opcje opcji
	enum OptionsOptions {
		resolution = 0,
		sound = 1,
		character = 2,
		OK = 3,
		cancel = 4
	};

	///inkrementacja
	inline OptionsOptions& operator++(OptionsOptions& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<OptionsOptions>((i + 1) % 5);
		return option;
	}

	///dekrementacja
	inline OptionsOptions& operator--(OptionsOptions& option, int) {
		const int i = static_cast<int>(option);
		option = static_cast<OptionsOptions>((i - 1) % 5);
		if (static_cast<int>(option) < 0)
			option = static_cast<OptionsOptions>(4);
		return option;
	}
}

#endif