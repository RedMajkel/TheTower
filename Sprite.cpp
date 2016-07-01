#include "Sprite.h"
#include "Engine.h"



Sprite::Sprite(const SpriteConfigData& data):
	m_data(data), m_current_frame(0), m_current_frame_duration(0.0)
{
}

void Sprite::SetCurrentFrame(size_t frame_num) {
	m_current_frame = frame_num;
	m_current_frame_duration = 0.0;
}

void Sprite::Update(double dt) {
	m_current_frame_duration += dt;

	if (m_current_frame_duration >= m_data.frame_duration) {
		m_current_frame++;
		m_current_frame_duration -= m_data.frame_duration;
	}

	if (m_current_frame >= m_data.frame_count) {
		if (m_data.loop) {
			m_current_frame = 0;
		} else {
			m_current_frame = m_data.frame_count - 1;
		}
	}
}

void Sprite::DrawCurrentFrame(double x, double y, double width, double heigth) {
	Engine::Get().getRenderer()->DrawSprite(m_data.left + m_data.width * m_current_frame,
		m_data.bottom, m_data.width, m_data.height, x, y, width, heigth, m_data.level);
}