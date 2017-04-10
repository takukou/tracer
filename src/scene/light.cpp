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
	ray R = ray(P, d);
	vec3f result = getColor(P);
	while(scene->intersect(R, i)) {
		// transparent
		if (i.getMaterial().kt.iszero())
			return vec3f(0.0, 0.0, 0.0);
		R = ray(R.at(i.t), d);
		result = prod(result, i.getMaterial().kt);
	}
	return result;
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
	double coeff = constant_atten + linear_atten * d + quadratic_atten * d2;
	return minimum(1.0, 1.0 / coeff);
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
	ray R = ray(P, d);
	vec3f result = getColor(P);
	while (scene->intersect(R, i)) {
		// transparent
		if (i.getMaterial().kt.iszero())
			return vec3f(0.0, 0.0, 0.0);
		R = ray(R.at(i.t), d);
		result = prod(result, i.getMaterial().kt);
	}
	return result;
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
