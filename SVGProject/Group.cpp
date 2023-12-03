#include "Shape.h"

Group::Group()
{
	rotation = 0;
}

Group::~Group()
{
}

bool Group::IsEmpty() {
	if (polygon.size() != 0 || text.size() != 0 || ellipse.size() != 0 || circle.size() != 0 || polyline.size() != 0)
		return false;
	return true;
}

void Group::SetElement(vector<string> s)
{
	string data = "";
	for (int i = 2; i < s.size(); ++i)
		data += s[i] + " ";

	for (int i = 0; i < data.length(); ++i)
		if (data[i] == '"')
			data[i] = ' ';

	stringstream str(data);
	string getter = "";
	vector<string> collector;

	while (str >> getter)
		collector.push_back(getter);

	for(int i = 0; i < collector.size(); ++i)
		if (collector[i].compare("translate") == 0)
		{
			position.x = stof(collector[++i]);
			position.y = stof(collector[++i]);
		}
		else if (collector[i].compare("rotate") == 0)
		{
			rotation = stof(collector[++i]);

			if (i + 1 != collector.size())
			{
				bool isNum = true;
				for (int j = 0; j < collector[i + 1].length(); ++j)
					if (collector[i + 1][j] < '0' || collector[i + 1][j] > '9')
						isNum = false;

				if (isNum)
				{
					center.x = stof(collector[++i]);
					center.y = stof(collector[++i]);
				}
			}
		}
}

void Group::clear()
{
	polygon.clear();
	text.clear();
	ellipse.clear();
	circle.clear();
	polyline.clear();

	position.x = position.y = 0;
	center.x = center.y = 0;
	rotation = 0;
}

void Group::SetCenter()
{
	int count = 0;
	center = { 0, 0 };

	for (int i = 0; i < group.size(); ++i)
	{
		group[i].SetCenter();
		center.x += group[i].center.x;
		center.y += group[i].center.y;
		++count;
	}

	for (int i = 0; i < polygon.size(); ++i)
	{
		polygon[i].SetCenter();
		center.x += polygon[i].GetCenter().x;
		center.y += polygon[i].GetCenter().y;
		++count;
	}

	for (int i = 0; i < text.size(); ++i)
	{
		center.x += text[i].GetPosition().x;
		center.y += text[i].GetPosition().y;
		++count;
	}

	for (int i = 0; i < ellipse.size(); ++i)
	{
		ellipse[i].SetCenter();
		center.x += ellipse[i].GetCenter().x;
		center.y += ellipse[i].GetCenter().y;
		++count;
	}

	for (int i = 0; i < circle.size(); ++i)
	{
		center.x += circle[i].GetPosition().x;
		center.y += circle[i].GetPosition().y;
		++count;
	}

	for (int i = 0; i < polyline.size(); ++i)
	{
		polyline[i].SetCenter();
		center.x += polyline[i].GetCenter().x;
		center.y += polyline[i].GetCenter().y;
		++count;
	}

	center.x /= count;
	center.y /= count;
}

void Group::MovePosition()
{
	for (int i = 0; i < group.size(); ++i)
	{
		group[i].position.x += (position.x - group[i].position.x);
		group[i].position.y += (position.y - group[i].position.y);
		group[i].MovePosition();
	}

	for (int i = 0; i < polygon.size(); ++i)
	{
		vector<Point> pt = polygon[i].GetPosition();
		for (int j = 0; j < pt.size(); ++j)
		{
			pt[j].x += position.x;
			pt[j].y += position.y;
		}
		polygon[i].SetPosition(pt);
	}

	for (int i = 0; i < text.size(); ++i)
	{
		Point pt = text[i].GetPosition();
		pt.x += position.x;
		pt.y += position.y;
		text[i].SetPosition(pt);
	}

	for (int i = 0; i < ellipse.size(); ++i)
	{
		Point pt = ellipse[i].GetPosition();
		pt.x += position.x;
		pt.y += position.y;
		ellipse[i].SetPosition(pt);
	}

	for (int i = 0; i < circle.size(); ++i)
	{
		Point pt = circle[i].GetPosition();
		pt.x += position.x;
		pt.y += position.y;
		circle[i].SetPosition(pt);
	}

	for (int i = 0; i < polyline.size(); ++i)
	{
		vector<Point> pt = polyline[i].GetPosition();
		for (int j = 0; j < pt.size(); ++j)
		{
			pt[j].x += position.x;
			pt[j].y += position.y;
		}
		polyline[i].SetPosition(pt);
	}
}

void Group::Rotate()
{
	SetCenter();

	for (int i = 0; i < group.size(); ++i)
	{
		//group[i].position = MovePoint(group[i].position, rotation, center);
		group[i].rotation += rotation;
		//group[i].MovePosition();
	}

	for (int i = 0; i < polygon.size(); ++i)
	{
		//vector<Point> pt = polygon[i].GetPosition();
		//for (int j = 0; j < pt.size(); ++j)
		//	pt[i] = MovePoint(pt[i], rotation, center);

		polygon[i].SetAngle(polygon[i].GetAngle() + rotation);
		//polygon[i].SetPosition(pt);
	}

	for (int i = 0; i < text.size(); ++i)
	{
		//Point pt = MovePoint(text[i].GetPosition(), rotation, center);

		text[i].SetAngle(text[i].GetAngle() + rotation);
		//text[i].SetPosition(pt);
	}

	for (int i = 0; i < ellipse.size(); ++i)
	{
		//Point pt = MovePoint(ellipse[i].GetPosition(), rotation, center);

		ellipse[i].SetAngle(ellipse[i].GetAngle() + rotation);
		//ellipse[i].SetPosition(pt);
	}

	for (int i = 0; i < circle.size(); ++i)
	{
		//Point pt = MovePoint(circle[i].GetPosition(), rotation, center);

		circle[i].SetAngle(circle[i].GetAngle() + rotation);
		//circle[i].SetPosition(pt);
	}

	for (int i = 0; i < polyline.size(); ++i)
	{
		//vector<Point> pt = polyline[i].GetPosition();
		//for (int j = 0; j < pt.size(); ++j)
			//pt[i] = MovePoint(pt[i], rotation, center);

		polyline[i].SetAngle(polyline[i].GetAngle() + rotation);
		//polyline[i].SetPosition(pt);
	}
}

void Group::setGroup(Group group) {
	this->group.push_back(group);
}

void Group::setPolygon(vector<Polygon> polygon) {
	this->polygon = polygon;
}

void Group::setWord(vector<Word> word) {
	this->text = word;
}

void Group::setEllipse(vector<Ellipse> ellipse) {
	this->ellipse = ellipse;
}

void Group::setCircle(vector<Circle> circle) {
	this->circle = circle;
}

void Group::setPolyline(vector<Polyline> polyline) {
	this->polyline = polyline;
}

void Group::setShapeId(vector<int> shapeId) {
	this->shapeID = shapeId;
}

vector<Group> Group::GetGroup()
{
	return this->group;
}

vector<Polygon> Group::GetPolygon()
{
	return this->polygon;
}

vector<Word> Group::GetText()
{
	return this->text;
}

vector<Ellipse> Group::GetEllipse()
{
	return this->ellipse;
}

vector<Circle> Group::GetCircle()
{
	return this->circle;
}

vector<Polyline> Group::GetPolyline()
{
	return this->polyline;
}
