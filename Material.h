#pragma once

#include "float3.h"

// Skeletal Material class. Feel free to add methods e.g. for illumination computation (shading).
class Material
{
public:
    
    float3 ka; // Ambient constant
	float3 kd; // Diffuse constant
	float3 ks; // Shinniness constant
    float3 kr; // Reflective constant
    float3 kt; // Refractive constant
	float shininess;
    float n;
    bool reflective;
    bool refractive;
	bool textured;
    
    
    Material(float3 ka, 
             float3 kd, 
             float3 ks, 
             float3 kr, 
             float3 kt, 
             float shine, 
             float n, 
             bool reflective,
             bool refractive,
             bool textured)
    
    :ka(ka),
     kd(kd),
     ks(ks), 
     kr(kr),
     kt(kt),
     shininess(shine), 
     n(n),
     reflective(reflective),
     refractive(refractive),
     textured(textured) {}
    
    Material(float3 ka, float3 kd, float3 ks, float3 kr = float3(0.5f,0.5f,0.5f), float3 kt = float3(0.5f, 0.5f, 0.5f))
    : Material(ka, kd, ks, kr, kt, 5.0f, 1.0f, false, false, false) {}
    
	Material(): Material(float3(0.5f, 0.5f, 0.5f), 
                         float3(1.0f, 1.0f, 1.0f),
                         float3(0.5f, 0.5f, 0.5f),
                         float3(0.5f, 0.5f, 0.5f),
                         float3(0.5f, 0.5f, 0.5f),
                         5.0f,
                         1.0f,
                         false,
                         false,
                         false) { }
                         
    Material(bool reflective, bool refractive, bool textured): Material() {
        this->reflective = reflective; 
        this->refractive = refractive;
        this->textured   = textured;
    }
    
    
};