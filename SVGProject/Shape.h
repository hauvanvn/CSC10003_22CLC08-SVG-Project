#pragma once
#pragma once

#ifndef _SHAPE_H_
#define _SHAPE_H_
#include "stdafx.h"

#include "rapidxml.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace rapidxml;
using namespace std;

struct Point2D
{
	float x, y;
};
//
//struct RGBA
//{
//	float R, G, B, A;
//};

class Figure
{
public:
	Figure() {
		fillColor = strokeColor = "black";
		fillColor_opa = strokeColor_opa = 1;
		strokeWidth = 1;
	}
	/*void SetColor(RGBA color);
	void SetStrokeWidth(float width);
	void SetStrokeColor(RGBA color);

	RGBA GetColor();
	float GetStrokeWidth();
	RGBA GetStrokeColor();*/

protected:
	string fillColor, strokeColor;
	float fillColor_opa, strokeColor_opa;
	float strokeWidth;
};

class PolygonShape : public Figure
{
public:
	PolygonShape();
	~PolygonShape();

	void SetElement(vector<string> data);
	void clear();

	//void SetPosition(Point2D pt);

	//vector<Point2D> GetPosition();

private:
	vector<Point2D> point;
	float width, height;
};

class Text : public Figure
{
public:
	Text();
	~Text();

	void SetElement(vector<string> data);
	void clear();
	//
	//	void SetFont(string font);
	//	void SetText(string text);
	//	void SetSize(float size);
	//	void SetPosition(Point2D position);
	//
	//	string GetFont();
	//	string GetText();
	//	float GetSize();
	//	Point2D GetPosition();
	//
private:
	string font;
	string text;
	float size;
	Point2D position;
};
//
class EllipseShape : public Figure
{
public:
	EllipseShape();
	~EllipseShape();

	void SetElement(vector<string> data);
	void clear();
	//
	//	void SetPoisition(Point2D position);
	//	void SetMradius(Point2D m_radius);
	//
	//	Point2D GetPosition();
	//	Point2D GetMradius();
	//
private:
	Point2D center;
	float width, height;
};

class PolylineShape : public Figure
{
public:
	PolylineShape();
	~PolylineShape();

	void SetElement(vector<string> data);
	void clear();

	/*void SetPosition(Point2D pt);

	vector<Point2D> GetPosition();*/

private:
	vector<Point2D> points;
};

class Group : public Figure
{
public:
	Group();
	~Group();

	void SetElement(vector<string> data);
	void clear();

	void setGroup(Group);
	void setPolygon(vector<PolygonShape>);
	void setText(vector<Text>);
	void setEllipse(vector<EllipseShape>);
	void setPolyline(vector<PolylineShape>);
	void setShapeID(vector<int>);
private:
	Point2D position;
	Point2D anchor;
	Point2D scale;
	float rotation;

	vector<Group> group;
	vector<PolygonShape> polygon;
	vector<Text> text;
	vector<EllipseShape> ellipse;
	vector<PolylineShape> polyline;

	vector<int> shapeID;
};

class Path : public Figure
{
public:
	Path();
	~Path();

	void SetElement(vector<string> data);
	void clear();

private:
	vector<Point2D> points;
};

class Drawer
{
public:
	Drawer();
	~Drawer();

	void readData(string filename);
	Group readGroup(xml_node<>*, vector<string>);
	void processData(vector<string> data, string tag);
	/*void Draw(RenderWindow& window);

	void DrawPolygon(RenderWindow& window, Polygon shape);
	void DrawWord(RenderWindow& window, Word shape);
	void DrawEllipse(RenderWindow& window, Ellipse shape);
	void DrawCircle(RenderWindow& window, Circle shape);
	void DrawLine(RenderWindow& window, Polyline shape, Point2D p1, Point2D p2);
	void DrawPolyline(RenderWindow& window, Polyline shape);
	void DrawGroup(RenderWindow& window, Group shape);*/

private:
	vector<PolygonShape> polygon;
	vector<Text> text;
	vector<EllipseShape> ellipse;
	vector<PolylineShape> polyline;
	vector<Group> group;

	vector<int> shapeID;
};

Point2D FindIntersectionPoint2D(Point2D A, Point2D B, Point2D C, Point2D D);

#endif // !_SHAPE_H_