#pragma once

#include <GL\glew.h>
#include <list>
#include <ctime>
#include <Windows.h>

#include "Utils.h"
#include "Engine.h"

///Struktura opisuj¹ca pojedyncz¹ cz¹steczkê
struct SParticle
{
	GLfloat lifetime;					      ///current lifetime of the particle
	GLfloat maximum_lifetime;                 ///time of death of particle 
	GLfloat r, g, b;                          /// color values of the particle
	GLfloat xpos, ypos, zpos;                 /// position of the particle
	GLfloat xspeed, yspeed, zspeed;           /// speed of the particle
	GLfloat size;							  ///Size of particle
};

const int MAX_PARTICLES = 500; /// maksymalna iloœæ cz¹steczek na ekranie


///Klasa opisuj¹ca system efektów cz¹steczkowych (w tym wypadku fajerwerki w menu "SubmitScore")
class ParticleSystem
{
public:
	///Domyœlny konstruktor, ustawia emiter cz¹steczek w zadanym miejscu
	ParticleSystem(double x, double y);

	///rysowanie
	void draw();

	///emituje nowe cz¹steczki
	void emitParticles();

	///aktualizuje
	void update();

	///Wybuch cz¹steczki, na jej miejsce powstaj¹ nowe
	void Explode(std::list<SParticle>::iterator particle_iterator);


private:
	size_t m_particles_count;
	double m_x;
	double m_y;
	std::list<SParticle> Particles;
	std::list<SParticle>::iterator particle_iter;


};
