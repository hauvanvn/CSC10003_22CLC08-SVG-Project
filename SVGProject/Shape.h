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
protected:
	RGBA color;
	float stroke_width;
	RGBA stroke_color;
};

class Polygon : private Figure
{
public:
	Polygon();
	~Polygon();

	void SetElement(vector<string> s);
	void clear();

	friend class Drawer;

private:
	string type;
	vector<Point> point;
	float width, height;
	
};

class Word : private Figure
{
public:
	Word();
	~Word();

	void SetElement(vector<string> s);
	void clear();

	friend class Drawer;

private:
	string font;
	string text;
	float size;
	Point position;
};

class Ellipse : protected Figure
{
public:
	Ellipse();
	~Ellipse();

	void SetElement(vector<string> s);
	void clear();

	friend class Drawer;

protected:
	Point position, m_radius;
	RGBA color;
	float stroke_width;
	RGBA stroke_color;
};

class Circle : public Ellipse
{
public:
	Circle();
	~Circle();

	void SetRadius(vector<string> s);
	void clearRadius();

	friend class Drawer;

private:
	float radius;
};

class Polyline : private Figure
{
public:
	Polyline();
	~Polyline();

	void SetElement(vector<string> s);
	void clear();

	friend class Drawer;

private:
	vector<Point> points;
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
	void DrawLine(RenderWindow& window, const Polyline& shape, const Point& p1, const Point& p2);
	void DrawPolyline(RenderWindow& window, Polyline shape);

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
