#pragma once

#include "vector3.h"
#include "quaternion.h"

namespace enGino
{
	class Transform
	{
	public:
		Scalar scale;
		Vector3 translate;
		Quaternion rotate;

		Transform() : scale(1), translate(0, 0, 0), rotate(Quaternion::identity()) {}

		Vector3 forwardVector() const
		{
			return rotate.apply(Vector3(0, 0, 1));
		}

		Vector3 rightVector() const
		{
			return rotate.apply(Vector3(1, 0, 0));
		}

		Vector3 upVector() const
		{
			return rotate.apply(Vector3(0, 1, 0));
		}

		Vector3 transformPoint(const Vector3& p) const
		{
			return rotate.apply(p * scale) + translate;
		}

		Vector3 transformVersor(const Vector3& p) const
		{
			return rotate.apply(p);
		}

		Vector3 transformVector(const Vector3& p) const
		{
			return rotate.apply(p * scale);
		}

		Scalar transformScalar(const Scalar& p) const
		{
			return p * scale;
		}

		Transform inverse() const
		{
			Transform t;

			t.scale = (1 / scale);
			t.rotate = rotate.conjugated();
			t.translate = t.rotate.apply(-translate * t.scale);

			return t;
		}

		void invert()
		{
			scale = (1 / scale);
			rotate.conjugate();
			translate = rotate.apply(-translate * scale);
		}
	};

	//  first b then a
	Transform operator * (const Transform& a, const Transform& b)
	{
		Transform t;
		t.rotate = a.rotate * b.rotate;
		t.scale = a.scale * b.scale;
		t.translate = a.transformVector(b.translate) + a.translate;
		return t;
	}
}