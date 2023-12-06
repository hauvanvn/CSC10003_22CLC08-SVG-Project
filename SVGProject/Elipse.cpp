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
		{
			size_t foundRGB = data[++i].find("rgb");
			if (foundRGB == string::npos)
				fillColor.color = data[i];
			else
			{
				for (int j = 0; j < data[i].length(); ++j)
					if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-')
						data[i][j] = ' ';

				stringstream str(data[i]);
				string getter;

				str >> getter;
				fillColor.R = stof(getter);
				str >> getter;
				fillColor.G = stof(getter);
				str >> getter;
				fillColor.B = stof(getter);
			}
		}
		else if (data[i].compare("stroke") == 0)
		{
			size_t foundRGB = data[++i].find("rgb");
			if (foundRGB == string::npos)
				fillColor.color = data[i];
			else
			{
				for (int j = 0; j < data[i].length(); ++j)
					if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-')
						data[i][j] = ' ';

				stringstream str(data[i]);
				string getter;

				str >> getter;
				strokeColor.R = stof(getter);
				str >> getter;
				strokeColor.G = stof(getter);
				str >> getter;
				strokeColor.B = stof(getter);
			}
		}

		else if (data[i].compare("fill-opacity") == 0)
			fillColor.A = stof(data[++i]);
		else if (data[i].compare("stroke-opacity") == 0)
			strokeColor.A = stof(data[++i]);
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
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = strokeColor.A = 1;
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