#include "Vector2D.h"

Vector2D::Vector2D(float x0, float y0) {
	x = y = 0;
}

Vector2D::~Vector2D() {}

Vector2D Vector2D::operator*(int i) {
	Vector2D v;
	v.x = x * i;
	v.y = y * i;
	return v;
}

Vector2D Vector2D::operator+=(Vector2D v2) {
	Vector2D v1;
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}