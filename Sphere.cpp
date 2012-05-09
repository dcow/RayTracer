#include "Sphere.h"

Hit Sphere::intersect(const Ray& ray) 
{
    float3 diff = ray.origin - center;
    double a = ray.dir.dot(ray.dir);
    double b = diff.dot(ray.dir) * 2.0;
    double c = diff.dot(diff) - radius * radius;
 
    double discr = b * b - 4.0 * a * c;
    if ( discr < 0 ) 
        return Hit();
    double sqrt_discr = sqrt( discr );
    double t1 = (-b + sqrt_discr)/2.0/a;
	double t2 = (-b - sqrt_discr)/2.0/a;
 
	float t = (float) (t1<t2)?t1:t2;
	if(t < 0)
		t = (t1<t2)?t2:t1;
	if (t < 0)
        return Hit();

	Hit h;
	h.t = t;
	h.material = material;
	h.position = ray.origin + ray.dir * t;
	h.normal = h.position - center;
	h.normal.normalize();
	h.uv = float2( h.normal.dot(float3(0, 1, 0)) * 0.5 + 0.5,  atan2(h.normal.z, h.normal.x) / (2 * M_PI) + 0.5 );

	return h;

}
