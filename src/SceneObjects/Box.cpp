#include <cmath>
#include <assert.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.
	i.obj = this;
	double tFar = numeric_limits<double>::infinity(), tNear = -tFar;
	
	vec3f dir = r.getDirection();
	vec3f org = r.getPosition();

	for (int axis = 0; axis < 3; axis++) {
		double aDir = dir[axis];
		double aOrg = org[axis];
		double aMin = this->bounds.min[axis];
		double aMax = this->bounds.max[axis];
		if (aDir == 0) {
			if (aOrg < aMin || aOrg > aMax)
				return false;
		}
		else {
			double T1 = (aMin - aOrg) / aDir;
			double T2 = (aMax - aOrg) / aDir;
			
			if (T1 > T2) { // since T1 intersection with near plane
				double temp = T1;
				T1 = T2;
				T2 = temp;
			}

			if (T1 > tNear)
				tNear = T1; // want largest tNear

			if (T2 < tFar)
				tFar = T2; // want smallest tFar
			
			if (tNear > tFar)
				return false; // box is missed

			if (tFar < 0)
				return false; // box is behind ray
		}
	}

	return true;
}
