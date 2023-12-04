#include "stdafx.h"
#include "Shape.h"

PolylineShape::PolylineShape() {}

PolylineShape::~PolylineShape() {}

void PolylineShape::SetElement(vector<string> data)
{
	Point2D secondPoint;
	bool line = false;

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

		//This part is postion of points making up a line
		else if (data[i].compare("x1") == 0 || data[i].compare("y1") == 0)
		{
			line = true; //Mark this is a line

			if (points.size() != 1)
			{
				Point2D temp;
				if (data[i].compare("x") == 0)		temp.x = stof(data[++i]);
				else	temp.y = stof(data[++i]);
				points.push_back(temp);
			}
			else
			{
				if (data[i].compare("x") == 0)		points[0].x = stof(data[++i]);
				else	points[0].y = stof(data[++i]);
			}
		}
		else if (data[i].compare("x2") == 0 || data[i].compare("y2") == 0)
		{
			if (points.size() != 1)
			{
				if (data[i].compare("x") == 0)		secondPoint.x = stof(data[++i]);
				else	secondPoint.y = stof(data[++i]);
			}
			else
			{
				if (data[i].compare("x") == 0)		secondPoint.x = stof(data[++i]);
				else	secondPoint.y = stof(data[++i]);
			}
		}

		//This part is postion of points making up a polyline
		else if (data[i].compare("points") == 0)
		{
			i++;
			for (int j = 0; j < data[i].length(); ++j)
				if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-')
					data[i][j] = ' ';

			string getter;
			stringstream str(data[i]);
			for (int j = 0; str >> getter; ++j)
			{
				if (j % 2 == 0)
				{
					Point2D temp;
					temp.x = stof(getter);
					points.push_back(temp);
				}
				else	points[j / 2].y = stof(getter);
			}
		}
	}

	if (line)
		points.push_back(secondPoint);
}

void PolylineShape::clear()
{
	fillColor = strokeColor = "black";
	fillColor_opa = strokeColor_opa = 1;
	strokeWidth = 1;

	points.clear();
}

