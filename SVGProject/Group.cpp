#include "stdafx.h"
#include "Shape.h"

Group::Group()
{
	translate.x = translate.y = 0;
	anchor.x = anchor.y = 0;
	scale.x = scale.y = 1;
	angle = 0;
}

Group::~Group() {}

void Group::SetElement(vector<string> data)
{
	readFigure(data);
	//for (int i = 0; i < data.size(); ++i)
	//{
	//	

	//	//if (data[i].compare("transform") == 0)
	//	//{
	//	//	++i;  //go to the value of transform
	//	//	for (int j = 0; j < data[i].length(); ++j)
	//	//		if (data[i][j] == '(' || data[i][j] == ')' || data[i][j] == ',')
	//	//			data[i][j] = ' ';

	//	//	string getter;
	//	//	vector<string> collector;

	//	//	stringstream str(data[i]);
	//	//	while (str >> getter)
	//	//		collector.push_back(getter);

	//	//	for (int j = 0; j < collector.size(); ++j)
	//	//	{
	//	//		if (collector[j].compare("translate") == 0)
	//	//		{
	//	//			translate.x = stof(collector[++j]);
	//	//			translate.y = stof(collector[++j]);
	//	//		}
	//	//		else if (collector[j].compare("scale") == 0)
	//	//		{
	//	//			scale.x = stof(collector[++j]);
	//	//			scale.y = stof(collector[++j]);
	//	//		}
	//	//		else if (collector[j].compare("rotate") == 0)
	//	//		{
	//	//			angle = stof(collector[++j]);

	//	//			if (j + 1 != collector.size())
	//	//			{
	//	//				bool isNum = true;
	//	//				for (int k = 0; k < collector[j + 1].length(); ++k)
	//	//					if (collector[j + 1][k] < '0' || collector[j + 1][k] > '9')
	//	//					{
	//	//						isNum = false;
	//	//						break;
	//	//					}

	//	//				if (isNum) //This is when rotate has cx, cy
	//	//				{
	//	//					anchor.x = stof(collector[++j]);
	//	//					anchor.y = stof(collector[++j]);
	//	//				}
	//	//			}
	//	//		}
	//	//	}
	//	//}
	//}


}

void Group::clear()
{
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = strokeColor.A = 1;
	strokeWidth = 1;

	translate.x = translate.y = 0;
	anchor.x = anchor.y = 0;
	scale.x = scale.y = 1;
	group.clear();
	ellipse.clear();
	text.clear();
	ellipse.clear();
	polyline.clear();
	shapeID.clear();
	Figure::Reset();
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

vector<Group> Group::GetGroup()
{
	return this->group;
}

vector<PolygonShape> Group::GetPolygon()
{
	return this->polygon;
}

vector<Text> Group::GetText()
{
	return this->text;
}

vector<EllipseShape> Group::GetEllipse()
{
	return this->ellipse;
}

vector<PolylineShape> Group::GetPolyline()
{
	return this->polyline;
}

vector<Path> Group::GetPath()
{
	return this->path;
}

vector<int> Group::GetShapeID()
{
	return this->shapeID;
}


void Group::ApplyGroup2Child()
{
	for (int i = 0; i < group.size(); ++i)
	{
		group[i].AddTranslate(translate);
		group[i].AddAngle(angle);
		group[i].AddFillColor(fillColor);
		group[i].AddStrokeColor(strokeColor);
		//group[i].ApplyGroup2Child();
	}

	for (int i = 0; i < polygon.size(); ++i)
	{
		polygon[i].AddTranslate(translate);
		polygon[i].AddAngle(angle);
		polygon[i].AddFillColor(fillColor);
		polygon[i].AddStrokeColor(strokeColor);
	}

	for (int i = 0; i < text.size(); ++i)
	{
		text[i].AddTranslate(translate);
		text[i].AddAngle(angle);
		text[i].AddFillColor(fillColor);
		text[i].AddStrokeColor(strokeColor);
	}

	for (int i = 0; i < ellipse.size(); ++i)
	{
		ellipse[i].AddTranslate(translate);
		ellipse[i].AddAngle(angle);
		ellipse[i].AddFillColor(fillColor);
		ellipse[i].AddStrokeColor(strokeColor);
	}

	for (int i = 0; i < polyline.size(); ++i)
	{
		polyline[i].AddTranslate(translate);
		polyline[i].AddAngle(angle);
		polyline[i].AddFillColor(fillColor);
		polyline[i].AddStrokeColor(strokeColor);
	}

	for (int i = 0; i < path.size(); ++i)
	{
		path[i].AddTranslate(translate);
		path[i].AddAngle(angle);
		path[i].AddFillColor(fillColor);
		path[i].AddStrokeColor(strokeColor);
	}
}