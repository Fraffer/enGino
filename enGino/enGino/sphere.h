#pragma once

#include "vector3.h"
#include "shape.h"
#include "ray.h"

namespace enGino
{
	class Sphere : public Shape
	{
	public:
		Scalar radius;
		
		Sphere(Scalar _r) : radius(_r), Shape(Transform()) {}
		Sphere(Scalar _r, Transform _t) : radius(_r), Shape(_t) {}
        Sphere(Scalar _r, Vector3 _p) : radius(_r), Shape(Transform()) { transform.translate = _p; }        
	};

    bool rayCast(Ray ray, Sphere sphere, Point3& hitPos, Versor3& hitNorm, float& distMax)
    {
        // the hitpos is (ray.p + k * ray.dir)
        // for some k such that a*k^2 + b*k + c  = 0
        Scalar a = 1;
        Scalar b = 2 * dot(ray.direction, ray.transform.translate - sphere.transform.translate);
        Scalar c = (ray.transform.translate - sphere.transform.translate).squaredNorm() - sphere.radius * sphere.radius;

        Scalar delta = b * b - 4 * a * c;

        if (delta < 0) return false; // ray misses the sphere!

        Scalar k = (-b - sqrt(delta)) / (2 * a);
        if (k < 0) return false;
        if (k > distMax) return false;
        distMax = k;

        hitPos = ray.transform.translate + k * ray.direction;
        hitNorm = (hitPos - sphere.transform.translate).normalized();
        return true;

    }

    Sphere apply(const Transform& a, const Sphere& s)
    {
        return Sphere(
            a.transformScalar(s.radius),
            a.transformPoint(s.transform.translate)            
        );
    }
} // end of namespace