#include "Fire.h"
#include <stdafx.h>

Fire::Fire(FireType type, FireworkRule* r, cyclone::Vector3 color) : size(0.35), type(type), age(0.), rule(r), color(color) {
	static cyclone::Random crandom;
	particle = new cyclone::Particle();
	this->maxAge = crandom.randomReal(r->minAge, r->maxAge);

	if (type == Fizzle) {
		this->maxAge /= 3;
	}

	if (type == Init) {
		particle->setVelocity(crandom.randomVector({ -30., 80., -30. }, { 30., 125., 30. }));
	} else if (type == Child) {
		particle->setVelocity(crandom.randomVector(r->minVelocity, r->maxVelocity));
	}
	particle->setMass(0.2f);
	particle->setAcceleration(0.0f, 0.0f, 0.0f);
	particle->setDamping(r->damping);
	particle->setPosition(2., 3., 2.);

	gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -10, 0));
	drag = new cyclone::ParticleDrag(0.03, 0.002);
	forces = new cyclone::ParticleForceRegistry();
	forces->add(particle, gravity);
	forces->add(particle, drag);
};

bool Fire::update(float duration) {
	forces->updateForces(duration);
	particle->integrate(duration);
	this->putHistory();
	age += duration;
	if (this->type == Init) {
		if (particle->getVelocity().y <= 1.) {
			return true;
		}
	}
	else {
		if (particle->getPosition().y < 0. || age > this->maxAge) {
			return true;
		}
	}
	return false;
}

void Fire::drawHistory() {
	if (this->history.size() < 2) {
		return;
	}
	
	for (unsigned int i = 0; i != this->history.size() - 1; i++) {
		float ratio = ((float)this->history.size() - i) / (float)this->history.size();
		ratio = 1 - ratio;
		if (ratio <= 0) {
			continue;
		}
		glColor3f(this->color.x + ratio / 1.5, this->color.y + ratio / 1.5, this->color.z + ratio / 1.5);
		glLineWidth(this->size * 10 * ratio); //Line Width
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(this->history[i].x, this->history[i].y, this->history[i].z); //Starting point
		glVertex3f(this->history[i + 1].x, this->history[i + 1].y, this->history[i + 1].z); //Ending point
		glEnd();
		glPopMatrix();
	}
}

void Fire::draw(bool shadow) {
	if (type == Fizzle && (int) (this->age * 10) % 3 == 0) {
		return;
	}
	glEnable(GL_LIGHTING);
	cyclone::Vector3 position = this->particle->getPosition();

	if (shadow) {
		glColor3f(0.1f, 0.1f, 0.1f);
	} else {
		glColor3f(this->color.x, this->color.y, this->color.z);
	}
	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glutSolidSphere(this->size, 8, 8);
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

void Fire::putHistory() {
	if (type == Fizzle) {
		while (history.size() >= (30. * (1 - (age / maxAge)))) {
			history.pop_front();
		}
	} else {
		if (history.size() >= 30) {
			history.pop_front();
		}
	}
	this->history.push_back(this->particle->getPosition());
}