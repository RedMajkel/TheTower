#pragma once

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Types.h"
#include "Sprite.h"
#include "Aabb.h"
#include "Level.h"
#include "Sound.h"


#include <boost\shared_ptr.hpp>


///Klasa opisuj¹ca postaæ gracza
class Player
{
public:
	///Domyœlny konstruktor, ustawia gracza na zadanej pozycji
	explicit Player(double x, double y, size_t level_width);

	///Ustawia sprite'y gracza
	void setSprites(SpritePtr right, SpritePtr left, SpritePtr stop);

	///aktualizacja stanu gracza
	void update(double dt, LevelPtr level);

	///rysowanie
	void draw() const;

	///Zwraca pozycjê x  gracza
	double getX() const { return m_x; };

	///Zwraca pozycjê y gracza
	double getY() const { return m_y; };

	///Zwraca prêdkoœæ gracza w pionie
	double getDefaultYVelocity() const {
		return defaultYVelocity;
	}

	///Zwraca przyspieszenie gracza w pionie
	double getDefaultYAcceleration() const {
		return defaultYAcceleration;
	}

	///Bieg w lewo
	void goLeft()				{ m_vx -= 4.0; m_state = PS::GoLeft; };
	
	///Bieg w prawo
	void goRight()				{ m_vx += 4.0; m_state = PS::GoRight; };
	
	///Zatrzymanie biegu w lewo
	void stopLeft()				{ m_vx += 4.0; m_state = PS::Stand; };
	
	///Zatrzymanie biegu w prawo
	void stopRight()			{ m_vx -= 4.0; m_state = PS::Stand; };
	
	///Zabroñ biegu w lewo
	void forbidGoingLeft()		{ m_can_go_left = false; };
	
	///Zabroñ biegu w prawo
	void forbidGoingRight()		{ m_can_go_right = false; };
	
	///Spadanie
	void fall()                 { m_vy = 0.0; m_is_on_ground = false; is_falling = true; m_jump_allowed = false; };
	
	///Skok
	void jump(double y_velocity = defaultYVelocity);

	///Zezwól na skok
	void allowToJump()			{ m_jump_allowed = true; };

	///Zabroñ skoku
	void forbidToJump()			{ m_jump_allowed = false; };

	///Ustaw domyœlne poruszanie siê
	void setDefaultMoving()		{ m_is_on_ground = false; m_can_go_right = m_can_go_left = true; };

	///Gracz na ziemi
	void playerOnGround()		{ m_vy = 0.0; m_is_on_ground = m_jump_allowed = true; is_falling = false; };

	///Nastêpna pozycja x gracza, po zadanaym czasie dt
	double getNextXPosition(double dt) const {
		return m_x + m_vx *dt *m_running_factor;
	}

	///Nastêpna pozycja y gracza, po zadanym czasie dt
	double getNextYPosition(double dt) const {
		return m_y + (m_vy + m_ay * dt) * dt;
	}

	///Czy jest pode mn¹ "klocek"
	bool IsAnyFieldBelowMe(double dt, LevelPtr level);

	///Zwraca wspó³rzêdne gracza w siatce mapy
	void GetCurrentTile(size_t *x, size_t *y) const {
		const size_t v_tiles_count =
			Engine::Get().getRenderer()->
			getVerticalTilesOnScreenCount();
		*y = v_tiles_count
			+ (GetAabb().GetMinY() + GetAabb().GetMaxY()) / 2;
		*x = getX() + GetBasicAabb().GetMaxX() / 2;
	}

	///Zwraca podstawowego CollidBox'a  gracza
	virtual Aabb GetBasicAabb() const { return Aabb(0, 0, 1, 1); }

	///Zwraca CollidBox'a gracza
	Aabb GetAabb() const {
		return GetBasicAabb().Move(m_x, m_y, m_x, m_y);
	}

	///Zwraca nastêpnego poziomego CollidBox'a gracza, po zadanym czasie dt
	Aabb GetNextHorizontalAabb(double dt) const {
		return GetBasicAabb().Move(getNextXPosition(dt), m_y,
			getNextXPosition(dt), m_y);
	}

	///Zwraca nastêpnego pionowego CollidBox'a gracza, po zadanym czasie dt
	Aabb GetNextVerticalAabb(double dt) const {
		return GetBasicAabb().Move(m_x, getNextYPosition(dt),
			m_x, getNextYPosition(dt));
	}

	///Zwraca nastêpnego CollidBox'a gracza, po zadanym czasie dt
	Aabb GetNextAabb(double dt) const {
		return GetBasicAabb().Move(
			getNextXPosition(dt), getNextYPosition(dt),
			getNextXPosition(dt), getNextYPosition(dt));
	}

	///Sprawdza kolizje z plansz¹
	void CheckCollisionsWithLevel(double dt, LevelPtr level);

	///Zwraca punkty gracza
	size_t getPoints() {
		return m_points / 3;
	}

	///Resetuje gracza
	void Reset();

private:
	enum {defaultYVelocity = 30, defaultYAcceleration = -60};
	PS::PlayerState m_state;
	SpritePtr m_left;
	SpritePtr m_right;
	SpritePtr m_stop;
	double m_x;
	double m_y;
	double m_vx;
	double m_vy;
	double m_ay;
	double m_running_factor;
	bool m_jump_allowed;
	size_t m_level_width;
	bool m_is_on_ground;
	bool m_can_go_right;
	bool m_can_go_left;
	bool is_falling;
	size_t m_points;

};

///WskaŸnik na obiekt gracza
typedef boost::shared_ptr<Player> PlayerPtr;

#endif /// !_PLAYER_H