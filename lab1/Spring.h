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

	class MyAnchoredSpring : public ParticleForceGenerator
	{
	protected:
		Vector3* anchor; /** Anchor position. * : can change if you want*/
		double springConstant; /** spring constant. */
		double restLength; /** rest length. */
	public:
		MyAnchoredSpring();
		MyAnchoredSpring(Vector3* anchor, double springConstant, double restLength);
		const Vector3* getAnchor() const { return anchor; } //return anchor position
		void init(Vector3* anchor, double springConstant, double restLength); //set values
		virtual void updateForce(Particle* particle, real duration);
	};
}
