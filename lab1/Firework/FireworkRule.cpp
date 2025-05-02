#include "FireworkRule.h"

FireworkRule::FireworkRule(unsigned type, cyclone::real minAge, cyclone::real maxAge,
	const cyclone::Vector3& minVelocity, const cyclone::Vector3& maxVelocity,
	cyclone::real damping, unsigned payloadCount)
	: type(type), minAge(minAge), maxAge(maxAge), minVelocity(minVelocity), maxVelocity(maxVelocity), damping(damping), payloadCount(payloadCount) {
}