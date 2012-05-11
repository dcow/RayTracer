#include "raytracer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// global application data

////
Camera camera;

// screen resolution
const int screenWidth   = 600;
const int screenHeight  = 600;

// image to be computed by ray tracing
float3 image[screenWidth*screenHeight];

// Color of infinity:
RGB background(0,0,0);

// Ambient Light:
RGB ia(0.17, 0.17, 0.17);

PointLightSource pl0(float3(sin(M_PI_2), -1*cos(M_PI_2), 3), float3(5, 0, 0));
PointLightSource pl1(float3(-1*sin(M_PI_2), -1*cos(M_PI_2), 3), float3(0, 0, 5));
PointLightSource pl2(float3(0, 1, 3), float3(0, 5, 0));
PointLightSource pl3(float3(0,0,-2.5), float3(5,5, 5));
DirectionalLightSource dl0(float3(0, 10, 0), float3(.2, .2, .2));

#define LIGHTS 5
LightSource* lightSources[LIGHTS] = {&pl0, &pl1, &pl2, &pl3, &dl0};

// Objects:
Material material;
Material reflective(true, false, false);
Material refractive(float3(0.1f,0.1f,0.1f), 
                    float3(0.0f,0.0f,0.0f), 
                    float3(0.0f,0.0f,0.0f), 
                    float3(0.2f,0.2f,0.2f), 
                    float3(10.8f,0.8f,0.8f),
                5, 1.52, 
                true, true, false);
Material mirror(float3(0.1,0.1,0.1), float3(0,0,0), float3(1,1,1), float3(1,1,1), float3(0,0,0),
                5, 1, 
                true, false, false);
Sphere sphere(float3(0, 0, 0), 1, &refractive);
Plane  world(float3(0, 1, 0), 5, &mirror);
//Sphere world(float3(0, -55, 2.5), 50, &mirror);
Sphere wall(float3(0, 0, -55), 50, &material);
Sphere smallleft(float3(-2, 0, 0), 0.5, &reflective);
Sphere smallright(float3(2, 0, 0), 0.5, &reflective);
Sphere smalltop(float3(0, 2.71, -2), 0.5, &refractive);
Sphere smallbottom(float3(0, -2, 0), 0.5, &reflective);
Sphere smallleftback(float3(-2, -2, -2), 0.5, &refractive);
Sphere smallrightback(float3(2, -2, -2), 0.5, &refractive);
Sphere topleft(float3(-2, 2.71, 0), 1, &reflective);
Sphere topright(float3(2, 2.71, 0), 1, &reflective);

#define OBJS 11
Intersectable* objects[OBJS] = {&sphere, &wall, &world, &smallleft, &smallright,
    &smalltop, &smallbottom, &smallleftback, &smallrightback, &topleft, &topright};

float3 cast(const Ray &ray, RGB baseColor, Hit *bestHit) {
    
    // Find the closest object to the ray..
    int i;
    Hit h;
    bestHit->t = INFINITY;
    for (i = 0; i < OBJS; i++) {
        h = objects[i]->intersect(ray);
        *bestHit = (h.t < bestHit->t && h.t >= 0) ? h : *bestHit; 
    }
    
    //// Calculate the color..
    // Did the ray even hit an object?
    if (bestHit->t >= INFINITY || bestHit->t < 0) {
        return background;
    }
    
    // The ray intersects an object, calculate color using Phong.
    // Ambient + Diffuse + Specular = Phong Reflection
    
    // Ambient
    baseColor += bestHit->material->ka*ia;
    
    // + the Sum of the Diffuse and Specular contributions for each light
    
    // Diffuse and Specular are calculated independently for each light source
    for (i = 0; i < LIGHTS; i++) {
        
        // LightSource:
        LightSource *ls = lightSources[i];
        // Incident ray:
        float3 incidentLightRay = ls->getLightDirAt(bestHit->position);
        
        // Calculate Shadows
        
        // Send a ray from the object towards the light source (or ls to obj):
        Ray ShadowRay(bestHit->position + (bestHit->normal * 0.01) ,incidentLightRay);
        // shadow hit?
        bool sh = false;
        int y;
        Hit h;
        for (y = 0; y < OBJS; y++)
            if ((h = objects[y]->intersect(ShadowRay)).t < INFINITY && 
                 h.t < ls->getDistanceFrom(bestHit->position))
                sh = true;
        
        if (sh) continue;
        // the cosine of the angle between the normal and the incident light
        // used in both diffuse and specular parts
        float cosLightNormal = bestHit->normal.dot(incidentLightRay);
        
        // skip this source if the light comes from behind..
        if (cosLightNormal < 0)
            continue;
        
        // the radiance of the light source at the object.
        float3 radiance = lightSources[i]->getRadianceAt(bestHit->position);
        
        // Diffuse
        baseColor += bestHit->material->kd * cosLightNormal * radiance;
        
        // Specular
        // Reflected light vector:
        float3 reflectedLightDirection 
            = ((bestHit->normal * 2 * cosLightNormal) - incidentLightRay);
        
        // cosine of the angle between reflected light vector and the hitposition
        float cosRefHit = reflectedLightDirection.dot(bestHit->normal);
        
        if (cosRefHit < 0)
            continue;
        
        // Shinnyz        
        baseColor += bestHit->material->ks * pow(cosRefHit, bestHit->material->shininess)
                 * radiance;
    }
    // =
    
    // Return the Phong Reflection color..
    return baseColor;
}

#define MAX_DEPTH 7

RGB traceRec(const Ray ray, int depth, RGB color, bool inside) {
    if (--depth < -1)
        return color;
    
    RGB retcolor(0.0f, 0.0f, 0.0f);
    
    Hit hit;
    retcolor += cast(ray, color, &hit);
    
    if (hit.t >= INFINITY)
        return retcolor;
    
    float cosAngle = hit.normal.dot(-ray.dir);
    if (hit.material->reflective && cosAngle > 0) {
        float3 reflectedDirection = ray.dir + (hit.normal * 2 * cosAngle);
        Ray newRay(hit.position + (hit.normal * 0.01), reflectedDirection);
        retcolor += hit.material->kr * traceRec(newRay, depth, color, false);
    }
    
    float n;
    if  (hit.material->refractive) {
        n = (inside) ? hit.material->n : 1/hit.material->n;
        float cosRefrAngle2 = (1 - ((n*n) * (1-(cosAngle*cosAngle))));
        // Check for total internal reflection..
        float cosRefrAngle = (cosRefrAngle2 > 0) ? sqrtf(cosRefrAngle2) : 0.0f;
        //float cosRefrAngle = sqrtf(cosRefrAngle2);
        
        // Calculate refracted ray: Rr = (n * V) + (n * c1 - c2) * N
        float3 refNormal = (inside) ? -hit.normal : hit.normal;
        float3 refractedDirection = (cosAngle > 0) ? 
                (ray.dir * n) + (refNormal * ((n * cosAngle) - cosRefrAngle)) : 
                (ray.dir * n) - (refNormal * ((n * cosAngle) - cosRefrAngle)) ;
        Ray refractedRay(hit.position - (refNormal * 0.01), refractedDirection);

        
        retcolor += hit.material->kt * traceRec(refractedRay, depth, color, !inside);
                                                          
    }
        
        
    return retcolor;    
}

inline RGB trace(const Ray ray) {
    return traceRec(ray, MAX_DEPTH, background, false);
}


void computeImage() {
    for(int j = 0; j < screenHeight; j++) {
        for(int i = 0; i < screenWidth; i++) {
			float3 pixelColor = float3(0, 0, 0);
			float2 ndcPixelCentre( (2.0f * i - screenWidth) / screenWidth, (2.0f * j - screenHeight) / screenHeight );

			Ray ray = Ray(camera.getEye(), camera.rayDirFromNdc(ndcPixelCentre));
			
			image[j*screenWidth + i] = trace(ray);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL starts here. OpenGL just outputs the image computed to the array.

// display callback invoked when window needs to be redrawn
void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
  
    computeImage();
    glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, image);
 
    glutSwapBuffers(); // drawing finished
}

// "Animation" code... 
void onKeyPressed(unsigned char key, int x, int y) {
    
    switch (key) {
        case 'w':
            camera.setEye(camera.getEye() + float3(0,0,-0.1));
            break;
        case 'a':
            camera.setEye(camera.getEye() + float3(-0.1,0,0));
            break;
        case 's':
            camera.setEye(camera.getEye() + float3(0,0,0.1));
            break;
        case 'd':
            camera.setEye(camera.getEye() + float3(0.1,0,0));
            break;
            
    }
    glutPostRedisplay();
}



int main(int argc, char **argv) {
    glutInit(&argc, argv);						// initialize GLUT
    glutInitWindowSize(screenWidth, screenHeight);				// startup window size 
    glutInitWindowPosition(100, 100);           // where to put window on screen
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // 8 bit R,G,B,A + double buffer + depth buffer
 
    glutCreateWindow("RayTracer");				// application window is created and displayed
 
    glViewport(0, 0, screenWidth, screenHeight);

    glutDisplayFunc(onDisplay);                 // register callback
    glutKeyboardFunc(onKeyPressed);
    
    glutMainLoop();								// launch event handling loop
    
    return 0;
}



