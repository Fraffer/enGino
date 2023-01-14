#pragma once

#include "vector3.h"
#include "shape.h"
#include "ray.h"

namespace enGino
{
	class Plane : public Shape
	{
	public:
		Versor3 normal;

		Plane(Versor3 _n) : normal(_n), Shape(Transform()) {}
		Plane(Versor3 _n, Transform _t) : normal(_n), Shape(_t) {}
	};

	bool rayCast(Ray ray, Plane plane, Point3& hitPos, Versor3& hitNorm, float& distMax) {
		Scalar dn = dot(ray.direction, plane.normal);
		if (dn == 0) return false;

		Scalar k = dot(plane.transform.translate - ray.transform.translate, plane.normal) / dn;

		if (k < 0) return false;
		if (k > distMax) return false;
		distMax = k;
		hitPos = ray.transform.translate + k * ray.direction;
		hitNorm = plane.normal;
		return true;
	}
} // end of namespace