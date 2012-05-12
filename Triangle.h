#include "Plane.h"

class Triangle : public Plane {
    
    float3 v1;
    float3 v2;
    float3 v3;
    
public: 
    Triangle(float3 v1, float3 v2, float3 v3, Plane plane):Plane(plane), 
    v1(v1), v2(v2), v3(v3){};
    
    Hit intersect(Ray &ray);
};