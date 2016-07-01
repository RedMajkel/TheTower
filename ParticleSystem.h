#pragma once

#include <GL\glew.h>
#include <list>
#include <ctime>
#include <Windows.h>

#include "Utils.h"
#include "Engine.h"

///Struktura opisuj�ca pojedyncz� cz�steczk�
struct SParticle
{
	GLfloat lifetime;					      ///current lifetime of the particle
	GLfloat maximum_lifetime;                 ///time of death of particle 
	GLfloat r, g, b;                          /// color values of the particle
	GLfloat xpos, ypos, zpos;                 /// position of the particle
	GLfloat xspeed, yspeed, zspeed;           /// speed of the particle
	GLfloat size;							  ///Size of particle
};

const int MAX_PARTICLES = 500; /// maksymalna ilo�� cz�steczek na ekranie


///Klasa opisuj�ca system efekt�w cz�steczkowych (w tym wypadku fajerwerki w menu "SubmitScore")
class ParticleSystem
{
public:
	///Domy�lny konstruktor, ustawia emiter cz�steczek w zadanym miejscu
	ParticleSystem(double x, double y);

	///rysowanie
	void draw();

	///emituje nowe cz�steczki
	void emitParticles();

	///aktualizuje
	void update();

	///Wybuch cz�steczki, na jej miejsce powstaj� nowe
	void Explode(std::list<SParticle>::iterator particle_iterator);


private:
	size_t m_particles_count;
	double m_x;
	double m_y;
	std::list<SParticle> Particles;
	std::list<SParticle>::iterator particle_iter;


};
