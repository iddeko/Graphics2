#pragma once

#include "plinks.h"
#include "pcontacts.h"

namespace cyclone {
class ParticleCollision : public ParticleLink
{
public:
	double size = 2; //particle size
public:
	unsigned addContact(ParticleContact* contact, unsigned limit) const override;
};

}
