#include "intVector2D.h"

intVector2D::intVector2D(int x0, int y0) {
	x = y = 0;
}

intVector2D::~intVector2D() {}

intVector2D intVector2D::operator*(int i) {
	intVector2D v;
	v.x = x * i;
	v.y = y * i;
	return v;
}