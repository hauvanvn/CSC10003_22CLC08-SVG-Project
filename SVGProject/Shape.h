#pragma once

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

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
	void SetAngle(float angle);

	RGBA GetColor();
	float GetStrokeWidth();
	RGBA GetStrokeColor();
	Point GetCenter();
	float GetAngle();

protected:
	RGBA color;
	float stroke_width;
	RGBA stroke_color;
	Point center;
	float rotation;
};

class Polygon : public Figure
{
public:
	Polygon();
	~Polygon();

	void SetElement(vector<string> s);
	void clear();

	void SetPosition(vector<Point> pt);
	void SetCenter();

	vector<Point> GetPosition();

private:
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

	void SetPosition(Point position);
	void SetMradius(Point m_radius);
	void SetCenter();

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

	void SetPosition(vector<Point> pt);
	void SetCenter();

	vector<Point> GetPosition();

private:
	vector<Point> points;
};

class Group: public Figure
{
public:
	Group();
	~Group();

	bool IsEmpty();
	void SetElement(vector<string> s);
	void clear();

	void SetCenter();
	void MovePosition();
	void Rotate();

	void setGroup(Group);
	void setPolygon(vector<Polygon>);
	void setWord(vector<Word>);
	void setEllipse(vector<Ellipse>);
	void setCircle(vector<Circle>);
	void setPolyline(vector<Polyline>);
	void setShapeId(vector<int>);

	vector<Group> GetGroup();
	vector<Polygon> GetPolygon();
	vector<Word> GetText();
	vector<Ellipse> GetEllipse();
	vector<Circle> GetCircle();
	vector<Polyline> GetPolyline();
private:
	Point position;
	
	vector<Group> group;
	vector<Polygon> polygon;
	vector<Word> text;
	vector<Ellipse> ellipse;
	vector<Circle> circle;
	vector<Polyline> polyline;

	vector<int> shapeID;
};

class Drawer
{
public:
	Drawer();
	~Drawer();
	
	void readData(string filename);
	Group readGroup(istream&, vector<string>);
	void processData(vector<string> data);
	//void Draw(RenderWindow& window);

	//void DrawPolygon(RenderWindow& window, Polygon shape);
	//void DrawWord(RenderWindow& window, Word shape);
	//void DrawEllipse(RenderWindow& window, Ellipse shape);
	//void DrawCircle(RenderWindow& window, Circle shape);
	//void DrawLine(RenderWindow& window, Polyline shape, Point p1, Point p2);
	//void DrawPolyline(RenderWindow& window, Polyline shape);
	//void DrawGroup(RenderWindow& window, Group shape);

private:
	vector<Polygon> polygon;
	vector<Word> text;
	vector<Ellipse> ellpise;
	vector<Circle> circle;
	vector<Polyline> polyline;
	vector<Group> group;

	vector<int> shapeID;
};

Point FindIntersectionPoint(Point A, Point B, Point C, Point D);

Point MovePoint(Point x, float rotation, Point center);

#endif // !_SHAPE_H_
