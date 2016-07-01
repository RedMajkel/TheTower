#include "TextRenderer.h"


void TextRenderer::draw(int tex_x, int tex_y, double pos_x, double pos_y) {
	glPushMatrix(); {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix(); {
			Engine::Get().getRenderer()->ResetProjection();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			Engine::Get().getRenderer()->DrawSprite(tex_x, tex_y, 64, 64, pos_x, pos_y, m_width, m_height, DL::DisplayLayer(m_layer));
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void TextRenderer::drawDigit(char ch, double pos_x, double pos_y) {
	int digit = ch - '0';
	int tex_x = digit * 64;
	int tex_y = 417;
	draw(tex_x, tex_y, pos_x, pos_y);
}

void TextRenderer::drawLetter(char ch, double pos_x, double pos_y) {
	int letter = toupper(ch) - 'A';

	int letter_row = letter / 10;
	int letter_col = letter % 10;

	int tex_x = letter_col * 64;
	int tex_y = 481 + letter_row * 64;

	draw(tex_x, tex_y, pos_x, pos_y);
}

void TextRenderer::drawSpecial(char ch, double pos_x, double pos_y) {
	double tex_x = 0;
	double tex_y = 0;

	if (ch == '_') {
		tex_x = 384;
		tex_y = 598;
	}
	else {
		return;
	}
	draw(tex_x, tex_y, pos_x, pos_y);
}

void TextRenderer::drawText(const std::string& text, double pos_x, double pos_y) {
	double x = pos_x;
	double y = pos_y;

	for (size_t i = 0; i < text.size(); ++i) {
		char ch = text.at(i);
		if (isdigit(ch)) {
			drawDigit(ch, x, y);
		}
		else if (isalpha(ch)) {
			drawLetter(ch, x, y);
		}
		else if (ch == '_') {
			drawSpecial(ch, x, y);
		}
		else {
			;
		}
		x += m_width;
	}
}

void TextRenderer::drawNumber(size_t number, double pos_x, double pos_y, size_t width) {
	std::string number_str = IntToStr(number);
	size_t spaces_count = std::max(0, static_cast<int> (width) - static_cast<int> (number_str.size()));
	for (size_t i = 0; i < spaces_count; i++) {
		number_str = " " + number_str;
	}
	drawText(number_str, pos_x, pos_y);
}


