#include "Renderer.h"

#include <SDL.h>
#include <Windows.h>




void Renderer::LoadTexture(const std::string& filename) {
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		MessageBoxA(NULL, "Can't init SDL_IMAGE ", "Error", MB_ICONWARNING | MB_OK);
		exit(1);
	}
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (!surface) {
		MessageBoxA(NULL, ("Can't load file " + filename).c_str(), "Error", MB_ICONWARNING | MB_OK);
		exit(1);
	}

	const int width = surface->w;
	const int heigth = surface->h;
	if (((width & (width - 1)) != 0) || ((heigth & (heigth - 1)) != 0)) {
		MessageBoxA(NULL, ("Picture " + filename + "has invalid size").c_str(), "Error", MB_ICONWARNING | MB_OK);
		exit(1);
	}

	GLenum format;
	switch (surface->format->BytesPerPixel) {
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: MessageBoxA(NULL, ("Unknown file format " + filename).c_str(), "Error", MB_ICONWARNING | MB_OK);
		exit(1);
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, width, heigth, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
	if (surface)
		SDL_FreeSurface(surface);
}

void Renderer::DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h,
	double pos_x, double pos_y, double width, double height, size_t level) {
	
	const double texture_w = 1024.0;
	const double texture_h = 1024.0;

	const double left = tex_x / texture_w;
	const double right = left + tex_w / texture_w;
	const double bottom = tex_y / texture_h;
	const double top = bottom - tex_h / texture_h;

	glPushMatrix(); {
		glTranslatef(0, 0, -static_cast<int> (level));
		glBegin(GL_QUADS); {
			glColor3f(1, 1, 1);
			glTexCoord2f(right, top);	 glVertex2f(pos_x + width,	pos_y + height);
			glTexCoord2f(left, top);	 glVertex2f(pos_x,			pos_y + height);
			glTexCoord2f(left, bottom);	 glVertex2f(pos_x,			pos_y);
			glTexCoord2f(right, bottom); glVertex2f(pos_x + width,	pos_y);
		}
		glEnd();
	}
	glPopMatrix();
}

void Renderer::setProjection(size_t width, size_t height) {
	glViewport(0, 0,
		static_cast<GLsizei> (width),
		static_cast<GLsizei> (height));
	ResetProjection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Renderer::ResetProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 10);
}

void Renderer::DrawQuad(double min_x, double min_y,
	double max_x, double max_y,
	double r, double g, double b, double a) const {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_TEXTURE_2D);
	glColor4f(r, g, b, a);
	glBegin(GL_QUADS); {
		glVertex2f(min_x, min_y);
		glVertex2f(max_x, min_y);
		glVertex2f(max_x, max_y);
		glVertex2f(min_x, max_y);
	}
	glEnd();

	glPopAttrib();
}