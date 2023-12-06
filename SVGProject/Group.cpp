#include "stdafx.h"
#include "Shape.h"

Group::Group()
{
	position.x = position.y = 0;
	anchor.x = anchor.y = 0;
	scale.x = scale.y = 1;
	rotation = 0;
}

Group::~Group() {}

void Group::SetElement(vector<string> data)
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

		else if (data[i].compare("transform") == 0)
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
					position.x = stof(collector[++j]);
					position.y = stof(collector[++j]);
				}
				else if (collector[j].compare("scale") == 0)
				{
					scale.x = stof(collector[++j]);
					scale.y = stof(collector[++j]);
				}
				else if (collector[j].compare("rotate") == 0)
				{
					rotation = stof(collector[++j]);

					if (j + 1 != collector.size())
					{
						bool isNum = true;
						for (int k = 0; k < collector[j + 1].length(); ++k)
							if (collector[j + 1][k] < '0' || collector[j + 1][k] > '9')
							{
								isNum = false;
								break;
							}

						if (isNum) //This is when rotate has cx, cy
						{
							anchor.x = stof(collector[++j]);
							anchor.y = stof(collector[++j]);
						}
					}
				}
			}
		}
	}


}

void Group::clear()
{
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = strokeColor.A = 1;
	strokeWidth = 1;

	position.x = position.y = 0;
	anchor.x = anchor.y = 0;
	scale.x = scale.y = 1;
	group.clear();
	polygon.clear();
	text.clear();
	ellipse.clear();
	polyline.clear();
	shapeID.clear();
}

void Group::setGroup(Group group) {
	this->group.push_back(group);
}

void Group::setPolygon(vector<PolygonShape> polygon) {
	this->polygon = polygon;
}

void Group::setText(vector<Text> text) {
	this->text = text;
}

void Group::setEllipse(vector<EllipseShape> ellipse) {
	this->ellipse = ellipse;
}

void Group::setPolyline(vector<PolylineShape> polyline) {
	this->polyline = polyline;
}

void Group::setPath(vector<Path> path) {
	this->path = path;
}

void Group::setShapeID(vector<int> shapeID) {
	this->shapeID = shapeID;
}
