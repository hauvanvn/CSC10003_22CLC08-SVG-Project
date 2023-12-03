#include "Shape.h"

Polyline::Polyline()
{
	stroke_width = -1;
	points.clear();
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
	rotation = 0;
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
	stroke_width = 1;
	points.clear();
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
	rotation = 0;
}

void Polyline::SetPosition(vector<Point> pt)
{
	for (int i = 0; i < points.size(); ++i)
		points[i] = pt[i];
}

void Polyline::SetCenter()
{
	center = { 0, 0 };
	int count = 0;
	for (int i = 0; i < points.size(); ++i)
	{
		center.x += points[i].x;
		center.y += points[i].y;
		++count;
	}

	center.x = center.x / count;
	center.y = center.y / count;
}

vector<Point> Polyline::GetPosition()
{
	return points;
}