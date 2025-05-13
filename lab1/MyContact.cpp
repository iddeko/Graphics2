#include "MyContact.h"
#include <vector>
#include <Plane.h>

using namespace cyclone;

void cyclone::MyGroundContact::init(cyclone::Particle* p, double size) {
	if (p) {
		particle = p;
	}
	this->size = size;
}

unsigned cyclone::MyGroundContact::addContact(cyclone::ParticleContact* contact, unsigned limit) const {
	cyclone::Particle* p = particle;
	cyclone::real y = p->getPosition().y;
		
	if (y - this->size < 0) {
		contact->contactNormal = { 0., 1., 0. };
		contact->particle[0] = p;
		contact->particle[1] = NULL;
		contact->penetration = this->size - y;
		contact->restitution = 1.0;
		return 1;
	}
	return 0;
}

cyclone::MyPlaneContact::MyPlaneContact(Plane *p) {
	this->plane = p;
}

void cyclone::MyPlaneContact::init(cyclone::Particle* p, double size) {
	if (p) {
		particle = p;
	}
	this->size = size;
}

unsigned cyclone::MyPlaneContact::addContact(cyclone::ParticleContact* contact, unsigned limit) const {
	if (plane == NULL) {
		return 0;
	}
	cyclone::Particle* p = particle;

	double distance = plane->getDistance(p->getPosition(), size);
	if (abs(distance) < this->size && plane->inBounds(p->getPosition())) {
		auto normal = plane->getNormal();
		if (distance < 0) {
			normal *= -1;
		}
		contact->contactNormal = normal;
		contact->particle[0] = p;
		contact->particle[1] = NULL;
		contact->penetration = size - abs(distance);
		contact->restitution = 1.0;
		return 1;
	}	
	return 0;
}