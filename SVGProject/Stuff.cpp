#include "stdafx.h"
#include "Shape.h"

Stuff::Stuff()
{
}

Stuff::~Stuff()
{
}

Matrix* Stuff::GetTransform()
{
	Matrix transform;
	if (!matrix.empty()) transform.SetElements(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5]);
	transform.Translate(translate.x, translate.y);
	transform.Rotate(angle);
	transform.Scale(scale.x, scale.y);

	return transform.Clone();
}

Pen* Stuff::GetStroke()
{
	Pen pen(Color(Color(255 * strokeColor.A, strokeColor.R, strokeColor.G, strokeColor.B)));
	pen.SetWidth(strokeWidth);

	return pen.Clone();
}

Brush* Stuff::GetFill()
{
	SolidBrush brush(Color(Color(255 * fillColor.A, fillColor.R, fillColor.G, fillColor.B)));

	return brush.Clone();
}

Brush* Stuff::GetLinearGradient(GradientColor gradient)
{
	if (gradient.GetID() == "") return nullptr;

	vector<Point2D> points = gradient.GetPoint();
	if (points.size() < 2)
		for (int i = 0; i < 2; ++i) points.push_back({ 1000, 1000 });
	vector<StopGradient> stops = gradient.GetStopColor();
	Point2D translate = gradient.GetTranslate();

	Matrix transform;
	transform.Translate(translate.x, translate.y);

	float* offset = new float[stops.size()];
	Color* color = new Color[stops.size()];

	for (int i = 0; i < stops.size(); ++i)
	{
		offset[i] = stops[i].offset;
		Color temp(stops[i].opacity * 255, stops[i].stop_color.R, stops[i].stop_color.G, stops[i].stop_color.B);
		color[i] = temp;
	}
	
	vector<PointF> RectPos = getRectPos();

	LinearGradientBrush brush(RectPos[0], RectPos[1], color[0], color[stops.size() - 1]);
	brush.SetTransform(&transform);
	brush.SetInterpolationColors(color, offset, stops.size());

	delete[] offset;
	delete[] color;

	return brush.Clone();
}

vector<PointF> EllipseShape::getRectPos()
{
	PointF temp;
	vector<PointF> res;

	temp.X = center.x - width;
	temp.Y = center.y - height;
	res.push_back(temp);

	temp.X = center.x + width;
	temp.Y = center.y + height;
	res.push_back(temp);

	return res;
}

vector<PointF> Group::getRectPos()
{
	vector<PointF> res(2, PointF(0, 0));
	return res;
}

vector<PointF> Path::getRectPos()
{
	vector<PointF> res(2, PointF(0, 0));

	float minX, minY;
	float maxX, maxY;

	PointF temp;
	minX = maxX = Shapes[0].points[0].x;
	minY = maxY = Shapes[0].points[0].y;

	for (int i = 0; i < Shapes.size(); ++i)
	{
		for (int j = 0; j < Shapes[i].points.size(); ++j)
		{
			if (Shapes[i].points[j].x < minX)	minX = Shapes[i].points[j].x;
			if (Shapes[i].points[j].x > maxX)	maxX = Shapes[i].points[j].x;
			if (Shapes[i].points[j].y < minY)	minY = Shapes[i].points[j].y;
			if (Shapes[i].points[j].y > maxY)	maxY = Shapes[i].points[j].y;
		}
	}

	temp.X = minX;
	temp.Y = minY;
	res[0] = temp;

	temp.X = maxX;
	temp.Y = maxY;
	res[1] = temp;

	return res;
}

vector<PointF> PolygonShape::getRectPos()
{
	float minX, minY;
	float maxX, maxY;

	if (point.size() > 1)
	{
		minX = maxX = point[0].x;
		minY = maxY = point[0].y;

		for (int i = 0; i < point.size(); ++i)
		{
			if (point[i].x < minX)	minX = point[i].x;
			if (point[i].x > maxX)	maxX = point[i].x;
			if (point[i].y < minY)	minY = point[i].y;
			if (point[i].y > maxY)	maxY = point[i].y;
		}
	}
	else
	{
		minX = point[0].x;
		maxX = minX + width;
		minY = point[0].y;
		maxY = minY + height;
	}

	vector<PointF> res;
	PointF temp;

	temp.X = minX;
	temp.Y = minY;
	res.push_back(temp);

	temp.X = maxX;
	temp.Y = maxY;
	res.push_back(temp);

	return res;
}

vector<PointF> PolylineShape::getRectPos()
{
	vector<PointF> res(2, PointF(0, 0));

	float minX, minY;
	float maxX, maxY;

	if (points.size() > 1)
	{
		PointF temp;
		minX = maxX = points[0].x;
		minY = maxY = points[0].y;

		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].x < minX)	minX = points[i].x;
			if (points[i].x > maxX)	maxX = points[i].x;
			if (points[i].y < minY)	minY = points[i].y;
			if (points[i].y > maxY)	maxY = points[i].y;
		}

		temp.X = minX;
		temp.Y = minY;
		res[0] = temp;

		temp.X = maxX;
		temp.Y = maxY;
		res[1] = temp;
	}

	return res;
}

vector<PointF> Text::getRectPos()
{
	PointF temp;
	vector<PointF> res;

	temp.X = position.x;
	temp.Y = position.y - size;
	res.push_back(temp);

	temp.X = position.x + size;
	temp.Y = position.y;
	res.push_back(temp);

	return res;
}