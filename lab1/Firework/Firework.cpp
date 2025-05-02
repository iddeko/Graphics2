#include "Firework.h"
#include <iostream>

//Firework::Firework() : rule(FireworkRule(0, 1.f, 6.f, { -5., -15., -5. }, { 5., 15., 5. }, 0.9, 40)) {
Firework::Firework() : rule(FireworkRule(0, 1.f, 3.f, { -15., -5., -15. }, { 15., 25., 15. }, 0.9, 40)) {
	this->create();
}

Firework::~Firework() {

}

void Firework::update(float duration) {
	unsigned int initial_size = fires.size();

	for (unsigned int i = 0; i < initial_size; i++) {
		if (fires[i].update(duration)) {
			if (fires[i].type == Init) {
				// Spawn childs	
				this->create(fires[i]);
			}
			if (fires[i].type == Child) {
				// Spawn childs	
				this->createFizzle(fires[i]);
			}
			fires.erase(fires.begin() + i);
			initial_size -= 1;
		}
	}
}

void Firework::create() {
	static cyclone::Random crandom;

	this->fires.push_back(Fire(Init, &rule, crandom.randomVector({ 0., 0., 0. }, { 1., 1., 1. })));
} //create init Fire


void Firework::create(Fire &parent) {
	static cyclone::Random crandom;

	cyclone::Vector3 pos = parent.particle->getPosition();
	cyclone::Vector3 color = parent.color;
	
	for (unsigned i = 0; i != rule.payloadCount; i++) {
		Fire new_fire = Fire(Child, &rule, color + crandom.randomVector({ -0.1, -0.1, -0.1 }, { .1, .1, .1 }));
		new_fire.particle->setPosition(pos);
		new_fire.color.normalise();
		this->fires.push_back(new_fire);
	}
} //create Child Fire

void Firework::createFizzle(Fire& parent) {
	static cyclone::Random crandom;

	Fire new_fire = Fire(Fizzle, &rule, { 1., 1., 1. });
	new_fire.particle->setPosition(parent.particle->getPosition());
	new_fire.particle->setVelocity(parent.particle->getVelocity());
	new_fire.history = parent.history;
	this->fires.push_back(new_fire);
} //create Fizzle Fire

void Firework::draw(bool shadow) {
	for (auto& fire : fires) {
		fire.draw(shadow);
		if (!shadow) {
			fire.drawHistory();
		}
	}
} //draw
