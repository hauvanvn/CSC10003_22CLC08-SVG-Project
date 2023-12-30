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

void Group::SetElement(vector<string> data) {
	readFigure(data);
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
		group[i].SetMatrix(matrix);
	}

	for (int i = 0; i < polygon.size(); ++i)
	{
		polygon[i].AddTranslate(translate);
		polygon[i].AddAngle(angle);
		polygon[i].AddFillColor(fillColor);
		polygon[i].AddStrokeColor(strokeColor);
		polygon[i].SetMatrix(matrix);
	}

	for (int i = 0; i < text.size(); ++i)
	{
		text[i].AddTranslate(translate);
		text[i].AddAngle(angle);
		text[i].AddFillColor(fillColor);
		text[i].AddStrokeColor(strokeColor);
		text[i].SetMatrix(matrix);
	}

	for (int i = 0; i < ellipse.size(); ++i)
	{
		ellipse[i].AddTranslate(translate);
		ellipse[i].AddAngle(angle);
		ellipse[i].AddFillColor(fillColor);
		ellipse[i].AddStrokeColor(strokeColor);
		ellipse[i].SetMatrix(matrix);
	}

	for (int i = 0; i < polyline.size(); ++i)
	{
		polyline[i].AddTranslate(translate);
		polyline[i].AddAngle(angle);
		polyline[i].AddFillColor(fillColor);
		polyline[i].AddStrokeColor(strokeColor);
		polyline[i].SetMatrix(matrix);
	}

	for (int i = 0; i < path.size(); ++i)
	{
		path[i].AddTranslate(translate);
		path[i].AddAngle(angle);
		path[i].AddFillColor(fillColor);
		path[i].AddStrokeColor(strokeColor);
		path[i].SetMatrix(matrix);
	}
}