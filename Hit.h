#pragma once

#include <math.h>
#include "float2.h"
#include "float3.h"
#include "Material.h"

// Hit record structure. Contains all data that describes a ray-object intersection point.
class Hit
{
public:
	Hit()
	{
		t = INFINITY;
	}
    Hit(float3 position, float3 normal, Material * m):
    position(position), normal(normal), material(m) {
        Hit();
    }
    
	float t;
	float3 position;
	float3 normal;
	float2 uv;
	Material* material;
};

