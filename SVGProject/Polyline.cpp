#include "stdafx.h"
#include "Shape.h"

PolylineShape::PolylineShape() {}

PolylineShape::~PolylineShape() {}

void PolylineShape::SetElement(vector<string> data)
{
	Point2D secondPoint;
	bool line = false;

	readFigure(data);

	for (int i = 0; i < data.size(); ++i)
	{
		//This part is postion of points making up a line
		if (data[i].compare("x1") == 0 || data[i].compare("y1") == 0)
		{
			line = true; //Mark this is a line

			if (points.size() != 1)
			{
				Point2D temp;
				if (data[i][0] == 'x')        temp.x = stof(data[++i]);
				else    temp.y = stof(data[++i]);
				points.push_back(temp);
			}
			else
			{
				if (data[i][0] == 'x')        points[0].x = stof(data[++i]);
				else    points[0].y = stof(data[++i]);
			}
		}
		else if (data[i].compare("x2") == 0 || data[i].compare("y2") == 0)
		{
			if (points.size() != 1)
			{
				if (data[i][0] == 'x')        secondPoint.x = stof(data[++i]);
				else    secondPoint.y = stof(data[++i]);
			}
			else
			{
				if (data[i][0] == 'x')        secondPoint.x = stof(data[++i]);
				else    secondPoint.y = stof(data[++i]);
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
				if (j % 2 == 0)
				{
					Point2D temp;
					temp.x = stof(getter);
					points.push_back(temp);
				}
				else    points[j / 2].y = stof(getter);
		}
	}

	if (line)
		points.push_back(secondPoint);
}

void PolylineShape::clear()
{
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = 1;
	strokeColor.A = 1;
	strokeWidth = 1;

	points.clear();
	Figure::Reset();
}

vector<Point2D> PolylineShape::GetPoints()
{
	return this->points;
}
