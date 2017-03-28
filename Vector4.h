#pragma once

class Vector4
{
public:
	float p[4];
	Vector4()
	{
		p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 1.0;
	}
	Vector4(float x, float y, float z)
	{
		p[0] = x; p[1] = y; p[2] = z; p[3] = 1.0;
	}
	inline float * GetVector(void)
	{
		float * Pos = new float[4];
		Pos[0] = p[0]; Pos[1] = p[1]; Pos[2] = p[2]; Pos[3] = p[3];
		return Pos;
	}
	Vector4 operator * (float scale) {
		Vector4 out(*this);
		out.p[0] *= scale; out.p[1] *= scale; out.p[2] *= scale;
		return out;
	}
};

