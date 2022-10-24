#pragma once

class intVector2D {
public:
	intVector2D(int x0 = 0, int y0 = 0);
	~intVector2D();
	int x;
	int y;

	intVector2D operator* (int i);
private:
};