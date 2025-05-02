#pragma once

#include "cyclone.h"
#include "Fire.h"
#include "FireworkRule.h"

class Firework
{
public:
	FireworkRule rule;
	std::vector<Fire> fires; //contains Fires

	Firework();
	~Firework();
	void update(float duration); //Fire create/update
	void create(); //create init Fires
	void create(Fire &parent); //create Child Fires
	void createFizzle(Fire& parent);
	void draw(bool shadow); //draw
};