#pragma once

#include <vector>
#include "pcontacts.h"
#include "pfgen.h"
#include "cyclone.h"
#include "particle.h"
/*

namespace cyclone {
class ParticleWorld
{
public:
	//Data Types Definition
	typedef std::vector<Particle*> Particles;
	typedef std::vector<ParticleContactGenerator*> ContactGenerators;
protected:
	//Particle Container
	Particles particles;
	unsigned int iterations; // Whether Iteraction > 0
	ParticleForceRegistry registry; // Container for Forces
	ParticleContactResolver resolver; // Contact solver
	// Container for MyGroundContact, ParticleCollision and etc
	ContactGenerators contactGenerators;
	ParticleContact* contacts; //Array for storing contact info(must be big enough)
	unsigned int maxContacts; //maximum # of contacts
public:
	//Constructor (iteration = maxcontact * 2)
	ParticleWorld(unsigned int maxContacts, unsigned int iterations = 2);
	unsigned generateContacts(); // Call ContactGenerators for check collisions(btw floor, btw particles
	void integrate(real duration); //update all particles
	void runPhysics(real duration); // Run a physical simulation
	void startFrame(); //Reset the simulation time and reset the all forces
};
}

*/