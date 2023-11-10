#include "Shape.h"

///////////////////////////// Polygon \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
}

void Polygon::SetElement()
{
	point.push_back({ 350, 75 });
	point.push_back({ 379, 161 });
	point.push_back({ 469, 161 });
	point.push_back({ 397, 215 });
	point.push_back({ 423, 301 });
	point.push_back({ 350, 250 });
	point.push_back({ 277, 301 });
	point.push_back({ 303, 215 });
	point.push_back({ 231, 161 });
	point.push_back({ 321, 161 });

	color = { 255, 255, 0, 255 * 0.6 };
	stroke_width = 10;
	stroke_color = { 255, 0, 0, 255 * 0.7 };
}

void Polygon::Draw(RenderWindow& window)
{
	ConvexShape polygon;

	polygon.setPointCount(point.size());
	for (int i = 0; i < point.size(); ++i)
		polygon.setPoint(i, Vector2f(point[i].x, point[i].y));
	if (color.R != -1)
		if (color.A != -1) polygon.setFillColor(Color(color.R, color.G, color.B, color.A));
		else polygon.setFillColor(Color(color.R, color.G, color.B));
	if (stroke_width != -1)
		polygon.setOutlineThickness(stroke_width);
	if (stroke_color.R != -1)
		if (stroke_color.A != -1) polygon.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
		else polygon.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));

	window.draw(polygon);
}

//////////////////////////////// Text \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Word::Word()
{
}

Word::~Word()
{
}

void Word::SetElement()
{
	font = "times new roman.ttf";
	text = "Nguyen Van A";
	size = 30;
	color = { 255, 0, 255, -1 };
	position = { 400, 400 };
}

void Word::Draw(RenderWindow& window)
{
	Font font;
	font.loadFromFile(this->font);

	Text text;
	text.setFont(font);
	text.setString(this->text);
	text.setCharacterSize(size);
	if (color.R != -1)
		if (color.A != -1) text.setFillColor(Color(color.R, color.G, color.B, color.A));
		else text.setFillColor(Color(color.R, color.G, color.B));
	text.setPosition(Vector2f(position.x, position.y));

	window.draw(text);
}

///////////////////////////////////////// Ellipse \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Ellipse::Ellipse()
{
}

Ellipse::~Ellipse()
{
}

void Ellipse::SetPosition(Point position)
{
	this->position = position;
}

void Ellipse::SetRadius(Point m_radius)
{
	this->m_radius = m_radius;
}

void Ellipse::SetColor(RGBA color)
{
	this->color = color;
}

void Ellipse::SetStroke(float width, RGBA color)
{
	stroke_width = width;
	stroke_color = color;
}

void Ellipse::Draw(RenderWindow& window)
{
	
}

///////////////////////////////////////// Circle \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Circle::Circle()
{
}

Circle::~Circle()
{
}

void Circle::SetRadius(float radius)
{
	this->radius = radius;
}

void Circle::Draw(RenderWindow& window)
{
	CircleShape circle;

	circle.setPosition(Vector2f(position.x, position.y));
	circle.setRadius(radius);
	if (color.R != -1)
		if (color.A != -1) circle.setFillColor(Color(color.R, color.G, color.B, color.A));
		else circle.setFillColor(Color(color.R, color.G, color.B));
	if (stroke_width != -1) circle.setOutlineThickness(stroke_width);
	if (stroke_color.R != -1)
		if (stroke_color.A != -1) circle.setFillColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
		else circle.setFillColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));

	window.draw(circle);
}