//
//  LightSource.h
//  Raytracer
//
//  Created by David Cowden on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Raytracer_LightSource_h
#define Raytracer_LightSource_h

class LightSource
{
public:
	virtual float3 getRadianceAt(float3 x)=0;
	virtual float3 getLightDirAt(float3 x)=0;
	virtual float  getDistanceFrom(float3 x)=0;
    
};

#endif
