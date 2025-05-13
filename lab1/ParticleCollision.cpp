#include "ParticleCollision.h"

using namespace cyclone;

unsigned ParticleCollision::addContact(ParticleContact* contact, unsigned limit) const
{
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];
	Vector3 aToB = contact->particle[1]->getPosition() - contact->particle[0]->getPosition();
	double pen = size * 2 - aToB.magnitude();
	if (pen > 0) {
		contact->penetration = pen;
		aToB.normalise();
		contact->contactNormal = aToB * -1;
		contact->restitution = 1.0;
		return 1;
	}
	//Check whether two particles collide, if they are, enter information in
	//ParticleContact and return 1
	//if there is no collision, just return 0 (No information in the ParticleContact)
	return 0;
}