#pragma once
#include "AABoundingBox.h"

class Bullet
{
public:
	Vector3 P, V;
	Vector3 P0;
	bool isSniper;
	float LifeTime;
	static const float DefaultLifeTime;
	Bullet(const Vector3 &initPos, const Vector3 &velocity,float lifetime = 150) : P0(initPos),P(initPos), V(velocity)
	{
		LifeTime = lifetime;
		isSniper = false;
	}
	Bullet()
	{
		LifeTime = 150;
	}
	void Update();
	void Render(float Angle) const;
	bool HasExpired() const 
	{ 
		Vector3 Distance = P-P0;
		if(Distance.Magnitude() > LifeTime)
			return true;
		else return false;
	}
	AABoundingBox GetAABB() const 
	{
		return AABoundingBox(P, Vector3(2, 2, 2));
	}
};