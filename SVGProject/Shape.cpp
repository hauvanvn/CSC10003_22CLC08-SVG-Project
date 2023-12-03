#include "Shape.h"
#include <math.h>
////////////////////////////// Figure \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void Figure::SetColor(RGBA color)
{
	this->color = color;
}

void Figure::SetStrokeWidth(float width)
{
	this->stroke_width = width;
}

void Figure::SetStrokeColor(RGBA color)
{
	this->stroke_color = color;
}

void Figure::SetAngle(float angle)
{
	this->rotation = angle;
}

RGBA Figure::GetColor()
{
	return this->color;
}

float Figure::GetStrokeWidth()
{
	return this->stroke_width;
}

RGBA Figure::GetStrokeColor()
{
	return this->stroke_color;
}

Point Figure::GetCenter()
{
	return this->center;
}

float Figure::GetAngle()
{
	return this->rotation;
}

///////////////////////// Drawer \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::processData(vector<string> data)
{
	Polygon tempP;
	Word tempW;
	Ellipse tempE;
	Circle tempC;
	Polyline tempPL;

	if (data[0].compare("rect") == 0 || data[0].compare("polygon") == 0)
	{
		tempP.SetElement(data);
		polygon.push_back(tempP);

		shapeID.push_back(0);
		tempP.clear(); //Reseting this element to avoid compressing one shape to another
	}
	else if (data[0].compare("text") == 0)
	{
		tempW.SetElement(data);
		text.push_back(tempW);

		shapeID.push_back(1);
		tempW.clear(); 
	}
	else if (data[0].compare("ellipse") == 0)
	{
		tempE.SetElement(data);
		ellpise.push_back(tempE);

		shapeID.push_back(2);
		tempE.clear(); 
	}
	else if (data[0].compare("circle") == 0)
	{
		tempC.SetElement(data);
		tempC.SetRadius(data);
		circle.push_back(tempC);

		shapeID.push_back(3);
		tempC.clear();
		tempC.clearRadius(); //Since clear in Elipse dont have radius, this is extra method for the reason
	}
	else
	{
		tempPL.SetElement(data);
		polyline.push_back(tempPL);

		shapeID.push_back(4);
		tempPL.clear();
	}
}

Group Drawer::readGroup(istream& file, vector<string> data)
{
	Group result;
	Group tempG;
	result.SetElement(data);

	string s, getter;
	vector<string> collector;
	Drawer drawer;

	while (true)
	{
		getline(file, s);
		size_t foundEnd = s.find("</g>");
		if (foundEnd != string::npos)
			break;

		size_t foundPath = s.find("path"); //We skip reading path since we have not been able to render it
		if (foundPath != string::npos)
		{
			size_t foundEndOfPath = s.find(">");
			if (foundEndOfPath == string::npos)
			{
				getline(file, s, '>');
				getline(file, s);
			}
			continue;
		}

		for (int i = 0; i < s.length(); ++i)
			if (s[i] == ',' || s[i] == '<' || s[i] == '>' || s[i] == '/' || s[i] == '=' || s[i] == '(' || s[i] == ')')
				s[i] = ' ';
		stringstream str(s);
		while (str >> getter)
			collector.push_back(getter);

		if (collector[0].compare("g") == 0)
		{
			tempG = readGroup(file, collector);
			result.setGroup(tempG);
			tempG.clear();
		}
		else
			drawer.processData(collector);
		collector.clear();
	}

	result.setPolygon(drawer.polygon);
	result.setWord(drawer.text);
	result.setEllipse(drawer.ellpise);
	result.setCircle(drawer.circle);
	result.setPolyline(drawer.polyline);
	result.setShapeId(drawer.shapeID);

	return result;
}

void Drawer::readData(string filename)
{
	ifstream file(filename);

	string s = "";
	getline(file, s); //Skip the first 2 lines
	getline(file, s);

	Group tempG;

	Drawer* processedData = nullptr;
	string getter = "";
	vector<string> collector;
	while (!file.eof())
	{
		getline(file, s);
		if (s.compare("</svg>") == 0)
			break;

		size_t foundPath = s.find("path");//We skip reading path since we have not been able to render it
		if (foundPath != string::npos)
		{
			size_t foundEndOfPath = s.find(">");
			if (foundEndOfPath == string::npos)
			{
				getline(file, s, '>');
				getline(file, s);
			}
			continue;
		}

		for (int i = 0; i < s.length(); ++i)
			if (s[i] == ',' || s[i] == '<' || s[i] == '>' || s[i] == '/' || s[i] == '=' || s[i] == '(' || s[i] == ')')
				s[i] = ' ';
		stringstream str(s);
		while (str >> getter)
			collector.push_back(getter);

		if (collector[0].compare("g") == 0)
		{
			tempG = readGroup(file, collector);
			group.push_back(tempG);
			shapeID.push_back(5);
			tempG.clear();
		}
		else	processData(collector);
		collector.clear();
	}
}

//void Drawer::Draw(RenderWindow& window)
//{
//	vector<int> index(6, 0);
//
//	for (int i : shapeID)
//	{
//		switch (i)
//		{
//		case 0:
//			DrawPolygon(window, polygon[index[i]++]);
//			break;
//
//		case 1:
//			DrawWord(window, text[index[i]++]);
//			break;
//
//		case 2:
//			DrawEllipse(window, ellpise[index[i]++]);
//			break;
//
//		case 3:
//			DrawCircle(window, circle[index[i]++]);
//			break;
//
//		case 4:
//			DrawPolyline(window, polyline[index[i]++]);
//			break;
//
//		case 5:
//			DrawGroup(window, group[index[i]++]);
//			break;
//
//		default:
//			break;
//		}
//	}
//}
//
//void Drawer::DrawPolygon(RenderWindow& window, Polygon shape)
//{
//	ConvexShape polygon;
//
//	vector<Point> pt = shape.GetPosition();
//	RGBA color = shape.GetColor();
//	float stroke_width = shape.GetStrokeWidth();
//	RGBA stroke_color = shape.GetStrokeColor();
//
//	polygon.setPointCount(pt.size()); 	//Setting points
//	for (int i = 0; i < pt.size(); ++i)
//		polygon.setPoint(i, Vector2f(pt[i].x, pt[i].y));
//
//	if (color.R != -1) 	//Setting fill-color
//		if (color.A != -1) polygon.setFillColor(Color(color.R, color.G, color.B, color.A));
//		else polygon.setFillColor(Color(color.R, color.G, color.B));
//
//	if (stroke_width != -1) //Setting stroke width & color
//		polygon.setOutlineThickness(stroke_width);
//	if (stroke_color.R != -1)
//		if (stroke_color.A != -1) polygon.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
//		else polygon.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));
//
//	polygon.setRotation(shape.GetAngle());
//
//	window.draw(polygon);
//}
//
//void Drawer::DrawWord(RenderWindow& window, Word shape)
//{
//	Font font;
//	font.loadFromFile(shape.GetFont());
//
//	Text text;
//	text.setFont(font);
//	text.setString(shape.GetText());
//	text.setCharacterSize(shape.GetSize());
//
//	RGBA color = shape.GetColor();
//	Point position = shape.GetPosition();
//	if (color.R != -1)
//		if (color.A != -1) text.setFillColor(Color(color.R, color.G, color.B, color.A));
//		else text.setFillColor(Color(color.R, color.G, color.B));
//	text.setPosition(Vector2f(position.x, position.y - shape.GetSize()));
//
//	text.setRotation(shape.GetAngle());
//
//	window.draw(text);
//}
//
//void Drawer::DrawEllipse(RenderWindow& window, Ellipse shape)
//{
//	float radius_x = shape.GetMradius().x;
//	float radius_y = shape.GetMradius().y;
//	unsigned short pointNum = 72; /*72 is the golden distribution of points to form ellipse*/
//	const double PI = atan(1) * 4;
//
//	ConvexShape ellipse;
//	ellipse.setPointCount(pointNum);
//
//	for (unsigned short i = 0; i < pointNum; ++i)
//	{
//		float radian = (360 / pointNum * i) / (360 / PI / 2);
//		float x = cos(radian) * radius_x;
//		float y = sin(radian) * radius_y;
//
//		ellipse.setPoint(i, sf::Vector2f(x, y));
//
//		RGBA color = shape.GetColor();
//		float stroke_width = shape.GetStrokeWidth();
//		RGBA stroke_color = shape.GetStrokeColor();
//		if (color.R != -1)
//			if (color.A != -1) ellipse.setFillColor(Color(color.R, color.G, color.B, color.A));
//			else ellipse.setFillColor(Color(color.R, color.G, color.B));
//
//		if (stroke_width != -1)
//			ellipse.setOutlineThickness(stroke_width);
//		if (stroke_color.R != -1)
//			if (stroke_color.A != -1) ellipse.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
//			else ellipse.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));
//	}
//
//	ellipse.setPosition(shape.GetPosition().x, shape.GetPosition().y);
//	//ellipse.setRotation(shape.GetAngle());
//	ellipse.setRotation(45);
//	window.draw(ellipse);
//}
//
//void Drawer::DrawCircle(RenderWindow& window, Circle shape)
//{
//	CircleShape circle;
//
//	circle.setPosition(Vector2f(shape.GetPosition().x - shape.GetRadius(), shape.GetPosition().y - shape.GetRadius()));
//	circle.setRadius(shape.GetRadius());
//
//	RGBA color = shape.GetColor();
//	float stroke_width = shape.GetStrokeWidth();
//	RGBA stroke_color = shape.GetStrokeColor();
//
//	if (color.R != -1)
//		if (color.A != -1) circle.setFillColor(Color(color.R, color.G, color.B, color.A));
//		else circle.setFillColor(Color(color.R, color.G, color.B));
//
//	if (stroke_width != -1) circle.setOutlineThickness(stroke_width);
//	if (stroke_color.R != -1)
//		if (stroke_color.A != -1) circle.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
//		else circle.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));
//	
//	circle.setRotation(shape.GetAngle());
//	window.draw(circle);
//}
//
//void Drawer::DrawLine(RenderWindow& window, Polyline shape, Point p1, Point p2)
//{
//	float length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
//	float posX = p1.x, posY = p1.y;
//	float rotation = 0;
//	float stroke_width = shape.GetStrokeWidth();
//
//	if (p1.x == p2.x && p1.y < p2.y) //rotate 90 degree anticlockwise
//	{
//		rotation = -90;
//		posY += stroke_width;
//	}
//	else if (p1.x == p2.x && p1.y > p2.y) //rotate 90 degree clockwise
//	{
//		rotation = 90;
//		posY += stroke_width;
//	}
//	else
//	{
//		rotation = (pow(length, 2) + pow(p1.x - p2.x, 2) - pow(p1.y - p2.y, 2)) / (2 * length * abs(p1.x - p2.x));
//		rotation = acos(rotation) * 180 / 3.141592; //go from radian to degree
//
//		if (p2.x < p1.x) // for angel > 90 and < -90
//			if (p2.y > p1.y)	rotation = 180 - rotation; // > 90
//			else				rotation = rotation - 180; // < -90
//	}
//
//
//	RectangleShape lines(Vector2f(length, stroke_width));
//	lines.rotate(-1 * rotation); // multiply by -1 since rotate method rotate shape clockwise.
//	lines.setPosition(Vector2f(posX, posY));
//	RGBA stroke_color = shape.GetStrokeColor();
//	if (stroke_color.R != -1)
//		if (stroke_color.A != -1) lines.setFillColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
//		else lines.setFillColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));
//
//	lines.setRotation(shape.GetAngle());
//
//	window.draw(lines);
//}
//
//void Drawer::DrawPolyline(RenderWindow& window, Polyline shape)
//{
//	vector<Point> points = shape.GetPosition();
//	if (points.size() <= 2)
//	{
//		DrawLine(window, shape, points[0], points[1]);
//		return;
//	}
//
//	ConvexShape polyline;
//	RGBA color = shape.GetColor();
//	if (color.R != -1)
//		if (color.A != -1) polyline.setFillColor(Color(color.R, color.G, color.B, color.A));
//		else polyline.setFillColor(Color(color.R, color.G, color.B));
//
//	vector<Point> pt;
//	for (int i = 0; i < points.size() - 1; ++i)
//	{
//		Point iPoint = FindIntersectionPoint(points[0], points.back(), points[i], points[i + 1]);
//		if (iPoint.x != -1)
//			if (pt.size() == 0) pt.push_back(iPoint);
//			else
//			{
//				pt.push_back(points[i]);
//				pt.push_back(iPoint);
//				polyline.setPointCount(pt.size());
//				for (int j = 0; j < pt.size(); ++j) polyline.setPoint(j, Vector2f(pt[j].x, pt[j].y));
//				window.draw(polyline);
//
//				pt.clear();
//				pt.push_back(iPoint);
//			}
//		else pt.push_back(points[i]);
//	}
//
//	for (int i = 0; i < points.size() - 1; ++i) DrawLine(window, shape, points[i], points[i + 1]);
//}
//
//void Drawer::DrawGroup(RenderWindow& window, Group shape)
//{
//	shape.MovePosition();
//	//shape.Rotate();
//	vector<Group> group = shape.GetGroup();
//	vector<Polygon> polygon = shape.GetPolygon();
//	vector<Word> text = shape.GetText();
//	vector<Ellipse> ellipse = shape.GetEllipse();
//	vector<Circle> circle = shape.GetCircle();
//	vector<Polyline> polyline = shape.GetPolyline();
//
//	for (int i = 0; i < group.size(); ++i)
//		DrawGroup(window, group[i]);
//
//	for (int i = 0; i < polygon.size(); ++i)
//		DrawPolygon(window, polygon[i]);
//
//	for (int i = 0; i < text.size(); ++i)
//		DrawWord(window, text[i]);
//
//	for (int i = 0; i < ellipse.size(); ++i)
//		DrawEllipse(window, ellipse[i]);
//
//	for (int i = 0; i < circle.size(); ++i)
//		DrawCircle(window, circle[i]);
//
//	for (int i = 0; i < polyline.size(); ++i)
//		DrawPolyline(window, polyline[i]);
//}

Point FindIntersectionPoint(Point A, Point B, Point C, Point D)
{
	float a1 = B.y - A.y;
	float b1 = A.x - B.x;
	float c1 = a1 * A.x + b1 * A.y;

	float a2 = D.y - C.y;
	float b2 = C.x - D.x;
	float c2 = a2 * C.x + b2 * C.y;


	float determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)	
	{
		return {-1, -1};
	}
	else
	{
		float x = (b2 * c1 - b1 * c2) / determinant;
		float y = (a1 * c2 - a2 * c1) / determinant;
		{
			return { x, y };
		}
	}
}

Point MovePoint(Point x, float rotation, Point center)
{
	Point res;

	//res.x = (x.x - center.x) * cos(rotation) - (x.y - center.y) * sin(rotation) + center.x;
	//res.y = (x.x - center.x) * sin(rotation) + (x.y - center.y) * cos(rotation) + center.y;
	res.x = x.x * cos(rotation) - x.y * sin(rotation);
	res.y = x.x * sin(rotation) + x.y * cos(rotation);

	return res;
}
