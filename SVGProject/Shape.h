#pragma once

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
using namespace sf;

struct Point
{
	float x, y;
};

struct RGBA
{
	float R, G, B, A;
};

class Figure
{
public:
	void SetColor(RGBA color);
	void SetStrokeWidth(float width);
	void SetStrokeColor(RGBA color);

	RGBA GetColor();
	float GetStrokeWidth();
	RGBA GetStrokeColor();

protected:
	RGBA color;
	float stroke_width;
	RGBA stroke_color;
};

class Polygon : public Figure
{
public:
	Polygon();
	~Polygon();

	void SetElement(vector<string> s);
	void clear();

	void SetPosition(Point pt);

	vector<Point> GetPosition();

private:
	string type;
	vector<Point> point;
	float width, height;
	
};

class Word : public Figure
{
public:
	Word();
	~Word();

	void SetElement(vector<string> s);
	void clear();

	void SetFont(string font);
	void SetText(string text);
	void SetSize(float size);
	void SetPosition(Point position);

	string GetFont();
	string GetText();
	float GetSize();
	Point GetPosition();

private:
	string font;
	string text;
	float size;
	Point position;
};

class Ellipse : public Figure
{
public:
	Ellipse();
	~Ellipse();

	void SetElement(vector<string> s);
	void clear();

	void SetPoisition(Point position);
	void SetMradius(Point m_radius);

	Point GetPosition();
	Point GetMradius();

protected:
	Point position, m_radius;
};

class Circle : public Ellipse
{
public:
	Circle();
	~Circle();

	void SetRadius(vector<string> s);
	void clearRadius();

	void SetRadius(float radius);

	float GetRadius();

private:
	float radius;
};

class Polyline : public Figure
{
public:
	Polyline();
	~Polyline();

	void SetElement(vector<string> s);
	void clear();

	void SetPosition(Point pt);

	vector<Point> GetPosition();

private:
	vector<Point> points;
};

class Group: private Figure
{
public:
	Group();
	~Group();

	void SetElement(vector<string> s);
	void clear();

private:
	Point position;
	Point center;
	float rotation;

	vector<Polygon> polygon;
	vector<Word> text;
	vector<Ellipse> ellpise;
	vector<Circle> circle;
	vector<Polyline> polyline;
};

class Drawer
{
public:
	Drawer();
	~Drawer();
	void read(string filename);
	void Draw(RenderWindow& window);

	void DrawPolygon(RenderWindow& window, Polygon shape);
	void DrawWord(RenderWindow& window, Word shape);
	void DrawEllipse(RenderWindow& window, Ellipse shape);
	void DrawCircle(RenderWindow& window, Circle shape);
	void DrawLine(RenderWindow& window, Polyline shape, Point p1, Point p2);
	void DrawPolyline(RenderWindow& window, Polyline shape);
	void DrawGroup(RenderWindow& window, Group shape);

private:
	vector<Polygon> polygon;
	vector<Word> text;
	vector<Ellipse> ellpise;
	vector<Circle> circle;
	vector<Polyline> polyline;

	vector<int> shapeID;
};

Point FindIntersectionPoint(Point A, Point B, Point C, Point D);

#endif // !_SHAPE_H_
