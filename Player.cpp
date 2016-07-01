#include "Player.h"
#include "Engine.h"



Player::Player(double x, double y, size_t level_width) :
	m_state(PS::Stand),
	m_x(x),
	m_y(y),
	m_vx(0.0),
	m_vy(0.0),
	m_ay(defaultYAcceleration),
	m_running_factor(2.0),
	m_jump_allowed(true),
	m_level_width(level_width),
	m_is_on_ground(true),
	m_can_go_left(true),
	m_can_go_right(true),
	m_points(0)
{
	setDefaultMoving();
}

void Player::Reset() {
	m_state = PS::Stand;
	m_x = 9;
	m_y = 1;
	m_vx = 0.0;
	m_vy = 0.0;
	m_ay = defaultYAcceleration;
	m_running_factor = 2.0;
	m_jump_allowed = true;
	m_is_on_ground = true;
	m_can_go_left = true;
	m_can_go_right = true;
	m_points = 0;
	setDefaultMoving();
}

void Player::setSprites(SpritePtr right, SpritePtr left, SpritePtr stop) {
	m_left = left;
	m_right = right;
	m_stop = stop;
}

void Player::jump(double y_velocity) {
	if (m_jump_allowed) {
		m_jump_allowed = false;
		m_is_on_ground = false;
		m_vy = y_velocity;
		m_ay = defaultYAcceleration;
		if (Engine::Get().isSoundOn())
			Engine::Get().getSound()->PlaySfx("jump");
	}
}

void Player::draw() const {
	const double tileWidth = Engine::Get().getRenderer()->getTileWidth();
	const double tileHeigth = Engine::Get().getRenderer()->getTileHeigth();

	const double pos_x = m_x * tileWidth;
	const double pos_y = m_y * tileHeigth;

	switch (m_state) {
	case PS::Stand:
		m_stop->DrawCurrentFrame(pos_x, pos_y, tileWidth, tileHeigth);
		break;
	case PS::GoLeft:
		m_left->DrawCurrentFrame(pos_x, pos_y, tileWidth, tileHeigth);
		break;
	case PS::GoRight:
		m_right->DrawCurrentFrame(pos_x, pos_y, tileWidth, tileHeigth);
		break;
	}
}

void Player::update(double dt, LevelPtr level) {
	CheckCollisionsWithLevel(dt, level);

	if (!m_is_on_ground) {
		m_y = getNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	if (m_y < 1) {
		m_y = 1;
		playerOnGround();
	}

	m_x = getNextXPosition(dt);

	if (m_x < 0) {
		m_x = 0;
	}
	else if (m_x > m_level_width - 1) {
		m_x = m_level_width - 1;
	}

	if (fabs(m_vx) < 0.01) {
		m_state = PS::Stand;
		m_vx = 0.0;
	}
	else if (m_vx > 0.0) {
		m_state = PS::GoRight;
	}
	else {
		m_state = PS::GoLeft;
	}

	switch (m_state) {
	case PS::Stand:
		m_stop->Update(dt);
		break;
	case PS::GoLeft:
		m_left->Update(dt);
		break;
	case PS::GoRight:
		m_right->Update(dt);
		break;
	}


}

bool Player::IsAnyFieldBelowMe(double dt, LevelPtr level) {
	size_t current_x_tile, current_y_tile;
	GetCurrentTile(&current_x_tile, &current_y_tile);
	current_y_tile -= 20;
	current_x_tile = 20 - current_x_tile;
		if (level->Field(current_x_tile - 1, current_y_tile - 1) != FT::None) {
			if (abs(m_y - current_y_tile) < 0.2) {
				m_y -= 0.1;
				if (m_y < current_y_tile)
					m_y = current_y_tile;
				if (current_y_tile > m_points)
					m_points = current_y_tile;
				return true;
			}
		}
		else if (level->Field(current_x_tile, current_y_tile) != FT::None) {
			Aabb field_aabb = level->GetFieldAabb(current_x_tile, current_y_tile);
			Aabb aa = GetNextVerticalAabb(dt);
			if (bool b = aa.IsOver(field_aabb)) {
				if (current_y_tile > m_points)
					m_points = current_y_tile;
				return true;
			}
		}
	return false;
}

void Player::CheckCollisionsWithLevel(double dt, LevelPtr level) {
	if (IsAnyFieldBelowMe(dt, level)) {
		if (getNextYPosition(dt) < m_y || is_falling) {
			playerOnGround();
		}
	}
	else if (m_is_on_ground){
		fall();
	}
}

