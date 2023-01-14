#pragma once

#include "transform.h"

namespace enGino
{
	class Shape
	{
	public:
		Shape(Transform _t) : transform(_t) {}		
		virtual void move(Vector3 dir, float value) { transform.translate += dir * value; }
		virtual void rotate(Vector3 dir, float value) { transform.rotate = transform.rotate * Quaternion::fromAngleAxis(value, dir); }
		Transform transform;
	};            
} // end of namespace