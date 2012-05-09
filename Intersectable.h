#pragma once

#include "Material.h"
#include "Hit.h"
#include "Ray.h"

// Object abstract base class.
class Intersectable
{
protected:
	Material* material;
public:
	Intersectable(Material* material):material(material) {}
    virtual Hit intersect(const Ray& ray)=0;
};
