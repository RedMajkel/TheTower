#ifndef _RENDERER_H
#define _RENDERER_H

#pragma once
#include <string>
#include <boost\shared_ptr.hpp>
#include <GL\glew.h>
#include <SDL_image.h>


///Klasa opisuj�ca renderer grafiki
class Renderer
{
public:
	///Domy�lny konstruktor, ustawia rozmiar kom�rek w siatce gry
	Renderer() : 
		m_tile_width(.05), m_tile_heigth(.05){
	}

	///Zwraca szeroko�� kom�rki w siatce
	double getTileWidth() {
		return m_tile_width;
	}

	///Zwraca wysoko�� kom�rki w siatce
	double getTileHeigth() {
		return m_tile_heigth;
	}

	///Ustawia rozmiar kom�rki w siatce
	void setTileSize(double width, double heigth) {
		m_tile_width = width;
		m_tile_heigth = heigth;
	}


	///Zwraca ilo�� kom�rek mieszcz�cych si� na ekranie w poziomie
	size_t getHorizontalTilesOnScreenCount() const {
		return 1.0 / m_tile_width + 0.5;
	}

	///Zwraca ilo�� kom�rek mieszcz�cych si� na ekranie w pionie
	size_t getVerticalTilesOnScreenCount() const {
		return 1.0 / m_tile_heigth + 0.5;
	}

	///Wczytuje atlas tekstur
	void LoadTexture(const std::string& filename);

	///Wy�wietla Sprite'a z zadanych wsp�rz�dnych w atlasie na podane wsp�rz�dne na ekranie
	void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, 
		double pos_x, double pos_y, double width, double height, size_t level);

	///ustawia rozmiary projekcji na ekranie
	void setProjection(size_t width, size_t height);

	///resetuje projekcj� 
	void ResetProjection();

	///Rysuje prostok�t o zadanych parametrach
	void DrawQuad(double min_x, double min_y,
		double max_x, double max_y,
		double r, double g, double b, double a) const;


private:
	GLuint m_texture;
	double m_tile_width;
	double m_tile_heigth;
};

///Wska�nik na renderer
typedef boost::shared_ptr<Renderer> RendererPtr;

#endif