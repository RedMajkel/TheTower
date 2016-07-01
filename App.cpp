#include "App.h"

#include <cassert>
#include <gl\freeglut.h>
#include <string>

#include "Engine.h"
#include "Sprite.h"


void App::Run() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Engine::Get().Resize(Engine::Get().getWindowWidth(), Engine::Get().getWindowHeigth());
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	glClearColor(0.3, 0.66, 0.89, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	const std::string atlas_filename = "data/tex.png";
	Engine& engine = Engine::Get();
	engine.Load();
	engine.getRenderer()->LoadTexture(atlas_filename);
	
	if (Engine::Get().getPlayerSprite() == PT::Ninja) {
		m_player->setSprites(SpritePtr(new Sprite(engine.getSpriteConfig()->Get("ninja_right"))),
			SpritePtr(new Sprite(engine.getSpriteConfig()->Get("ninja_left"))),
			SpritePtr(new Sprite(engine.getSpriteConfig()->Get("ninja_stop"))));
	}
	else if (Engine::Get().getPlayerSprite() == PT::Samurai) {
		m_player->setSprites(SpritePtr(new Sprite(engine.getSpriteConfig()->Get("samurai_right"))),
			SpritePtr(new Sprite(engine.getSpriteConfig()->Get("samurai_left"))),
			SpritePtr(new Sprite(engine.getSpriteConfig()->Get("samurai_stop"))));
	}


	in_game = true;
	size_t last_ticks = SDL_GetTicks();
	Engine::Get().setGameState(GS::Menu);
	
	while (Engine::Get().getState() != GS::Quit) {
		switch (Engine::Get().getState()) {
		case GS::InGame:
			ProcessEvents();
			break;
		case GS::HallOfFame:
			if (!m_hall_of_fame->isActual())
				m_hall_of_fame.reset(new HallOfFame());
			m_hall_of_fame->proccessEvents();
			break;
		case GS::ScoreSubmit:
			m_score_submit->ProcessEvents();
			break;
		case GS::Menu:
			m_menu->ProcessEvents();
			break;
		case GS::Options:
			m_options->processEvents();
		}

		

		size_t ticks = SDL_GetTicks();
		delta_time = (ticks - last_ticks) / (CLOCKS_PER_SEC/10.0);
		if ((delta_time*(CLOCKS_PER_SEC / 10.0)) < ((CLOCKS_PER_SEC / 10.0) / Engine::Get().fps))  
			SDL_Delay(((CLOCKS_PER_SEC / 10.0) / Engine::Get().fps) - (delta_time*(CLOCKS_PER_SEC / 10.0)));
		delta_time = ((CLOCKS_PER_SEC / 10.0) / Engine::Get().fps)/ (CLOCKS_PER_SEC / 10.0);
		last_ticks = ticks;

		
		switch (Engine::Get().getState()) {
		case GS::InGame:
			if (delta_time > 0.0) {
				Update(delta_time);
			}
			Draw();
			break;
		case GS::HallOfFame:
			m_hall_of_fame->draw();
			break;
		case GS::ScoreSubmit:
			m_score_submit->Draw();
			break;
		case GS::Menu:
			m_menu->Draw();
			break;
		case GS::Options:
			m_options->draw();
			break;
		}
	}

	SDL_Quit();
}

void App::comparePos(PlayerPtr player)
{
	if (player->getY() > getPos() + 2.5) {
		speed = 0.15;
	}
	else {
		speed = base_speed;
	}
}

void App::Update(double dt) {
	m_player->update(dt, m_level);
}

void App::Draw() {
	TextRenderer t(0.04, 0.04);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_sky->DrawCurrentFrame(0, 0, 1.0, 1.0);
	

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		comparePos(m_player);
		glTranslatef(0, -(getPos() * Engine::Get().getRenderer()->getTileHeigth() - 0.45), 0);
		glMatrixMode(GL_MODELVIEW);

		m_level_view.setLevel(m_level, getPos());
		m_level_view.draw(getPos());
		

		m_player->draw();
		if (m_player->getY() < getPos() - 10.5) {
			m_score_submit.reset(new ScoreSubmit(m_player->getPoints()));
			ResetGame();
			Engine::Get().setGameState(GS::ScoreSubmit);
			m_hall_of_fame->setActual(false);
		}

	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);	
	
	if (m_player->getPoints() % 50 == 0 || m_player->getPoints() % 50 == 1) {
		if (pos > 10) {
			base_speed = 0.05 + (m_player->getPoints() / 50) * 0.03;
			t.drawText("Speed up!", 0.4, 0.5);
		}

	}

	t.drawText("Points: " + IntToStr(m_player->getPoints()), 0.1, 0.9);
	if (is_paused) {
		t.SetSize(0.07, 0.07);
		t.drawText("GAME PAUSED", 0.15, 0.6);
		t.SetSize(0.04, 0.04);
		t.drawText("Press SPACE to continue", 0.05, 0.5);
		t.drawText("Press ESCAPE to quit", 0.1, 0.4);
	}
	glLoadIdentity();


	SDL_GL_SwapBuffers();
}

void App::updatePos(double dt) {
	pos += 60*dt*speed;
};

void App::ProcessEvents() {
	if (!is_paused)
		updatePos(delta_time);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_VIDEORESIZE) {
			Engine::Get().Resize(event.resize.w, event.resize.h);
		}
		else if (event.type == SDL_QUIT){
			in_game = false;
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			if (is_paused) {
				Engine::Get().setGameState(GS::Menu);
				ResetGame();
			}
			else
				is_paused = true;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
			if (is_paused)
				is_paused = false;
		}
		else if (!is_paused) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
				m_player->jump();
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
				m_player->goLeft();
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
				m_player->goRight();
			}
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
				m_player->stopLeft();
			}
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
				m_player->stopRight();
			}
		}
	}
}


