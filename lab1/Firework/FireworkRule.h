#pragma once

#include <deque>
#include "particle.h"

class FireworkRule
{
public:
	FireworkRule(unsigned type, cyclone::real minAge, cyclone::real maxAge,
		const cyclone::Vector3& minVelocity, const cyclone::Vector3& maxVelocity,
		cyclone::real damping, unsigned payloadCount);
	~FireworkRule() {};
	unsigned type; //Fire type
	cyclone::real minAge; //minimum age of Fire
	cyclone::real maxAge; //maximum age of Fire
	cyclone::Vector3 minVelocity; //minimum velocity of Fire
	cyclone::Vector3 maxVelocity; //maximum velocity of Fire
	cyclone::real damping; //Fire’s damping
	unsigned payloadCount; //how many Child Fires are spawned?
};