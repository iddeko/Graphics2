#pragma once

#include <vector>
#include "particle.h"
#include "Plane.h"
#include "plinks.h"

namespace cyclone {
class MyGroundContact : public cyclone::ParticleContactGenerator
{
	cyclone::Particle* particle; //Container for all particles
	double size; //particle size(all particles have a same size)
public:
	MyGroundContact() {};
	~MyGroundContact() {};
	void init(cyclone::Particle* p, double size); //add particle p in the container
	//Detect collision. If there are collisions, write info in the contact (limit=max # of contacts)
	//If there are collision, return the number of collisions
	virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const;
};

class MyPlaneContact :public cyclone::ParticleContactGenerator
{
	cyclone::Particle* particle;
	double size; //size of the particle
	Plane *plane; //vertices of the plane
	cyclone::Vector3 contactNormal; //Normal of the plane
public:
	MyPlaneContact(Plane *p);
	~MyPlaneContact() {};
	void init(cyclone::Particle* p, double size);
	virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const;
};
}