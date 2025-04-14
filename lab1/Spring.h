#pragma once

#include "cyclone.h"
#include "pfgen.h"

namespace cyclone {
	class MySpring : public ParticleForceGenerator //Generic Force generating class
	{
		cyclone::Particle* other; //Target particle
		double springConstant; //Spring constant (k)
		double restLength; //lest length
	public:
		MySpring(cyclone::Particle* p, double springConstant, double restLenght);
		void updateForce(cyclone::Particle* p, double duration);
	};
}
