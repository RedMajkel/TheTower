#ifndef _RENDERER_H
#define _RENDERER_H

#pragma once
#include <string>
#include <boost\shared_ptr.hpp>
#include <GL\glew.h>
#include <SDL_image.h>


///Klasa opisuj¹ca renderer grafiki
class Renderer
{
public:
	///Domyœlny konstruktor, ustawia rozmiar komórek w siatce gry
	Renderer() : 
		m_tile_width(.05), m_tile_heigth(.05){
	}

	///Zwraca szerokoœæ komórki w siatce
	double getTileWidth() {
		return m_tile_width;
	}

	///Zwraca wysokoœæ komórki w siatce
	double getTileHeigth() {
		return m_tile_heigth;
	}

	///Ustawia rozmiar komórki w siatce
	void setTileSize(double width, double heigth) {
		m_tile_width = width;
		m_tile_heigth = heigth;
	}


	///Zwraca iloœæ komórek mieszcz¹cych siê na ekranie w poziomie
	size_t getHorizontalTilesOnScreenCount() const {
		return 1.0 / m_tile_width + 0.5;
	}

	///Zwraca iloœæ komórek mieszcz¹cych siê na ekranie w pionie
	size_t getVerticalTilesOnScreenCount() const {
		return 1.0 / m_tile_heigth + 0.5;
	}

	///Wczytuje atlas tekstur
	void LoadTexture(const std::string& filename);

	///Wyœwietla Sprite'a z zadanych wspó³rzêdnych w atlasie na podane wspórzêdne na ekranie
	void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, 
		double pos_x, double pos_y, double width, double height, size_t level);

	///ustawia rozmiary projekcji na ekranie
	void setProjection(size_t width, size_t height);

	///resetuje projekcjê 
	void ResetProjection();

	///Rysuje prostok¹t o zadanych parametrach
	void DrawQuad(double min_x, double min_y,
		double max_x, double max_y,
		double r, double g, double b, double a) const;


private:
	GLuint m_texture;
	double m_tile_width;
	double m_tile_heigth;
};

///WskaŸnik na renderer
typedef boost::shared_ptr<Renderer> RendererPtr;

#endif