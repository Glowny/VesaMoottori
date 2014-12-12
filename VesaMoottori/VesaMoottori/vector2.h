#pragma once
struct vector2i
{
	vector2i(int X, int Y)
	{
		x = X;
		y = Y;
	}

	vector2i()
	{
		x = 0;
		y = 0;
	}

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
	{
		x = 0.0f;
		y = 0.0f;
	}

	vector2f operator* (float number)
	{
		vector2f temp;
		temp.x *= temp.x * number;
		temp.y *= temp.y * number;
		return temp;
	}

	float x;
	float y;
};