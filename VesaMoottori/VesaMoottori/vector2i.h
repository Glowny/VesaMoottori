#pragma once

struct vector2i
{
	vector2i(int X, int Y)
	{
		x = X;
		y = Y;
	}

	vector2i()
	{}

	int x;
	int y;
};

struct vector2f
{
	vector2f(float X, float Y)
	{
		x = X;
		y = Y;
	}
	vector2f()
	{}

	float x;
	float y;
};