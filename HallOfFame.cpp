#include "HallOfFame.h"



HallOfFame::HallOfFame() :
	m_is_done(false),
	m_is_actual(true)
{
	loadFromFile();
	Particle = new ParticleSystem(0.5, 0.5);
}

void HallOfFame::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	TextRenderer t(0.08, 0.08);
	t.drawText("Hall of Fame", 0.01, 0.9);

	t.SetSize(0.035, 0.035);
	double y = 0.7;
	double x = 0.15;
	for (size_t i = 0; i < m_entries.size(); ++i) {
		t.drawText(m_entries.at(i).name, x, y);
		t.drawNumber(m_entries.at(i).points, x + 0.4, y, 8);
		y -= 0.07;
	}

	
	Particle->update();
	Particle->draw();

	SDL_GL_SwapBuffers();
}

void HallOfFame::update(double dt) {
	return;
}

void HallOfFame::proccessEvents() {
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
			Engine::Get().setGameState(GS::Menu);
			break;
		}
	}
}

void HallOfFame::loadFromFile() {
	std::ifstream in("data/hof.txt");
	if (!in) {
		MessageBoxA(NULL, "Couldn't load hall of fame", "Error", MB_ICONWARNING | MB_OK);
		exit(1);
	}

	Entry entry;
	while (in >> entry.name >> entry.points) {
		m_entries.push_back(entry);
	}
}

