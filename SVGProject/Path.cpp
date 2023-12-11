#include "stdafx.h"
#include "Shape.h"

Path::Path() 
{
	fillColor.A = 0;
}

Path::~Path() {}

void Path::SetElement(vector<string> data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		readFigure(data);

		if (data[i].compare("d") == 0)
		{
			++i;
			for (int j = 0; j < data[i].length(); ++j) //This removes coma from the string
				if (data[i][j] == ',')
					data[i][j] = ' ';

			for (int j = 0; j < data[i].length(); ++j)
				if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-' && data[i][j] != ' ' && data[i][j] != '\n')
				{
					PathShapes shape;
					shape.type = data[i][j];

					data[i][j] = ' ';

					string curData = "";
					for (int k = j; k < data[i].length(); ++k) //copying the part of string from data[i] to count how many shapes of the same type will be created
						curData += data[i][k];

					stringstream str(curData);
					string getter;
					int count = 0;
					bool stopPoint = false;

					while (str >> getter) //count similar shapes
					{
						for (int k = 0; k < getter.length(); ++k)
							if ((getter[k] < '0' || getter[k] > '9') && getter[k] != '-' && getter[k] != '.')
							{
								if (k != 0) //seperate cases where the letter stuck between 2 number
									count++;
								stopPoint = true;
								break;
							}
						if (stopPoint)
							break;
						count++;
					}

					if (shape.type == 'M' || shape.type == 'm' || shape.type == 'L' || shape.type == 'l')
						for(int k = 0; k < count / 2; ++k)
							Shapes.push_back(shape);
					else if (shape.type == 'H' || shape.type == 'h' || shape.type == 'V' || shape.type == 'v')
						for (int k = 0; k < count; ++k)
							Shapes.push_back(shape);
					else if (shape.type == 'C' || shape.type == 'c')
						for (int k = 0; k < count / 6; ++k)
							Shapes.push_back(shape);
					else if(shape.type == 'Z' || shape.type == 'z')
						Shapes.push_back(shape);
				}
					
			stringstream str(data[i]);
			string getter;
			Point2D tempPoint;

			for (int j = 0; j < Shapes.size(); ++j)
			{
				if (Shapes[j].type == 'M' || Shapes[j].type == 'm' || Shapes[j].type == 'L' || Shapes[j].type == 'l')
				{
					str >> getter;
					tempPoint.x = stof(getter);
					str >> getter;
					tempPoint.y = stof(getter);
					Shapes[j].points.push_back(tempPoint);
				}
				else if (Shapes[j].type == 'H' || Shapes[j].type == 'h')
				{
					str >> getter;
					tempPoint.x = stof(getter);
					tempPoint.y = 0;
					Shapes[j].points.push_back(tempPoint);
				}
				else if (Shapes[j].type == 'V' || Shapes[j].type == 'v')
				{
					str >> getter;
					tempPoint.x = 0;
					tempPoint.y = stof(getter);
					Shapes[j].points.push_back(tempPoint);
				}
				else if (Shapes[j].type == 'C' || Shapes[j].type == 'c')
					for (int k = 0; k < 3; ++k)
					{
						str >> getter;
						tempPoint.x = stof(getter);
						str >> getter;
						tempPoint.y = stof(getter);
						Shapes[j].points.push_back(tempPoint);
					}
			}
		}
	}
}

void Path::clear()
{
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = 0; strokeColor.A = 1;
	strokeWidth = 1;

	Shapes.clear();
	Figure::Reset();
}

vector<PathShapes> Path::GetPathShapes()
{
	return this->Shapes;
}
