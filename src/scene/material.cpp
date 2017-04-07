#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
    // You will need to call both distanceAttenuation() and shadowAttenuation()
    // somewhere in your code in order to compute shadows and light falloff.

	vec3f shade = vec3f(0.0, 0.0, 0.0);
	vec3f N = i.N;
	vec3f P = r.at(i.t);
	
	shade += ke + prod(ka, scene->getAmbientLight());

	for (Scene::cliter j = scene->beginLights(); j != scene->endLights(); j++) {
		

		vec3f light = (*j)->getColor(P);
		/*vec3f diffuse = prod(light, kd);
		diffuse *= maximum(N.dot((*j)->getDirection(P)),0.0);*/
		vec3f diffuse = kd * maximum(N.dot((*j)->getDirection(P)), 0.0);
		
		double atten = (*j)->distanceAttenuation(P);
		vec3f R = 2 * ((*j)->getDirection(P).dot(N)) * N - (*j)->getDirection(P);
		vec3f spec = ks * pow(maximum(R*(*j)->getDirection(P), 0.0), shininess*128.0);
		shade += prod(atten*light, diffuse + spec);
	}

	return shade.clamp();
}
