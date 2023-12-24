#include "stdafx.h"
#include "Shape.h"

GradientColor::GradientColor() {}
GradientColor::~GradientColor() {}

void GradientColor::SetElement(vector<string> data)
{
	Point2D secondPoint;

	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].compare("id") == 0)
			ID = data[++i];
		else if (data[i].compare("x1") == 0 || data[i].compare("y1") == 0)
		{
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

		else if (data[i].compare("garadientTransform") == 0)
		{
			++i;  //go to the value of transform
			for (int j = 0; j < data[i].length(); ++j)
				if (data[i][j] == '(' || data[i][j] == ')' || data[i][j] == ',')
					data[i][j] = ' ';

			string getter;
			vector<string> collector;

			stringstream str(data[i]);
			while (str >> getter)
				collector.push_back(getter);

			for (int j = 0; j < collector.size(); ++j)
			{
				if (collector[j].compare("translate") == 0)
				{
					translate.x = stof(collector[++j]);
					translate.y = stof(collector[++j]);
				}
				//else if (collector[j].compare("scale") == 0)
				//{
				//	scale.x = stof(collector[++j]);
				//	scale.y = stof(collector[++j]);
				//}
				//else if (collector[j].compare("rotate") == 0)
				//{
				//	angle = stof(collector[++j]);

				//	if (j + 1 != collector.size())
				//	{
				//		bool isNum = true;
				//		for (int k = 0; k < collector[j + 1].length(); ++k)
				//			if (collector[j + 1][k] < '0' || collector[j + 1][k] > '9')
				//			{
				//				isNum = false;
				//				break;
				//			}

				//		if (isNum) //This is when rotate has cx, cy
				//		{
				//			anchor.x = stof(collector[++j]);
				//			anchor.y = stof(collector[++j]);
				//		}
				//	}
				//}
			}
		}
	}

	if (points.size() != 0)
		points.push_back(secondPoint);
}

void GradientColor::clear(){
	ID = ""; 
	translate.x = translate.y = 0;
	points.clear();
	stops.clear();
}

void GradientColor::addStopGradient(StopGradient stopGradient){
	stops.push_back(stopGradient);
}

