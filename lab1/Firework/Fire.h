#pragma once

#include "cyclone.h"
#include "FireworkRule.h"

enum FireType {
	Init,
	Child,
	Fizzle,
};

class Fire
{
public:
	float size; // Fire size (0.5)
	FireType type; //Fire type (set in the constructor)
	float age; //Fire’s current age
	float maxAge; //Fire’s max age

	cyclone::Particle* particle;
	cyclone::ParticleForceRegistry* forces;
	cyclone::ParticleGravity* gravity;
	cyclone::ParticleDrag* drag;

	FireworkRule* rule;//Which rule this particle is influenced by?
	cyclone::Vector3 color; //Fire color
	std::deque<cyclone::Vector3> history; //history saving

	Fire(FireType type, FireworkRule* r, cyclone::Vector3 color);
	~Fire() {};

	bool update(float duration); //return bool
	void drawHistory();
	void draw(bool shadow);
	void setRule(FireworkRule* r); //set a particular rule
	void putHistory(); //Save current position in the m_history
};