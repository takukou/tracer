#include <cmath>

#include "light.h"

double DirectionalLight::distanceAttenuation( const vec3f& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


vec3f DirectionalLight::shadowAttenuation( const vec3f& P ) const
{
	vec3f d = getDirection(P).normalize();
	isect i;
	ray R(P, d);
	if (scene->intersect(R, i)) {
		return vec3f(0.0, 0.0, 0.0);
	}
	else {
		return vec3f(1.0, 1.0, 1.0);
	}
}

vec3f DirectionalLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f DirectionalLight::getDirection( const vec3f& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation(const vec3f& P) const
{
	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, I assume no attenuation and just return 1.0
	double d = (P - position).length();
	double d2 = (P - position).length_squared();
	
	return minimum(1.0, 1.0/(constant_atten + linear_atten * d + quadratic_atten * d2));
}

vec3f PointLight::getColor(const vec3f& P) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f PointLight::getDirection(const vec3f& P) const
{
	return (position - P).normalize();
}

void PointLight::setAttentuation(const double constant, const double linear, const double quadratic) {
	constant_atten = constant;
	linear_atten = linear;
	quadratic_atten = quadratic;
}


vec3f PointLight::shadowAttenuation(const vec3f& P) const
{
	vec3f d = getDirection(P).normalize();
	isect i;
	ray R(P, d);
	if (scene->intersect(R, i)) {
		double Q = (position - P).length();
		if (Q > i.t) {
			return vec3f(0.0, 0.0, 0.0);
		}
		else {
			return vec3f(1.0, 1.0, 1.0);
		}
	}
	else {
		return vec3f(1.0, 1.0, 1.0);
	}
}
double AmbientLight::distanceAttenuation(const vec3f& P) const
{
	return 1.0;
}

vec3f AmbientLight::getColor(const vec3f& P) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f AmbientLight::getDirection(const vec3f& P) const
{
	// no direction, illuminates surrounding
	return vec3f(0.0, 0.0, 0.0);
}


vec3f AmbientLight::shadowAttenuation(const vec3f& P) const
{
	// illuminates surrounding
	return vec3f(1, 1, 1);
}
