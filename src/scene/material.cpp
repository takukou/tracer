#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	vec3f shade = vec3f(0.0, 0.0, 0.0);
	vec3f N = i.N;
	vec3f P = r.at(i.t);

	vec3f transparency = vec3f(1, 1, 1) - kt;
	vec3f ambient = prod(ka, scene->getAmbientLight());
	shade += ke + prod(ambient, transparency);

	for (Scene::cliter j = scene->beginLights(); j != scene->endLights(); j++) {
		
		vec3f atten = (*j)->distanceAttenuation(P) * (*j)->shadowAttenuation(P);
		
		vec3f dir = (*j)->getDirection(P).normalize();
		vec3f diffuse = prod(transparency, kd * maximum(N.dot(dir), 0.0));
		
		vec3f R = (2 * (dir.dot(N)) * N - dir).normalize();
		vec3f spec = ks * pow(maximum(R*(-r.getDirection()), 0.0), shininess*128.0);
		shade += prod(atten, diffuse + spec);
	}

	return shade.clamp();
}
