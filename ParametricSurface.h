//
//  ParametricSurface.h
//  Raytracer
//
//  Created by David Cowden on 5/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Hit.h"
#import "Ray.h"
#import "Intersectable.h"

#ifndef Raytracer_ParametricSurface_h
#define Raytracer_ParametricSurface_h

class ParametricSurface : public Intersectable {
    
    
    
public:
    
    Hit intersect(const Ray& ray);
}

#endif
