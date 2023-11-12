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

class Polygon
{
public:
	Polygon();
	~Polygon();

	void SetElement(vector<string> s);
	void SetPoints(vector<Point> point);
	void SetFillColor(RGBA color);
	void SetStroke(float width, RGBA color);
	void Draw(RenderWindow& window);

private:
	string type;
	vector<Point> point;
	RGBA color;
	float width, height;
	float stroke_width;
	RGBA stroke_color;
};

class Word
{
public:
	Word();
	~Word();

	void SetElement(vector<string> s);
	void clear();
	void Draw(RenderWindow& window);

private:
	string font;
	string text;
	float size;
	Point position;
	RGBA color;
};

class Ellipse
{
public:
	Ellipse();
	~Ellipse();

	void SetElement(vector<string> s);
	void clear();
	void Draw(RenderWindow& window);

protected:
	Point position, m_radius;
	RGBA color;
	float stroke_width;
	RGBA stroke_color;
};

class Circle: public Ellipse
{
public:
	Circle();
	~Circle();

	void SetRadius(vector<string> s);
	void clearRadius();
	void Draw(RenderWindow& window);

private:
	float radius;
};

class Polyline
{
public:
	Polyline();
	~Polyline();

	void SetElement(vector<string> s);

private:
	vector<Point> points;
	RGBA color;
	float stroke_width;
	RGBA stroke_color;
};

#endif // !_SHAPE_H_
