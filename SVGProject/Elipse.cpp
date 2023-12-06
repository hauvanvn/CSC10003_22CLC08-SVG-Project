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
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].compare("fill") == 0)
			fillColor = data[++i];
		else if (data[i].compare("stroke") == 0)
			strokeColor = data[++i];

		else if (data[i].compare("fill-opacity") == 0)
			fillColor_opa = stof(data[++i]);
		else if (data[i].compare("stroke-opacity") == 0)
			strokeColor_opa = stof(data[++i]);
		else if (data[i].compare("stroke-width") == 0)
			strokeWidth = stof(data[++i]);					//Finish update attribute in Figure

		else if (data[i].compare("cx") == 0)
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
	fillColor = strokeColor = "black";
	fillColor_opa = strokeColor_opa = 1;
	strokeWidth = 1;

	center.x = center.y = 0;
	width = height = 0;
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
