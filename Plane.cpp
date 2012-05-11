//
//  File.cpp
//  Raytracer
//
//  Created by David Cowden on 5/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "Plane.h"

Hit Plane::intersect(const Ray &ray) {

    Hit h;
    
    float bot = normal.dot(ray.dir);
    if (bot == 0)
        return h;
    
    
    float t = -(ray.origin.dot(normal) + offset)/bot;
    
    if (t < 0)
        return h;
    
    h.t = t;
    h.material = material;
    h.position = ray.origin + (ray.dir*h.t);
    h.normal = (bot > 0) ? -normal : normal;
    
    return h;
}
