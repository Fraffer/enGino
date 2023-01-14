#pragma once

#include "vector3.h"
#include "shape.h"

namespace enGino
{
	class Ray : public Shape
	{
	public:
		Versor3 direction;

		Ray() : Shape(Transform()) {}
		Ray(Transform _t) : Shape(_t) {}
		Ray(Vector3 _d) : direction(_d.normalized()), Shape(Transform()) { }
		Ray(Vector3 _d, Transform _t) : direction(_d.normalized()), Shape(_t) { }
	};
} // end of namespace