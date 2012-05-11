//
//  Plane.h
//  Raytracer
//
//  Created by David Cowden on 5/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Ray.h"
#import "float3.h"
#import "Hit.h"
#import "Intersectable.h"

#ifndef Raytracer_Plane_h
#define Raytracer_Plane_h

class Plane : public Intersectable {
    
    float3  normal;
    float   offset;
    
public:
        
    Plane(float3 normal, float offset, Material *material): 
        Intersectable(material),
        normal(normal.normalize()), offset(offset) {};
    
    Hit intersect(const Ray& ray);
};

#endif
