#include "Menu.h"



Menu::Menu():
	m_selected_option(MO::NewGame)
{
}


void Menu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	TextRenderer t(0.07, 0.07);
	t.drawText("the tower", 0.18, 0.9);
	t.SetLayer(0);
	
	
	switch (m_selected_option) {
	case MO::NewGame:
		Engine::Get().getRenderer()->DrawQuad(0.295, 0.6 - 0.005, 0.705, 0.6 + 0.055, 0, 1, 0, 1);
		break;
	case MO::HallOfFame:
		Engine::Get().getRenderer()->DrawQuad(0.195, 0.5 - 0.005, 0.805, 0.5 + 0.055, 0, 1, 0, 1);
		break;
	case MO::Options:
		Engine::Get().getRenderer()->DrawQuad(0.32, 0.4 - 0.005, 0.68, 0.4 + 0.055, 0, 1, 0, 1);
		break;
	case MO::Quit:
		Engine::Get().getRenderer()->DrawQuad(0.395, 0.3 - 0.005, 0.605, 0.3 + 0.055, 0, 1, 0, 1);
		break;
	}
	t.SetSize(0.05, 0.05);
	t.drawText("new game", 0.3, 0.6);
	t.drawText("hall of fame", 0.2, 0.5);
	t.drawText("options", 0.325, 0.4);
	t.drawText("exit", 0.4, 0.3);

	SDL_GL_SwapBuffers();
}

void Menu::ProcessEvents() {
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
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				Engine::Get().setGameState(GS::Quit);
				return;
			}
			else if (e.key.keysym.sym == SDLK_UP) {
				m_selected_option--;
			}
			else if (e.key.keysym.sym == SDLK_DOWN) {
				m_selected_option++;
			}
			else if (e.key.keysym.sym == SDLK_RETURN) {
				switch (m_selected_option) {
				case MO::NewGame:
					Engine::Get().setGameState(GS::InGame);
					break;
				case MO::HallOfFame:
					Engine::Get().setGameState(GS::HallOfFame);
					break;
				case MO::Options:
					Engine::Get().setGameState(GS::Options);
					break;
				case MO::Quit:
					Engine::Get().setGameState(GS::Quit);
					break;
				}
			}
		}
		else if (e.type == SDL_MOUSEMOTION) {
			double x = e.motion.x / 800.0;
			double y = 1.0 - e.motion.y / 600.0;
			if (x >= 0.3 && x <= 0.7 && y >= 0.6 && y <= 0.65)
				m_selected_option = MO::NewGame;
			else if (x >= 0.2 && x <= 0.8 && y >= 0.5 && y <= 0.55)
				m_selected_option = MO::HallOfFame;
			else if (x >= 0.325 && x <= 0.675 && y >= 0.4 && y <= 0.45)
				m_selected_option = MO::Options;
			else if (x >= 0.4 && x <= 0.6 && y >= 0.3 && y <= 0.35)
				m_selected_option = MO::Quit;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			double y = 1.0 - e.motion.y / 600.0;
			if (y >= 0.3 && y <= 0.65) {
				switch (m_selected_option) {
				case MO::NewGame:
					Engine::Get().setGameState(GS::InGame);
					break;
				case MO::HallOfFame:
					Engine::Get().setGameState(GS::HallOfFame);
					break;
				case MO::Options:
					Engine::Get().setGameState(GS::Options);
					break;
				case MO::Quit:
					Engine::Get().setGameState(GS::Quit);
					break;
				}
			}
		}
	}
}
