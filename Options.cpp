#include "Options.h"



Options::Options()
{
	m_resolution = Engine::Get().getResolution();
	m_player_sprite = Engine::Get().getPlayerSprite();
	m_sound_on = Engine::Get().isSoundOn();
	m_selected_option = OO::resolution;
}


void Options::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	TextRenderer t(0.045, 0.045);

	switch (m_selected_option) {
	case OO::resolution:
		Engine::Get().getRenderer()->DrawQuad(0.495, 0.6 - 0.005, 0.905, 0.6 + 0.055, 0, 1, 0, 1);
		break;
	case OO::sound:
		Engine::Get().getRenderer()->DrawQuad(0.495, 0.5 - 0.005, 0.905, 0.5 + 0.055, 0, 1, 0, 1);
		break;
	case OO::character:
		Engine::Get().getRenderer()->DrawQuad(0.495, 0.4 - 0.005, 0.905, 0.4 + 0.055, 0, 1, 0, 1);
		break;
	case OO::OK:
		Engine::Get().getRenderer()->DrawQuad(0.245, 0.2 - 0.005, 0.345, 0.2 + 0.055, 0, 1, 0, 1);
		break;
	case OO::cancel:
		Engine::Get().getRenderer()->DrawQuad(0.495, 0.2 - 0.005, 0.760, 0.2 + 0.055, 0, 1, 0, 1);
		break;
	}
	t.SetLayer(0);

	t.drawText("Resolution: ", 0.05, 0.6);
	switch (m_resolution) {
	case RS::_640x480:
		t.drawText("  640x480", 0.5, 0.6);
		break;
	case RS::_800x600:
		t.drawText("  800x600", 0.5, 0.6);
		break;
	case RS::_1024x768:
		t.drawText(" 1024x768", 0.5, 0.6);
		break;
	case RS::_1280x1024:
		t.drawText("1280x1024", 0.5, 0.6);
		break;
	case RS::_1280x800:
		t.drawText(" 1280x800", 0.5, 0.6);
		break;
	case RS::_1366x768:
		t.drawText(" 1366x768", 0.5, 0.6);
		break;
	case RS::_1680x1050:
		t.drawText("1680x1050", 0.5, 0.6);
		break;
	case RS::_1920x1080:
		t.drawText("1920x1080", 0.5, 0.6);
		break;
	}
	
	
	t.drawText("Sound:", 0.05, 0.5);
	if (m_sound_on)
		t.drawText("       ON", 0.5, 0.5);
	else
		t.drawText("      OFF", 0.5, 0.5);
	
	
	t.drawText("Character:", 0.05, 0.4);
	switch (m_player_sprite)
	{
	case PT::Ninja:
		t.drawText("    NINJA", 0.5, 0.4);
		break;
	case PT::Samurai:
		t.drawText("  SAMURAI", 0.5, 0.4);
		break;
	}


	t.drawText("OK", 0.25, 0.2);
	t.drawText("CANCEL", 0.5, 0.2);

	SDL_GL_SwapBuffers();
}


void Options::processEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_VIDEORESIZE) {
			Engine::Get().Resize(e.resize.w, e.resize.h);
		}
		else if (e.type == SDL_QUIT) {
			Engine::Get().setGameState(GS::Quit);
			break;
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_UP) {
				m_selected_option--;
			}
			else if (e.key.keysym.sym == SDLK_DOWN) {
				m_selected_option++;
			}
			else if (e.key.keysym.sym == SDLK_LEFT) {
				switch (m_selected_option) {
				case OO::resolution:
					m_resolution--;
					break;
				case OO::sound:
					m_sound_on = !m_sound_on;
					break;
				case OO::character:
					m_player_sprite--;
					break;
				case OO::cancel:
					m_selected_option--;
					break;
				}
			}
			else if (e.key.keysym.sym == SDLK_RIGHT) {
				switch (m_selected_option) {
				case OO::resolution:
					m_resolution++;
					break;
				case OO::sound:
					m_sound_on = !m_sound_on;
					break;
				case OO::character:
					m_player_sprite++;
					break;
				case OO::OK:
					m_selected_option++;
					break;
				}
			}
			else if (e.key.keysym.sym == SDLK_RETURN) {
				switch (m_selected_option) {
				case OO::resolution:
					m_resolution++;
					break;
				case OO::sound:
					m_sound_on = !m_sound_on;
					break;
				case OO::character:
					m_player_sprite++;
					break;
				case OO::OK:
					saveConfigToFile();
					Engine::Get().loadConfigFromFile();
					Engine::Get().setGameState(GS::Menu);
					break;
				case OO::cancel:
					Engine::Get().setGameState(GS::Menu);
					break;
				}
			}
			else if (e.key.keysym.sym == SDLK_ESCAPE) {
				Engine::Get().setGameState(GS::Menu);
			}
		}
	}
}

void Options::saveConfigToFile() {
	std::fstream config("Data/config.txt");
	switch (m_resolution) {
	case RS::_640x480:
		config << "640x480";
		break;
	case RS::_800x600:
		config << "800x600";
		break;
	case RS::_1024x768:
		config << "1024x768";
		break;
	case RS::_1280x1024:
		config << "1280x1024";
		break;
	case RS::_1280x800:
		config << "1280x800";
		break;
	case RS::_1366x768:
		config << "1366x768";
		break;
	case RS::_1680x1050:
		config << "1680x1050";
		break;
	case RS::_1920x1080:
		config << "1920x1080";
		break;
	}

	switch (m_player_sprite) {
	case PT::Ninja:
		config << " " << "ninja";
		break;
	case PT::Samurai:
		config << " " << "samurai";
		break;
	}

	if (m_sound_on)
		config << " " << 1 << " ";
	else
		config << " " << 0 << " ";

	config << Engine::Get().fps;

	config.close();
}