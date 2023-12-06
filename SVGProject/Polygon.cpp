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
				fillColor.R = stof(getter);
				str >> getter;
				fillColor.G = stof(getter);
				str >> getter;
				fillColor.B = stof(getter);
			}
		}

		else if (data[i].compare("fill-opacity") == 0)
			fillColor.A = stof(data[++i]);
		else if (data[i].compare("stroke-opacity") == 0)
			strokeColor.A = stof(data[++i]);
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
			for (int j = 0; j < data[i].length(); ++j)
				if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-')
					data[i][j] = ' ';

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
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = strokeColor.A = 1;
	strokeWidth = 1;

	point.clear();
	width = height = -1;
}

vector<Point2D> PolygonShape::GetPoints()
{
	return this->point;
}

float PolygonShape::GetWidth()
{
	return this->width;
}

float PolygonShape::GetHeight()
{
	return this->height;
}
