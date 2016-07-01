#include "SpriteGrid.h"
#include "Engine.h"


SpriteGrid::SpriteGrid()
{
	size_t heigth = Engine::Get().getRenderer()->getVerticalTilesOnScreenCount() + 10;
	size_t width = Engine::Get().getRenderer()->getHorizontalTilesOnScreenCount();
	m_grid.resize(heigth);
	for (size_t i = 0; i < heigth; i++) {
		m_grid.at(i).resize(width);
	}
}

void SpriteGrid::setLevel(const LevelPtr lvl, double dy) {
	int half_grid_height = (m_grid.size() - 1) * 0.35;

	for (size_t y = 0; y < m_grid.size(); ++y) {
		std::vector<SpritePtr>& row = m_grid.at(y);
		for (size_t x = 0; x < row.size(); ++x) {
			int draw_x = x;
			int draw_y = y + static_cast<int>(dy) - half_grid_height + 1;
			if (draw_y < 0)
				draw_y = 0;
			const FT::FieldType& ft = lvl->Field(draw_x, draw_y);
			if (ft != FT::None) {
				setSprite(x, y, m_sprites.at(ft));
			}
			else {
				setSprite(x, y, SpritePtr());
			}
		}
	}
}

void SpriteGrid::draw(double dy) const {
	const double tile_width = Engine::Get().getRenderer()->getTileWidth();
	const double tile_height = Engine::Get().getRenderer()->getTileHeigth();

	glPushMatrix(); 
	{
		glTranslatef(0, dy*tile_height - 0.45, 0);

		double offset = dy - static_cast<int>(dy);
		glTranslatef(0, -offset*tile_height, 0);
		for (size_t y = 0; y < m_grid.size(); ++y) {
			const std::vector<SpritePtr>& row = m_grid.at(y);
			for (size_t x = 0; x < row.size(); ++x) {
				const SpritePtr& sprite = row.at(x);
				if (sprite) {
					sprite->DrawCurrentFrame(1.0 - (x + 1) *tile_width, y*tile_height, tile_width, tile_height);
				}
			}
		}
	}
	glPopMatrix();
}

void SpriteGrid::storeSprite(FT::FieldType ft, SpritePtr sp) {
	if (m_sprites.size() <= static_cast<size_t>(ft)) {
		m_sprites.resize(ft + 1);
	}
	m_sprites.at(ft) = sp;

}


