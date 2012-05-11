//
//  DirectionalLightSource.h
//  Raytracer
//
//  Created by David Cowden on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Raytracer_DirectionalLightSource_h
#define Raytracer_DirectionalLightSource_h

#include "LightSource.h"

class DirectionalLightSource : public LightSource
{
	float3 dir;
	float3 radiance;
public:
	DirectionalLightSource(	float3 dir, float3 radiance):dir(dir.normalize()), radiance(radiance){}
	virtual float3 getRadianceAt(float3 x){return radiance;}
	virtual float3 getLightDirAt(float3 x){return dir;}
	virtual float  getDistanceFrom(float3 x){return INFINITY;}
};

#endif
