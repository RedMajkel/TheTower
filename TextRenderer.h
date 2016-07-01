#ifndef _TEXT_RENDERER_H
#define _TEXT_RENDERER_H

#pragma once

#include <string>
#include <GL\glew.h>
#include <boost\shared_ptr.hpp>

#include "Engine.h"
#include "Types.h"
#include "Utils.h"


///Klasa opisuj¹ca renderer do wypisywania tekstu
class TextRenderer
{
public:
	///Domyœlny konstruktor, ustawia rozmiar tekstu
	explicit TextRenderer(double width = 0.025, double height = 0.025, size_t layer = 3) {
		SetSize(width, height);
		SetLayer(layer);
	}

	///Ustawianie rozmiaru tekstu
	void SetSize(double width, double height) {
		m_width = width;
		m_height = height;
	}

	///Ustawia warstwê na której ma zostaæ umieszczony tekst
	void SetLayer(size_t layer) {
		m_layer = layer;
	}

	///Napisz zadan¹ cyfrê na zadanej pozycji
	void drawDigit(char ch, double pos_x, double pos_y);

	///Napisz zadan¹ literê na zadanej pozycji
	void drawLetter(char ch, double pos_x, double pos_y);

	///Napisz zadany znak specjalny na zadanej pozycji
	void drawSpecial(char ch, double pos_x, double pos_y);

	///Wypisz zadany tekst na zadanej pozycji
	void drawText(const std::string& text, double pos_x, double pos_y);

	///Wypisz zadan¹ liczbê na zadanej pozycji
	void drawNumber(size_t number, double pos_x, double pos_y, size_t width = 0);

private:
	///Rysuj
	void draw(int tex_x, int tex_y, double pos_x, double pos_y);

	double m_width;
	double m_height;
	size_t m_layer;
};

///WskaŸnik na renderer tekstu
typedef boost::shared_ptr<TextRenderer> TextRendererPr;

#endif /// !_TEXT_RENDERER_H