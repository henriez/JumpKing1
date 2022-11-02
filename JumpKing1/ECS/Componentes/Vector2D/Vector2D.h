#pragma once

class Vector2D {
public:
	Vector2D(float x0 = 0, float y0 = 0);
	~Vector2D();
	float x;
	float y;

	Vector2D operator* (int i);
private:
};