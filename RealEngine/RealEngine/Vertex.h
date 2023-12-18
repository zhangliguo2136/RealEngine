#pragma once

#include "Vector.h"

struct TMeshVertex
{
	TMeshVertex() {};
	TMeshVertex(const Vector3f& p, const Vector3f& n, const Vector3f& t, const Vector2f& uv)
		:Position(p), Normal(n), TangentU(t), TexCoord(uv){}

	Vector3f Position;
	Vector3f Normal;
	Vector3f TangentU;
	Vector2f TexCoord;
};