#include "Spring.h"
#include "cyclone.h"

cyclone::MySpring::MySpring(cyclone::Particle* p, double springConstant, double restLenght) : ParticleForceGenerator()
{
	other = p;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void cyclone::MySpring::updateForce(cyclone::Particle* p, double duration)
{
	Vector3 force;
	Vector3 d = p->getPosition() - other->getPosition();
	force = - this->springConstant * (d.magnitude() - this->restLength) * d;
	p->addForce(force);
}