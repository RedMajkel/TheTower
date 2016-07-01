#include "ScoreSubmit.h"



ScoreSubmit::ScoreSubmit(size_t points) :
	m_is_done(false),
	m_player_nickname("__________"),
	m_next_letter(0),
	m_points(points),
	m_highlighted_char(' ')
{
	Particle = new ParticleSystem(0.5, 0.5);
	Particle->emitParticles();

}

void ScoreSubmit::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	TextRenderer t(0.065, 0.065);
	t.drawText("congraulations", 0.05, 0.9);
	t.SetSize(0.05, 0.05);
	t.drawText("enter your name", 0.1, 0.8);
	t.drawText(m_player_nickname, 0.25, 0.6);

	t.SetSize(0.05, 0.05);
	t.SetLayer(0);
	for (char ch = 'a'; ch <= 'z'; ++ch) {
		std::pair<double, double> pos = LetterPosition(ch);
		if (ch == m_highlighted_char) {
			Engine::Get().getRenderer()->DrawQuad(pos.first - 0.005, pos.second + 0.055,
												  pos.first + 0.055, pos.second - 0.005,
												  0, 1, 0, 1);
		
		}
		t.drawLetter(ch, pos.first, pos.second);

	}
	
	Particle->update();
	Particle->draw();


	SDL_GL_SwapBuffers();
}

std::pair<double, double> ScoreSubmit::LetterPosition(char ch) {
	int index = ch - 'a';
	int col = index % 7;
	int row = index / 7;

	return std::make_pair(0.25 + col * 0.07, 
		                  0.45 - row * 0.07);
}

void ScoreSubmit::ProcessEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_VIDEORESIZE) {
			Engine::Get().Resize(e.resize.w, e.resize.h);
		}
		if (e.type == SDL_QUIT) {
			Engine::Get().setGameState(GS::Quit);
			break;
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_RETURN && m_player_nickname.at(0) != '_') {
				StoreInFile();
				Engine::Get().setGameState(GS::HallOfFame);
				break;
			}
			else if (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym < SDLK_z
				&& m_next_letter < m_player_nickname.size()) {
				char key = e.key.keysym.sym - SDLK_a + 'a';
				m_player_nickname.at(m_next_letter++) = key;
			}
			else if (e.key.keysym.sym == SDLK_BACKSPACE) {
				if (m_player_nickname.at(0) != '_') {
					m_player_nickname.at(--m_next_letter) = '_';
				}
			}
		}
		else if (e.type == SDL_MOUSEMOTION) {
			double x = e.motion.x / 800.0;
			double y = 1.0 - e.motion.y / 600.0;
			m_highlighted_char = ' ';
			for (char ch = 'a'; ch <= 'z'; ++ch) {
				std::pair<double, double> ch_pos = LetterPosition(ch);
				if (x >= ch_pos.first &&  x <= ch_pos.first + 0.07
					&& y <= ch_pos.second + 0.07 && y >= ch_pos.second) {
					m_highlighted_char = ch;
				}
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (m_highlighted_char != ' ' && m_next_letter < m_player_nickname.size()) {
				m_player_nickname.at(m_next_letter++) = m_highlighted_char;
			}
		}
	}
}

void ScoreSubmit::StoreInFile() {
	std::fstream hof("data/hof.txt");
	if (!hof) {
		MessageBoxA(NULL, "Couldn't save hall of fame", "Error", MB_ICONWARNING | MB_OK);
		return;
	}
	 
	std::vector <Entry> entries;
	Entry e;
	while (hof >> e.name >> e.points) {
		entries.push_back(e);
	}

	Entry new_e;
	for (size_t i = 0; i < m_player_nickname.size(); ++i) {
		if (m_player_nickname.at(i) != '_') {
			new_e.name += m_player_nickname.at(i);
		}
	}
	new_e.points = m_points;
	entries.push_back(new_e);

	int j = entries.size() - 1;
	while (j > 0) {
		if (entries.at(j - 1).points < entries.at(j).points) {
			std::swap(entries.at(j - 1), entries.at(j));
		}
		--j;
	}

	hof.close();
	hof.open("data/hof.txt", std::ios::out);
	for (size_t i = 0; i < 10 && i < entries.size(); ++i) {
		hof << entries.at(i).name << " " << entries.at(i).points << "\n";
	}
}


