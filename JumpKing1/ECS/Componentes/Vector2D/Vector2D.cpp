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

bool Vector2D::operator== (Vector2D v) {
	return (this->x == v.x && this->y == v.y);
}