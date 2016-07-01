#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(double x, double y) :
	m_x(x), m_y(y), m_particles_count(500) {

}

void ParticleSystem::draw() {
	particle_iter = Particles.begin();
	for (size_t i = 0; i < Particles.size(); i++, particle_iter++) {
	
		glPushMatrix(); {
			double x = particle_iter->xpos;
			double y = particle_iter->ypos;
			double z;
			glTranslatef(0, 0, particle_iter->zpos);
			double size = particle_iter->size;
			
			glBegin(GL_QUADS); {

				glColor3f(particle_iter->r, particle_iter->g, particle_iter->b);
				glTexCoord2f(0.25, 0);	 glVertex2f(x + size, y + size);
				glTexCoord2f(0.1875, 0);	 glVertex2f(x, y + size);
				glTexCoord2f(0.1875, 0.0625);	 glVertex2f(x, y);
				glTexCoord2f(0.25, 0.0625);  glVertex2f(x + size, y);
			}
			glEnd();
		}
		glPopMatrix();
	}
}

void ParticleSystem::emitParticles() {
	for (size_t i = 0; i < 200; i++) {
		SParticle particle = { 0, NRand()*2,
			NRand(), NRand(), NRand(),
			m_x, m_y, 0,
			NRand()*0.01, NRand()*0.01, NRand()*0.01,
			0.02
		};
		Particles.push_front(particle);
	}
}

void ParticleSystem::update() {

	static std::clock_t  oldtime = std::clock();
	std::clock_t newtime = std::clock();
	double timebetweenframes = (double)(newtime - oldtime) / (double)CLOCKS_PER_SEC;

	particle_iter = Particles.begin();
	while (particle_iter != Particles.end()){
		particle_iter->xpos += particle_iter->xspeed;
		particle_iter->ypos += particle_iter->yspeed;
		particle_iter->zpos += particle_iter->zspeed;
		particle_iter->r -= 0.001;
		particle_iter->g -= 0.001;
		particle_iter->b -= 0.001;

		particle_iter->lifetime = particle_iter->lifetime + timebetweenframes;
		if (particle_iter->lifetime > particle_iter->maximum_lifetime) {
			if (abs(NRand()) > 0.8) {
				Explode(particle_iter);
			}
			particle_iter = Particles.erase(particle_iter);
		}
		else {
			particle_iter++;
		}
	}
	oldtime = newtime;
}

void ParticleSystem::Explode(std::list<SParticle>::iterator particle_iter){
	for (size_t i = 0; i < 20; i++) {
		SParticle particle = { 0, 0.8 * particle_iter->maximum_lifetime,
			NRand(), NRand(), NRand(),
			particle_iter->xpos, particle_iter->ypos, particle_iter->zpos,
			NRand()*0.01, NRand()*0.01, NRand()*0.01,
			particle_iter->size
		};

		if (Particles.size() < m_particles_count && particle_iter->maximum_lifetime > 0.7)
			Particles.push_front(particle);
	}
}