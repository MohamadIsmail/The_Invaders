#pragma once

#include "Vector3.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>


class ThirdPersonCamera
{
public:
	float BreathingEffect;
	float breathValue;
	Vector3 P;
	Vector3 Rot;
	Vector3 R;
	Vector3 U;
	Vector3 N;
	Vector3 T;
	Vector3 Up;
	float constY;
	float Distance;
	float MinDistance;
	float MaxDistance;
	float MinRotationY;
	float MaxRotationY;
	bool SniperMode;
	Vector3 GetLookDirection()
	{
		return N;
	}
	Vector3 GetRightDirection()
	{
		return R;
	}
	Vector3 GetTarget()
	{
		return T;
	}
	ThirdPersonCamera(const Vector3 &eye, const Vector3 &center, const Vector3 &up)
	{
		Reset(eye, center, up,0);
	}
	ThirdPersonCamera()
	{
		Reset(0, 0, 0, 
			0, 0, -1, 
			0, 1, 0,0);
		Rot.x = 1;
		Rot.y = 1;
		Distance = 70;
		MinDistance = 1;
		MaxDistance = 70;
		MinRotationY = 7;
		MaxRotationY = 88;
		breathValue = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
		constY = 0;
	}
	ThirdPersonCamera(
		float eyeX,
		float eyeY,
		float eyeZ,
		float centerX,
		float centerY,
		float centerZ,
		float upX,
		float upY,
		float upZ,
		float Rotation)
	{
		Reset(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ,Rotation);
	}
	void Reset(
		float eyeX,
		float eyeY,
		float eyeZ,
		float centerX,
		float centerY,
		float centerZ,
		float upX,
		float upY,
		float upZ,
		float Rotation)
	{
		Vector3 eyePt(eyeX, eyeY, eyeZ);
		Vector3 centerPt(centerX, centerY, centerZ);
		Vector3 upVec(upX, upY, upZ);
		Reset(eyePt, centerPt, upVec,0);
	}
	void Reset(const Vector3 &eye, const Vector3 &center, const Vector3 &up,float Rotation)
	{
		SniperMode = false;
		BreathingEffect = 0;
		N = eye - center;
		T = center;
		R = Vector3::CrossProduct(up, N);
		U = Vector3::CrossProduct(N, R);
		R.Normalize();
		U.Normalize();
		N.Normalize();
		for (int i = 0 ; i < Rotation ; i++)
		{
			RotateLeft();
		}
		for (int i = 0 ; i < 20 ; i++)
		{
			RotateUp();
		}
	}
	void Walk(float dist)
	{
		T.x -= dist*N.x;
		T.z -= dist*N.z;
	}
	void Strafe(float dist)
	{
		T.x += dist * R.x;
		T.z += dist * R.z;
	}
	void Fly(float dist)
	{
		T += dist * U;
	}
	void ZoomIn()
	{
		if(Distance < MinDistance)
			Distance = MinDistance;
		Distance -= 1;
	}
	void ZoomOut()
	{
		if(Distance > MaxDistance)
			Distance = MaxDistance;
		Distance += 1;
	}
	void RotateUp()
	{
		if(Rot.x > MaxRotationY)
			return;
		Rot.x += 1;
		U.RotateAround(-1, R);
		N.RotateAround(-1, R);
	}
	void RotateDown()
	{
		if(Rot.x < MinRotationY)
			return;
		Rot.x -= 1;
		U.RotateAround(1, R);
		N.RotateAround(1, R);
	}
	void RotateRight()
	{
		Rot.y -= 1;
		N.RotateAround(-1, Up);
		R.RotateAround(-1, Up);
	}
	void RotateLeft()
	{
		Rot.y += 1;
		N.RotateAround(1, Up);
		R.RotateAround(1, Up);
	}
	void RotateRight(float Angle)
	{
		Rot.y -= Angle;
		N.RotateAround(-Angle, Up);
		R.RotateAround(-Angle, Up);
	}
	void RotateLeft(float Angle)
	{
		Rot.y += Angle;
		N.RotateAround(Angle, Up);
		R.RotateAround(Angle, Up);
	}
	void RotateUp(float Angle)
	{
		if(Rot.x > MaxRotationY)
			return;
		Rot.x += Angle;
		U.RotateAround(-Angle, R);
		N.RotateAround(-Angle, R);
	}
	void RotateDown(float Angle)
	{
		if(Rot.x < MinRotationY)
			return;
		Rot.x -= Angle;
		U.RotateAround(Angle, R);
		N.RotateAround(Angle, R);
	}
	void Tellgl()
	{
		glLoadIdentity();
		gluPerspective(60, 1366.0/1280/*640/480*/, 1, 10000);
		if(SniperMode)
		{
			MinRotationY = -40;
			BreathingEffect += 1.5;
			P = T - GetLookDirection()*200;
			breathValue = -5 + sin((BreathingEffect*22/7)/180)*1.2;
			P.y = breathValue;
			Vector3 t = P - GetLookDirection();
			gluLookAt(
			P.x, P.y, P.z,
			t.x, t.y, t.z,
			0, U.y, 0);
		}
		else
		{
			P = T + GetLookDirection()*Distance;
			gluLookAt(
			P.x, P.y, P.z,
			T.x, T.y, T.z,
			0, U.y, 0);
		}
		glMatrixMode(GL_MODELVIEW);
	}
};
