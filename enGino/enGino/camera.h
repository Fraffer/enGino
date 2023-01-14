#pragma once

#include "vector3.h"
#include "ray.h"

namespace enGino 
{
    class Camera {
    public:

        // Determine the distance from the scene: higher the value, higher the zoom
        Scalar focal;

        int pixelDimX, pixelDimY;

        Camera(Scalar f, int sx, int sy) :focal(f), pixelDimX(sx), pixelDimY(sy) {}

        Ray primaryRay(int pixelX, int pixelY) {
            Ray r;
            r.transform.translate = Point3(0, 0, 0); // the poinf of views by definition on the origin
            Scalar clipX = 2.0f * pixelX / pixelDimX - 1.0;
            Scalar clipY = -2.0f * pixelY / pixelDimY + 1.0;

            r.direction = Vector3(clipX, clipY, focal).normalized();

            return r;
        }

    };

}