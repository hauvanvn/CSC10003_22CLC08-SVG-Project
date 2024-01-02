#pragma once
#pragma once

#ifndef _SHAPE_H_
#define _SHAPE_H_
#include "stdafx.h"

#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
using namespace rapidxml;
using namespace std;

struct Point2D
{
	float x, y;
};

struct RGBA
{
	string color = "";
	float R = 0, G = 0, B = 0, A = 1;
};

struct StopGradient {
	RGBA stop_color;
	float offset, opacity = 1;
};

class GradientColor {
protected:
	string ID;
	Point2D translate;
	vector<Point2D> points;
	vector<StopGradient> stops;

public:
	GradientColor();
	~GradientColor();

	void SetElement(vector<string>);
	void clear();
	void addStopGradient(StopGradient);

	string GetID();
	Point2D GetTranslate();
	vector<Point2D> GetPoint();
	vector<StopGradient> GetStopColor();
};

class Figure
{
public:
	/*void SetColor(RGBA color);
	void SetStrokeWidth(float width);
	void SetStrokeColor(RGBA color);*/
	Figure();
	~Figure();

	void readFigure(vector<string> data);

	void AddTranslate(Point2D position);
	void AddAngle(float angle);
	void AddFillColor(RGBA newColor);
	void AddStrokeColor(RGBA newColor);
	void SetAnchor(Point2D anchor);
	void SetScale(Point2D scale);
	void SetMatrix(vector<float> matrix);
	void Reset();

	RGBA GetFillColor();
	RGBA GetStrokeColor();
	float GetStrokeWidth();
	vector<float> GetMatrix();

protected:
	RGBA fillColor, strokeColor;
	float strokeWidth;

	Point2D anchor;
	Point2D translate;
	float angle;
	Point2D scale;
	vector<float> matrix;
};

class Stuff : public Figure
{
public:
	Stuff();
	~Stuff();

	virtual vector<PointF> getRectPos() = 0;

	Matrix* GetTransform();
	Pen* GetStroke();
	Brush* GetFill();
	Brush* GetLinearGradient(GradientColor gradient);
};

class PolygonShape : public Stuff
{
public:
	PolygonShape();
	~PolygonShape();

	void SetElement(vector<string> data);
	void clear();

	vector<Point2D> GetPoints();
	float GetWidth();
	float GetHeight();
	vector<PointF> getRectPos();

private:
	vector<Point2D> point;
	float width, height;
};

class Text : public Stuff
{
public:
	Text();
	~Text();

	void SetElement(vector<string> data);
	void clear();

	string GetFont();
	string GetText();
	float GetSize();
	Point2D GetPosition();
	vector<PointF> getRectPos();
private:
	string font;
	string text;
	float size;
	Point2D position;
};

class EllipseShape : public Stuff
{
public:
	EllipseShape();
	~EllipseShape();

	void SetElement(vector<string> data);
	void clear();

	Point2D GetPosition();
	float GetWidth();
	float GetHeight();
	vector<PointF> getRectPos();

private:
	Point2D center;
	float width, height;
};

class PolylineShape : public Stuff
{
public:
	PolylineShape();
	~PolylineShape();

	void SetElement(vector<string> data);
	void clear();

	vector<Point2D> GetPoints();
	vector<PointF> getRectPos();

private:
	vector<Point2D> points;
};

struct PathShapes {
	char type;
	vector<Point2D> points;
};

class Path : public Stuff
{
public:
	Path();
	~Path();

	void SetElement(vector<string> data);
	void clear();

	vector<PathShapes> GetPathShapes();
	vector<PointF> getRectPos();

private:
	vector<PathShapes> Shapes;
};

class Group : public Stuff
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
	void setPath(vector<Path>);
	void setShapeID(vector<int>);

	vector<Group> GetGroup();
	vector<PolygonShape> GetPolygon();
	vector<Text> GetText();
	vector<EllipseShape> GetEllipse();
	vector<PolylineShape> GetPolyline();
	vector<Path> GetPath();
	vector<int> GetShapeID();
	vector<PointF> getRectPos();

	void ApplyGroup2Child();

private:
	vector<Group> group;
	vector<PolygonShape> polygon;
	vector<Text> text;
	vector<EllipseShape> ellipse;
	vector<PolylineShape> polyline;
	vector<Path> path;
	vector<float> matrix;

	vector<int> shapeID;
};

class Drawer
{
public:
	Drawer();
	~Drawer();

	void readData(string filename);
	void readGradient(xml_node<>*);
	Group readGroup(xml_node<>*, vector<string>);
	void processData(vector<string> data, string tag);
	
	GradientColor GetGradient(string ID);

	VOID Draw(HDC hdc);

	VOID DrawPolygon(HDC hdc, PolygonShape shape);
	VOID DrawText(HDC hdc, Text shape);
	VOID DrawEllipse(HDC hdc, EllipseShape shape);
	VOID DrawPolyline(HDC hdc, PolylineShape shape);
	VOID DrawPath(HDC hdc, Path shape);
	VOID DrawGroup(HDC hdc, Group shape);

private:
	vector<PolygonShape> polygon;
	vector<Text> text;
	vector<EllipseShape> ellipse;
	vector<PolylineShape> polyline;
	vector<Group> group;
	vector<Path> path;

	vector<int> shapeID;

	vector<GradientColor> ListLinearGradient;
};

#include <locale>
#include <codecvt>

wstring String2Wstring(string s);
RGBA Hex2RGBA(string data);
string getGradientId(string ID);

#endif // !_SHAPE_H_
