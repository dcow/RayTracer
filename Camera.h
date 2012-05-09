#pragma once

#include "float2.h"
#include "float3.h"

// Skeletal Camera class. Feel free to add custom initialization, set aspect ratio to fit viewport dimensions, or animation.
class Camera
{
	float3 eye;

	float3 ahead;
	float3 right;
	float3 up;

	float2 tanFovHalf;
public:
	float3 getEye()
	{
		return eye;
	}
    void setEye(float3 e) {
        eye = e;
    }
    
	Camera()
	{
		eye = float3(0, 0, 5);
		ahead = float3(0, 0, -1);
		right = float3(1, 0, 0);
		up = float3(0, 1, 0);
		tanFovHalf = float2(1, 1);
	}

	float3 rayDirFromNdc(const float2 ndc)
	{
		return (ahead + right * ndc.x * tanFovHalf.x + up * ndc.y * tanFovHalf.y).normalize();
	}
    
};
