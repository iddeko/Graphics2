#include "Spring.h"
#include "cyclone.h"

cyclone::MySpring::MySpring(cyclone::Particle* p, double springConstant, double restLenght) : ParticleForceGenerator()
{
	other = p;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void cyclone::MySpring::updateForce(cyclone::Particle* particle, double duration)
{
	Vector3 force;
	particle->getPosition(&force);
	force -= other->getPosition();

	// Calculate the magnitude of the force
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	particle->addForce(force);

	//Vector3 force;
	//Vector3 d = p->getPosition() - other->getPosition();
	//force = - this->springConstant * (d.magnitude() - this->restLength) * d;
	//p->addForce(force);
}

cyclone::MyAnchoredSpring::MyAnchoredSpring() {}

cyclone::MyAnchoredSpring::MyAnchoredSpring(cyclone::Vector3* anchor, double springConstant, double restLength)
{
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void cyclone::MyAnchoredSpring::init(Vector3* anchor, double springConstant, double restLength) {
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void cyclone::MyAnchoredSpring::updateForce(Particle* particle, real duration)
{
	Vector3 force;
	particle->getPosition(&force);
	force -= *anchor;

	// Calculate the magnitude of the force
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	particle->addForce(force);
}