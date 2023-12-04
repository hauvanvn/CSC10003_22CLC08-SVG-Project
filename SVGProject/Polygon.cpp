#include "stdafx.h"
#include "Shape.h"


PolygonShape::PolygonShape() {
	width = height = -1;
}

PolygonShape::~PolygonShape() {};

void PolygonShape::SetElement(vector<string> data)
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

		else if (data[i].compare("width") == 0)
			width = stof(data[++i]);
		else if (data[i].compare("height") == 0)
			height = stof(data[++i]);

		else if (data[i].compare("x") == 0 || data[i].compare("y") == 0) //This is for rectangle
		{
			if (point.size() != 1)
			{
				Point2D temp;
				if (data[i].compare("x") == 0)		temp.x = stof(data[++i]);
				else	temp.y = stof(data[++i]);
				point.push_back(temp);
			}
			else
			{
				if (data[i].compare("x") == 0)		point[0].x = stof(data[++i]);
				else	point[0].y = stof(data[++i]);
			}
		}
		else if (data[i].compare("points") == 0)
		{
			i++;
			stringstream str(data[i]);
			string getter;

			for (int j = 0; str >> getter; ++j)
			{
				if (j % 2 == 0)
				{
					Point2D temp;
					temp.x = stof(getter);
					point.push_back(temp);
				}
				else	point[j / 2].y = stof(getter);
			}
		}
	}
}

void PolygonShape::clear() {
	fillColor = strokeColor = "black";
	fillColor_opa = strokeColor_opa = 1;
	strokeWidth = 1;

	point.clear();
	width = height = -1;
}