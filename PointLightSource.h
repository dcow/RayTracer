//
//  PointLightSource.h
//  Raytracer
//
//  Created by David Cowden on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Raytracer_PointLightSource_h
#define Raytracer_PointLightSource_h

#include "LightSource.h"

class PointLightSource : public LightSource
{
	float3 position;
	float3 power;
public:
	PointLightSource(float3 position, float3 power):position(position), power(power){}
    
	virtual float3 getRadianceAt(float3 x){return power * (1 / (position - x).dot(position - x));}
	virtual float3 getLightDirAt(float3 x){return (position - x).normalize();}
	virtual float  getDistanceFrom(float3 x){return (position - x).norm();}
};

#endif
