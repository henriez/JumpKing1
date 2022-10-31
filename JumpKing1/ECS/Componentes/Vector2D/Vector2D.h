#pragma once

class Vector2D {
public:
	Vector2D(float x0 = 0, float y0 = 0);
	~Vector2D();
	float x;
	float y;

	Vector2D operator* (int i);
	Vector2D operator+= (Vector2D v2);
private:
};