#pragma once

#include <stdlib.h>
#include <math.h>

#include "float3.h"
#include "Intersectable.h"
#include "Hit.h"
#include "Ray.h"

// Object realization.
class Sphere : public Intersectable
{
	float3 center;
	float radius;
public:
    Sphere(const float3& center, float radius, Material* material):
		Intersectable(material),
		center(center),
		radius(radius)
    {
    }

    Hit intersect(const Ray& ray);
}; 

