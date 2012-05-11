#include <math.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// for MsWindows
#include <windows.h>     
#endif // Win32 platform

#include <GLUT/glut.h>

#include "float3.h"
#include "float2.h"
#include "RGB.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLightSource.h"
#include "DirectionalLightSource.h"