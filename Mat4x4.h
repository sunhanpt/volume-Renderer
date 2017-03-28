#pragma once
#include "Vector4.h"
#include "UserInput.h"

class Mat4x4
{
public:
	float p[4][4];		//  00 01 02 03
				//  10 11 12 13
				//  20 21 22 23
				//  30 31 32 33
	double saveTranslate[3];
	Mat4x4()
	{
		SetIdentity();
		saveTranslate[0] = 0.0;
		saveTranslate[1] = 0.0;
		saveTranslate[2] = 0.0;
	}
	void SetIdentity()
	{
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				p[i][j] = 0.0;
		p[0][0] = 1;	p[1][1] = 1;
		p[2][2] = 1;	p[3][3] = 1;
	}
	void PushTranslate()
	{
		for(int i = 0 ; i < 3 ; i++)
			saveTranslate[i] = p[i][3];
	}
	void PopTranslate()
	{
		for(int i = 0 ; i < 3 ; i++)
			p[i][3] = saveTranslate[i];
	}
	void ClearTranslate()
	{
		for(int i = 0 ; i < 3 ; i++)
			p[i][3] = 0.0f;
	}
	void MultiplyMat(Mat4x4 m)
	{
		float resultM[4][4];
		int i = 0, j = 0 , k = 0;
		for(i = 0 ; i < 4 ; i++)
		{
			for(j = 0 ; j < 4 ; j++)
			{
				resultM[i][j] = 0.0f;
				for(k = 0 ; k < 4 ; k++)
				{
					resultM[i][j] += m.p[i][k] * p[k][j];
				}
			}
		}
		for(i = 0 ; i < 4 ; i++)
		{
			for(j = 0 ; j < 4 ; j++)
			{
				p[i][j] = resultM[i][j];
			}
		} 
	}
	void RotateX(float theta)
	{
//		SetIdentity();
		Mat4x4 r;
		float rad = theta * 3.141592/180.0f;
		r.p[1][1] = cos(rad);
		r.p[1][2] = -sin(rad);
		r.p[2][1] = sin(rad);
		r.p[2][2] = cos(rad);
		MultiplyMat(r);
	}
	void RotateZ(float theta)
	{
//		SetIdentity();
		Mat4x4 r;
		float rad = theta * 3.141592/180.0f;
		r.p[0][0] = cos(rad);
		r.p[0][1] = -sin(rad);
		r.p[1][0] = sin(rad);
		r.p[1][1] = cos(rad);
		MultiplyMat(r);
	}
	void RotateY(float theta)
	{
//		SetIdentity();
		Mat4x4 r;
		float rad = theta * 3.141592/180.0f;
		r.p[0][0] = cos(rad);
		r.p[0][2] = sin(rad);
		r.p[2][0] = -sin(rad);
		r.p[2][2] = cos(rad);
		MultiplyMat(r);
	}
	void Translate(float x, float y, float z)
	{
//		SetIdentity();
		Mat4x4 t;
		t.p[0][3] = x;
		t.p[1][3] = y;
		t.p[2][3] = z;
		MultiplyMat(t);
	}

	Vector4 operator * (Vector4 in)
	{
		Vector4 out;
		for(int j=0; j<4; j++) 
		{
			out.p[j] = 0.0;
			for(int i=0; i<4; i++)
				out.p[j] += p[j][i]*in.p[i]; 
		}
		return out;
	}

	Mat4x4 operator * (Mat4x4 in)
	{
		Mat4x4 out;
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
			{
				out.p[i][j] = 0;
				for(int k=0; k<4; k++)
					out.p[i][j]+=
						p[i][k]*in.p[k][j];
			}
		
		return out;
	}
	Mat4x4 &operator =(const Mat4x4 & src)
	{
		for(int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 4 ; j++)
			{
				p[i][j] = src.p[i][j];
			}
		}
		return *this;
	}
};
