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

///////////////////////////// Polygon \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Polygon::Polygon()
{
	type = "";
	stroke_width = height = width = -1;
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B;
	color.A = stroke_color.A = -1;
}

Polygon::~Polygon()
{
}

void Polygon::SetElement(vector<string> s) { //read vector from: void read(paramater)
	type = s[0];

	for (int i = 1; i < s.size(); ++i)
	{
		int gap = 0;
		if (s[i + 1][s[i + 1].length() - 1] != '"') //reconnecting elements that were previously dislocate when using stringstream
			for (int j = i + 2; s[j - 1].back() != '"'; ++j)
			{
				s[i + 1] = s[i + 1] + " " + s[j];
				gap++;
			}

		for (int j = 0; j < s[i + 1].length(); ++j) //removing " to for stof
			if (s[i + 1][j] == '"')
				s[i + 1][j] = ' ';

		if (s[i].compare("fill-opacity") == 0)
			color.A = stof(s[++i]) * 255;

		else if (s[i].compare("stroke-opacity") == 0)
			stroke_color.A = stof(s[++i]) * 255;
		else if (s[i].compare("stroke-width") == 0)
			stroke_width = stof(s[++i]);

		else if (s[i].compare("height") == 0)
			height = stof(s[++i]);
		else if (s[i].compare("width") == 0)
			width = stof(s[++i]);

		else if (s[i].compare("stroke") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			stroke_color.R = stof(temp);

			str >> temp;
			stroke_color.G = stof(temp);

			str >> temp;
			stroke_color.B = stof(temp);
		}
		else if (s[i].compare("fill") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			color.R = stof(temp);

			str >> temp;
			color.G = stof(temp);

			str >> temp;
			color.B = stof(temp);
		}

		else if (s[i].compare("x") == 0 || s[i].compare("y") == 0)
		{
			if (point.size() != 1)
			{
				Point temp;
				if (s[i].compare("x") == 0)		temp.x = stof(s[++i]);
				else	temp.y = stof(s[++i]);
				point.push_back(temp);
			}
			else
			{
				if (s[i].compare("x") == 0)		point[0].x = stof(s[++i]);
				else	point[0].y = stof(s[++i]);
			}
		}
		else if (s[i].compare("points") == 0)
		{
			i++;
			stringstream str(s[i]);
			string temp1;

			for (int j = 0; str >> temp1; ++j)
			{
				if (j % 2 == 0)
				{
					Point temp2;
					temp2.x = stof(temp1);
					point.push_back(temp2);
				}
				else	point[j / 2].y = stof(temp1);
			}
		}

		i += gap; //update index if there was a reconecting action
	}

	if (point.size() == 1)
	{
		point.push_back({ point[0].x, point[0].y + height });
		point.push_back({ point[0].x + width, point[0].y + height });
		point.push_back({ point[0].x + width, point[0].y });
	}
}

void Polygon::clear() { //use to reset a Polygon object
	type = "";
	stroke_width = height = width = -1;
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B;
	color.A = stroke_color.A = -1;

	point.clear();
}

void Polygon::SetPosition(Point pt)
{
	for (int i = 0; i < point.size(); ++i)
	{
		point[i].x += pt.x;
		point[i].y += pt.y;
	}
}

vector<Point> Polygon::GetPosition()
{
	return this->point;
}

//////////////////////////////// Text \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Word::Word()
{
}

Word::~Word()
{
}

void Word::SetElement(vector<string> s) {
	font = "times new roman.ttf";

	int gap = 0;
	text += s[s.size() - 2];
	for (int i = s.size() - 3; i >= 0; --i)
		if (s[i][s[i].length() - 1] == '"')	break;
		else
		{
			text = s[i] + " " + text;
			gap++;
		}

	int length = s.size() - 2 - gap;
	for (int i = 1; i < length; ++i)
	{
		gap = 0;
		if (s[i + 1][s[i + 1].length() - 1] != '"') //reconnecting elements that were previously dislocate when using stringstream
			for (int j = i + 2; s[j - 1].back() != '"'; ++j)
			{
				s[i + 1] = s[i + 1] + " " + s[j];
				gap++;
			}

		for (int j = 0; j < s[i + 1].length(); ++j) //removing " to for stof
			if (s[i + 1][j] == '"')
				s[i + 1][j] = ' ';

		if (s[i].compare("font-size") == 0)
			size = stof(s[++i]);
		else if (s[i].compare("x") == 0)
			position.x = stof(s[++i]);
		else if (s[i].compare("y") == 0)
			position.y = stof(s[++i]);
		else if (s[i].compare("fill") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			color.R = stof(temp);

			str >> temp;
			color.G = stof(temp);

			str >> temp;
			color.B = stof(temp);
		}

		i += gap;
	}
}

void Word::clear() {
	font = text = "";
	size = 0;
	position.x = position.y = 0;
	color.R = color.G = color.B = 0;
}

void Word::SetFont(string font)
{
	this->font = font;
}

void Word::SetText(string text)
{
	this->text = text;
}

void Word::SetSize(float size)
{
	this->size = size;
}

void Word::SetPosition(Point position)
{
	this->position = position;
}

string Word::GetFont()
{
	return this->font;
}

string Word::GetText()
{
	return this->text;
}

float Word::GetSize()
{
	return this->size;
}

Point Word::GetPosition()
{
	return this->position;
}

///////////////////////////////////////// Ellipse \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Ellipse::Ellipse()
{
	stroke_width = -1;
	position.x = position.y = 0;
	m_radius.x = m_radius.y = 0;
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
}

Ellipse::~Ellipse()
{
}

void Ellipse::SetElement(vector<string> s) {
	for (int i = 1; i < s.size(); ++i)
	{
		int gap = 0;
		if (s[i + 1][s[i + 1].length() - 1] != '"') //reconnecting elements that were previously dislocate when using stringstream
			for (int j = i + 2; s[j - 1].back() != '"'; ++j)
			{
				s[i + 1] = s[i + 1] + " " + s[j];
				gap++;
			}

		for (int j = 0; j < s[i + 1].length(); ++j) //removing " to for stof
			if (s[i + 1][j] == '"')
				s[i + 1][j] = ' ';

		if (s[i].compare("fill-opacity") == 0)
			color.A = stof(s[++i]) * 255;

		else if (s[i].compare("stroke-opacity") == 0)
			stroke_color.A = stof(s[++i]) * 255;
		else if (s[i].compare("stroke-width") == 0)
			stroke_width = stof(s[++i]);

		else if (s[i].compare("cx") == 0)
			position.x = stof(s[++i]);
		else if (s[i].compare("cy") == 0)
			position.y = stof(s[++i]);
		else if (s[i].compare("rx") == 0)
			m_radius.x = stof(s[++i]);
		else if (s[i].compare("ry") == 0)
			m_radius.y = stof(s[++i]);
		else if (s[i].compare("r") == 0)
			i++;									//Since this will be used to read for Circle, we will skip radius element

		else if (s[i].compare("stroke") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			stroke_color.R = stof(temp);

			str >> temp;
			stroke_color.G = stof(temp);

			str >> temp;
			stroke_color.B = stof(temp);
		}
		else if (s[i].compare("fill") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			color.R = stof(temp);

			str >> temp;
			color.G = stof(temp);

			str >> temp;
			color.B = stof(temp);
		}

		i += gap; //update index if there was a reconecting action
	}
}

void Ellipse::clear() {
	stroke_width = -1;
	position.x = position.y = 0;
	m_radius.x = m_radius.y = 0;
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
}

void Ellipse::SetPoisition(Point position)
{
	this->position = position;
}

void Ellipse::SetMradius(Point m_radius)
{
	this->m_radius = m_radius;
}

Point Ellipse::GetPosition()
{
	return this->position;
}

Point Ellipse::GetMradius()
{
	return this->m_radius;
}

///////////////////////////////////////// Circle \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Circle::Circle()
{
}

Circle::~Circle()
{
}

void Circle::SetRadius(vector<string> s) {
	for (int i = 0; i < s.size(); ++i)
		if (s[i].compare("r") == 0)
		{
			for (int j = 0; j < s[i + 1].length(); ++j)
				if ((s[i + 1][j] < '0' || s[i + 1][j] > '9') && s[i + 1][j] != '.')
					s[i + 1][j] = ' ';
			radius = stof(s[i + 1]);
			break;
		}
}

void Circle::clearRadius()
{
	radius = 0;
}

void Circle::SetRadius(float radius)
{
	this->radius = radius;
}

float Circle::GetRadius()
{
	return this->radius;
}

////////////////////////// Polyline \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Polyline::Polyline()
{
	stroke_width = -1;
	points.clear();
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
}

Polyline::~Polyline()
{
}

void Polyline::SetElement(vector<string> s) {
	for (int i = 1; i < s.size(); ++i)
	{
		int gap = 0;
		if (s[i + 1][s[i + 1].length() - 1] != '"') //reconnecting elements that were previously dislocate when using stringstream
			for (int j = i + 2; s[j - 1].back() != '"'; ++j)
			{
				s[i + 1] = s[i + 1] + " " + s[j];
				gap++;
			}

		for (int j = 0; j < s[i + 1].length(); ++j) //removing " to for stof
			if (s[i + 1][j] == '"')
				s[i + 1][j] = ' ';

		if (s[i].compare("fill-opacity") == 0)
			color.A = stof(s[++i]) * 255;

		else if (s[i].compare("stroke-opacity") == 0)
			stroke_color.A = stof(s[++i]) * 255;
		else if (s[i].compare("stroke-width") == 0)
			stroke_width = stof(s[++i]);

		else if (s[i].compare("stroke") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			stroke_color.R = stof(temp);

			str >> temp;
			stroke_color.G = stof(temp);

			str >> temp;
			stroke_color.B = stof(temp);
		}
		else if (s[i].compare("fill") == 0)
		{
			i++;
			for (int j = 0; j < s[i].length(); ++j)
				if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.')
					s[i][j] = ' ';

			stringstream str(s[i]);
			string temp;

			str >> temp;
			color.R = stof(temp);

			str >> temp;
			color.G = stof(temp);

			str >> temp;
			color.B = stof(temp);
		}
		else if (s[i].compare("x1") == 0 || s[i].compare("y1") == 0 || s[i].compare("x2") == 0 || s[i].compare("y2") == 0) //this is for line
		{
			if (points.size() != 2)
			{
				if (points.size() != 1)
				{
					Point temp;
					if (s[i][0] == 'x')		temp.x = stof(s[++i]);
					else	temp.y = stof(s[++i]);

					points.push_back(temp);
				}
				else
				{
					if (s[i][0] == 'x')		points[0].x = stof(s[++i]);
					else	points[0].y = stof(s[++i]);

					Point temp;
					points.push_back(temp);
				}
			}
			else
			{
				if (s[i][0] == 'x')		points[1].x = stof(s[++i]);
				else	points[1].y = stof(s[++i]);
			}
		}
		else if (s[i].compare("points") == 0)
		{
			i++;
			stringstream str(s[i]);
			string temp1;

			for (int j = 0; str >> temp1; ++j)
			{
				if (j % 2 == 0)
				{
					Point temp2;
					temp2.x = stof(temp1);
					points.push_back(temp2);
				}
				else	points[j / 2].y = stof(temp1);
			}
		}


		i += gap; //update index if there was a reconecting action
	}
}

void Polyline::clear() {
	stroke_width = -1;
	points.clear();
	stroke_color.R = stroke_color.G = stroke_color.B = 0; 
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
}

void Polyline::SetPosition(Point pt)
{
	for (int i = 0; i < points.size(); ++i)
	{
		points[i].x += pt.x;
		points[i].y += pt.y;
	}
}

vector<Point> Polyline::GetPosition()
{
	return points;
}

///////////////////////// Group \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Group::Group()
{
}

Group::~Group()
{
}

void Group::SetElement(vector<string> s)
{
}

void Group::clear()
{
}

///////////////////////// Drawer \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::read(string filename)
{
	ifstream file(filename);

	string s;
	getline(file, s);	//Skip the first two line
	getline(file, s);

	Polygon tempP;
	Word tempW;
	Ellipse tempE;
	Circle tempC;
	Polyline tempPL;

	vector<string> collector;
	string getter = "";
	while (!file.eof())	//start to read svg file
	{
		getline(file, s);
		if (s.compare("</svg>") == 0)
			break;
		for (int i = 0; i < s.length(); ++i)
			if (s[i] == '<' || s[i] == '>' || s[i] == '/' || s[i] == '=' || s[i] == ',') //remove char to create space for stringstream
				s[i] = ' ';

		stringstream str(s);
		while (str >> getter)
			collector.push_back(getter);

		if (collector[0].compare("rect") == 0 || collector[0].compare("polygon") == 0)
		{
			tempP.SetElement(collector);
			polygon.push_back(tempP);

			shapeID.push_back(0);
			tempP.clear(); //Reseting this element to avoid compressing one shape to another
		}
		else if (collector[0].compare("text") == 0)
		{
			tempW.SetElement(collector);
			text.push_back(tempW);

			shapeID.push_back(1);
			tempW.clear(); //Same resone as line 524
		}
		else if (collector[0].compare("ellipse") == 0)
		{
			tempE.SetElement(collector);
			ellpise.push_back(tempE);

			shapeID.push_back(2);
			tempE.clear(); //Same resone as line 524
		}
		else if (collector[0].compare("circle") == 0)
		{
			tempC.SetElement(collector);
			tempC.SetRadius(collector);
			circle.push_back(tempC);

			shapeID.push_back(3);
			tempC.clear(); //Same resone as line 524
			tempC.clearRadius(); //Since clear in Elipse dont have radius, this is extra method for the reason
		}
		else
		{
			tempPL.SetElement(collector);
			polyline.push_back(tempPL);

			shapeID.push_back(4);
			tempPL.clear(); //Same resone as line 524
		}

		collector.clear();
	}

	file.close();
}

void Drawer::Draw(RenderWindow& window)
{
	vector<int> index(5, 0);

	for (int i : shapeID)
	{
		switch (i)
		{
		case 0:
			DrawPolygon(window, polygon[index[i]++]);
			break;
			
		case 1:
			DrawWord(window, text[index[i]++]);
			break;

		case 2:
			DrawEllipse(window, ellpise[index[i]++]);
			break;

		case 3:
			DrawCircle(window, circle[index[i]++]);
			break;

		case 4:
			DrawPolyline(window, polyline[index[i]++]);
			break;

		default:
			break;
		}
	}
}

void Drawer::DrawPolygon(RenderWindow& window, Polygon shape)
{
	ConvexShape polygon;

	vector<Point> pt = shape.GetPosition();
	RGBA color = shape.GetColor();
	float stroke_width = shape.GetStrokeWidth();
	RGBA stroke_color = shape.GetStrokeColor();

	polygon.setPointCount(pt.size()); 	//Setting points
	for (int i = 0; i < pt.size(); ++i)
		polygon.setPoint(i, Vector2f(pt[i].x, pt[i].y));

	if (color.R != -1) 	//Setting fill-color
		if (color.A != -1) polygon.setFillColor(Color(color.R, color.G, color.B, color.A));
		else polygon.setFillColor(Color(color.R, color.G, color.B));

	if (stroke_width != -1) //Setting stroke width & color
		polygon.setOutlineThickness(stroke_width);
	if (stroke_color.R != -1)
		if (stroke_color.A != -1) polygon.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
		else polygon.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));

	window.draw(polygon);
}

void Drawer::DrawWord(RenderWindow& window, Word shape)
{
	Font font;
	font.loadFromFile(shape.GetFont());

	Text text;
	text.setFont(font);
	text.setString(shape.GetText());
	text.setCharacterSize(shape.GetSize());

	RGBA color = shape.GetColor();
	Point position = shape.GetPosition();
	if (color.R != -1)
		if (color.A != -1) text.setFillColor(Color(color.R, color.G, color.B, color.A));
		else text.setFillColor(Color(color.R, color.G, color.B));
	text.setPosition(Vector2f(position.x, position.y - shape.GetSize()));

	window.draw(text);
}

void Drawer::DrawEllipse(RenderWindow& window, Ellipse shape)
{
	float radius_x = shape.GetMradius().x;
	float radius_y = shape.GetMradius().y;
	unsigned short pointNum = 72; /*72 is the golden distribution of points to form ellipse*/
	const double PI = atan(1) * 4;

	ConvexShape ellipse;
	ellipse.setPointCount(pointNum);

	for (unsigned short i = 0; i < pointNum; ++i)
	{
		float radian = (360 / pointNum * i) / (360 / PI / 2);
		float x = cos(radian) * radius_x;
		float y = sin(radian) * radius_y;

		ellipse.setPoint(i, sf::Vector2f(x, y));

		RGBA color = shape.GetColor();
		float stroke_width = shape.GetStrokeWidth();
		RGBA stroke_color = shape.GetStrokeColor();
		if (color.R != -1)
			if (color.A != -1) ellipse.setFillColor(Color(color.R, color.G, color.B, color.A));
			else ellipse.setFillColor(Color(color.R, color.G, color.B));

		if (stroke_width != -1)
			ellipse.setOutlineThickness(stroke_width);
		if (stroke_color.R != -1)
			if (stroke_color.A != -1) ellipse.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
			else ellipse.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));
	}

	ellipse.setPosition(shape.GetPosition().x, shape.GetPosition().y);
	window.draw(ellipse);
}

void Drawer::DrawCircle(RenderWindow& window, Circle shape)
{
	CircleShape circle;

	circle.setPosition(Vector2f(shape.GetPosition().x - shape.GetRadius(), shape.GetPosition().y - shape.GetRadius()));
	circle.setRadius(shape.GetRadius());

	RGBA color = shape.GetColor();
	float stroke_width = shape.GetStrokeWidth();
	RGBA stroke_color = shape.GetStrokeColor();

	if (color.R != -1)
		if (color.A != -1) circle.setFillColor(Color(color.R, color.G, color.B, color.A));
		else circle.setFillColor(Color(color.R, color.G, color.B));

	if (stroke_width != -1) circle.setOutlineThickness(stroke_width);
	if (stroke_color.R != -1)
		if (stroke_color.A != -1) circle.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
		else circle.setOutlineColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));

	window.draw(circle);
}

void Drawer::DrawLine(RenderWindow& window, Polyline shape, Point p1, Point p2)
{
	float length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	float posX = p1.x, posY = p1.y;
	float rotation;
	float stroke_width = shape.GetStrokeWidth();

	if (p1.x == p2.x && p1.y < p2.y) //rotate 90 degree anticlockwise
	{
		rotation = -90;
		posY += stroke_width;
	}
	else if (p1.x == p2.x && p1.y > p2.y) //rotate 90 degree clockwise
	{
		rotation = 90;
		posY += stroke_width;
	}
	else //rotate 'x' degree
	{
		rotation = (pow(length, 2) + pow(p1.x - p2.x, 2) - pow(p1.y - p2.y, 2)) / (2 * length * abs(p1.x - p2.x));
		rotation = acos(rotation) * 180 / 3.141592; //go from radian to degree
	}


	RectangleShape lines(Vector2f(length, stroke_width));
	lines.rotate(-1 * rotation); // multiply by -1 since rotate method rotate shape clockwise.
	lines.setPosition(Vector2f(posX, posY));
	RGBA stroke_color = shape.GetStrokeColor();
	if (stroke_color.R != -1)
		if (stroke_color.A != -1) lines.setFillColor(Color(stroke_color.R, stroke_color.G, stroke_color.B, stroke_color.A));
		else lines.setFillColor(Color(stroke_color.R, stroke_color.G, stroke_color.B));

	window.draw(lines);
}

void Drawer::DrawPolyline(RenderWindow& window, Polyline shape)
{
	vector<Point> points = shape.GetPosition();
	if (points.size() <= 2)
	{
		DrawLine(window, shape, points[0], points[1]);
		return;
	}

	ConvexShape polyline;
	RGBA color = shape.GetColor();
	if (color.R != -1)
		if (color.A != -1) polyline.setFillColor(Color(color.R, color.G, color.B, color.A));
		else polyline.setFillColor(Color(color.R, color.G, color.B));

	vector<Point> pt;
	for (int i = 0; i < points.size() - 1; ++i)
	{
		Point iPoint = FindIntersectionPoint(points[0], points.back(), points[i], points[i + 1]);
		if (iPoint.x != -1)
			if (pt.size() == 0) pt.push_back(iPoint);
			else
			{
				pt.push_back(points[i]);
				pt.push_back(iPoint);
				polyline.setPointCount(pt.size());
				for (int j = 0; j < pt.size(); ++j) polyline.setPoint(j, Vector2f(pt[j].x, pt[j].y));
				window.draw(polyline);

				pt.clear();
				pt.push_back(iPoint);
			}
		else pt.push_back(points[i]);
	}

	for (int i = 0; i < points.size() - 1; ++i) DrawLine(window, shape, points[i], points[i + 1]);
}

void Drawer::DrawGroup(RenderWindow& window, Group shape)
{
}

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