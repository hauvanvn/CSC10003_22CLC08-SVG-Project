#include "Shape.h"

Circle::Circle()
{
	rotation = 0;
}

Circle::~Circle()
{
}

void Circle::SetRadius(vector<string> s) {
	for (int i = 0; i < s.size(); ++i)
		if (s[i].compare("r") == 0)
		{
			for (int j = 0; j < s[i + 1].length(); ++j)
				if ((s[i + 1][j] < '0' || s[i + 1][j] > '9') && s[i + 1][j] != '.')
					s[i + 1][j] = ' ';
			radius = stof(s[i + 1]);
			break;
		}
}

void Circle::clearRadius()
{
	radius = 0;
	rotation = 0;
}

void Circle::SetRadius(float radius)
{
	this->radius = radius;
}

float Circle::GetRadius()
{
	return this->radius;
}