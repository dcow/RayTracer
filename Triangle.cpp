#include "Triangle.h"

Hit Triangle::intersect(Ray &ray) {
    
    Hit h = Plane::intersect(ray);
    
    if (h.t > 0 && h.t < INFINITY)
        return h;
    
    //Check if the point is in the triangle.
    
    
    
    return h;
}