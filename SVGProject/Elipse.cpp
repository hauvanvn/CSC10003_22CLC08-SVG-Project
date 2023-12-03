#include "Shape.h"

Ellipse::Ellipse()
{
	stroke_width = -1;
	position.x = position.y = 0;
	m_radius.x = m_radius.y = 0;
	stroke_color.R = stroke_color.G = stroke_color.B = 0;
	color.R = color.G = color.B = 0;
	color.A = stroke_color.A = -1;
	rotation = 0;
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
	rotation = 0;
}

void Ellipse::SetPosition(Point position)
{
	this->position = position;
}

void Ellipse::SetMradius(Point m_radius)
{
	this->m_radius = m_radius;
}

void Ellipse::SetCenter()
{
	center.x = (position.x + m_radius.x) / 2;
	center.y = (position.y + m_radius.y) / 2;
}

Point Ellipse::GetPosition()
{
	return this->position;
}

Point Ellipse::GetMradius()
{
	return this->m_radius;
}