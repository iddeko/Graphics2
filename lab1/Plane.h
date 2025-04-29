#pragma once

#include "cyclone.h"
#include <DrawUtils.H>


class Plane {
	static const int NUM_POINTS = 4;

	cyclone::Vector3 points[NUM_POINTS];
	cyclone::Vector3 normal;

public: 
	Plane() {}
	Plane(cyclone::Vector3 fst, cyclone::Vector3 snd, cyclone::Vector3 trd, cyclone::Vector3 frth) {
		points[0] = std::move(fst);
		points[1] = std::move(snd);
		points[2] = std::move(trd);
		points[3] = std::move(frth);

		cyclone::Vector3 v1 = (points[1] - points[0]);
		cyclone::Vector3 v2 = (points[2] - points[0]);

		v1.normalise();
		v2.normalise();

		normal = v2.cross(v1);
		normal.normalise();
	}

	void draw() {
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glColor4f(1, 1, 0, 0.5);
		polygonf(NUM_POINTS, points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);


		glColor3f(0, 100, 0); //Line color
		glLineWidth(3.0f); //Line Width
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(this->points[0].x, this->points[0].y, this->points[0].z); //Starting point
		cyclone::Vector3 end = this->points[0] + (this->normal * 5);
		glVertex3f(end.x, end.y, end.z); //Starting point
		glEnd();
		glPopMatrix();
	}

	bool inBounds(cyclone::Vector3 point) {
		float smallest_x = INT_MAX;
		float biggest_x = -INT_MAX;
		float smallest_z = INT_MAX;
		float biggest_z = -INT_MAX;

		for (auto& vertex: points) {
			if (vertex.x < smallest_x) {
				smallest_x = vertex.x;
			}
			if (vertex.z < smallest_z) {
				smallest_z = vertex.z;
			}
			if (vertex.x > biggest_x) {
				biggest_x = vertex.x;
			}
			if (vertex.z > biggest_z) {
				biggest_z = vertex.z;
			}
		}

		return point.x > smallest_x && point.x < biggest_x && point.z > smallest_z && point.z < biggest_z;
	}

	double getDistance(cyclone::Vector3 point, float size) {
		cyclone::Vector3 pa = (point - points[0]);
		double d = pa.dot(normal);
		return d;
	}

	const cyclone::Vector3& getNormal() {
		return this->normal;
	}

};