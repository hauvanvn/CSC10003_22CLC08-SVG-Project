#include "stdafx.h"
#include "Shape.h"

EllipseShape::EllipseShape()
{
	center.x = center.y = 0;
	width = height = 0;
}

EllipseShape::~EllipseShape() {}

void EllipseShape::SetElement(vector<string> data)
{
	readFigure(data);

	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].compare("cx") == 0)
			center.x = stof(data[++i]);
		else if (data[i].compare("cy") == 0)
			center.y = stof(data[++i]);
		else if (data[i].compare("rx") == 0)
			width = stof(data[++i]);
		else if (data[i].compare("ry") == 0)
			height = stof(data[++i]);
		else if (data[i].compare("r") == 0)					//This is for circle
			width = height = stof(data[++i]);
	}
}

void EllipseShape::clear()
{
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = strokeColor.A = 1;
	strokeWidth = 1;

	center.x = center.y = 0;
	width = height = 0;
	Figure::Reset();
}

Point2D EllipseShape::GetPosition()
{
	return this->center;
}

float EllipseShape::GetWidth()
{
	return this->width;
}

float EllipseShape::GetHeight()
{
	return this->height;
}
