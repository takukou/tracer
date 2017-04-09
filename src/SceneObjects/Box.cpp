#include <cmath>
#include <assert.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	i.obj = this;

	double tFar = numeric_limits<double>::infinity(), tNear = -tFar;
	
	vec3f dir = r.getDirection();
	vec3f org = r.getPosition();

	double aMin = -0.5, aMax = 0.5;

	int tNearAxis;

	for (int axis = 0; axis < 3; ++axis) {
		double aDir = dir[axis];
		double aOrg = org[axis];
		if (abs(aDir) < RAY_EPSILON) {
			if (aOrg < aMin || aOrg > aMax)
				return false;
		}
		
		double T1 = (aMin - aOrg) / aDir;
		double T2 = (aMax - aOrg) / aDir;
			
		if (T1 > T2) { // since T1 intersection with near plane
			double temp = T1;
			T1 = T2;
			T2 = temp;
		}

		if (T1 > tNear) {
			tNear = T1; // want largest tNear
			tNearAxis = axis;
		}

		if (T2 < tFar) {
			tFar = T2; // want smallest tFar
		}
			
		if (tNear > tFar)
			return false; // box is missed

		if (tFar < RAY_EPSILON)
			return false; // box is behind ray
	}

	i.setT(tNear);
	switch (tNearAxis) {
		case (0):
			if (dir[tNearAxis] < 0)
				i.setN(vec3f(1.0, 0.0, 0.0));
			else
				i.setN(vec3f(-1.0, 0.0, 0.0));
			break;
		case (1):
			if (dir[tNearAxis] < 0)
				i.setN(vec3f(0.0, 1.0, 0.0));
			else
				i.setN(vec3f(0.0, -1.0, 0.0));
			break;
		case (2):
			if (dir[tNearAxis] < 0)
				i.setN(vec3f(0.0, 0.0, 1.0));
			else
				i.setN(vec3f(0.0, 0.0, -1.0));
			break;
	}
	return true;
}
