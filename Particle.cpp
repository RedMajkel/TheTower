#include "Particle.h"

void Particle::CalculateChangePerSecond() {
	change.color = (change.color - current.color) / changeDuration;
	change.angle = (change.angle - current.angle) / changeDuration;
	change.size = (change.size - current.size) / changeDuration;
}
