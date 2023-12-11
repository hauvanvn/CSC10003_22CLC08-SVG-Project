#include "stdafx.h"
#include "Shape.h"

Figure::Figure()
{
	strokeWidth = 1;
	angle = 0;
	translate = { 0, 0 };
	scale = { 1, 1 };
}

Figure::~Figure() {}

RGBA Hex2RGBA(string data);

void Figure::readFigure(vector<string> data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].compare("fill") == 0)
		{
			size_t foundRGB = data[++i].find("rgb");
			if (foundRGB == string::npos)
				if (data[i][0] != '#')
					fillColor.color = data[i];
				else
					fillColor = Hex2RGBA(data[i]);
			else
			{
				for (int j = 0; j < data[i].length(); ++j)
					if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-')
						data[i][j] = ' ';

				stringstream str(data[i]);
				string getter;

				str >> getter;
				fillColor.R = stof(getter);
				str >> getter;
				fillColor.G = stof(getter);
				str >> getter;
				fillColor.B = stof(getter);
			}
		}
		else if (data[i].compare("stroke") == 0)
		{
			size_t foundRGB = data[++i].find("rgb");
			if (foundRGB == string::npos)
				if (data[i][0] != '#')
					strokeColor.color = data[i];
				else
					strokeColor = Hex2RGBA(data[i]);
			else
			{
				for (int j = 0; j < data[i].length(); ++j)
					if ((data[i][j] < '0' || data[i][j] > '9') && data[i][j] != '.' && data[i][j] != '-')
						data[i][j] = ' ';

				stringstream str(data[i]);
				string getter;

				str >> getter;
				strokeColor.R = stof(getter);
				str >> getter;
				strokeColor.G = stof(getter);
				str >> getter;
				strokeColor.B = stof(getter);
			}
		}

		else if (data[i].compare("fill-opacity") == 0)
			fillColor.A = stof(data[++i]);
		else if (data[i].compare("stroke-opacity") == 0)
			strokeColor.A = stof(data[++i]);
		else if (data[i].compare("stroke-width") == 0)
			strokeWidth = stof(data[++i]);
	}
}

void Figure::AddTranslate(Point2D position)
{
	this->translate.x += position.x;
	this->translate.y += position.y;
}

void Figure::AddAngle(float angle)
{
	this->angle += angle;
}

void Figure::AddFillColor(RGBA newColor)
{
	if (fillColor.R == 0 && fillColor.G == 0 && fillColor.B == 0 && fillColor.A == 1)
		fillColor = newColor;
}

void Figure::AddStrokeColor(RGBA newColor)
{
	if (strokeColor.R == 0 && strokeColor.G == 0 && strokeColor.B == 0 && strokeColor.A == 1)
		strokeColor = newColor;
}

void Figure::SetAnchor(Point2D anchor)
{
	this->anchor = anchor;
}

void Figure::SetScale(Point2D scale)
{
	if (this->scale.x == 1 && this->scale.y == 0)
		this->scale = scale;
}

void Figure::Reset()
{
	Figure::Figure();
}

RGBA Figure::GetFillColor()
{
	return this->fillColor;
}

RGBA Figure::GetStrokeColor()
{
	return this->strokeColor;
}

float Figure::GetStrokeWidth()
{
	return this->strokeWidth;
}

Point2D Figure::GetTranslate()
{
	return this->translate;
}

float Figure::GetAngle()
{
	return this->angle;
}

Point2D Figure::GetAnchor()
{
	return this->anchor;
}

Point2D Figure::GetScale()
{
	return this->scale;
}

RGBA Hex2RGBA(string data)
{
	RGBA color;
	float hex = 0;

	for (int i = 1; i < data.length(); ++i)
	{
		switch (data[i])
		{
		case 0: hex = 0;
			break;
		case '1': hex = 1;
			break;
		case '2': hex = 2;
			break;
		case '3': hex = 3;
			break;
		case '4': hex = 4;
			break;
		case '5': hex = 5;
			break;
		case '6': hex = 6;
			break;
		case '7': hex = 7;
			break;
		case '8': hex = 8;
			break;
		case '9': hex = 9;
			break;
		case 'A': hex = 10;
			break;
		case 'B': hex = 11;
			break;
		case 'C': hex = 12;
			break;
		case 'D': hex = 13;
			break;
		case 'E': hex = 14;
			break;
		case 'F': hex = 15;
			break;
		}

		if (i <= 2)
			if (i == 2)		color.R += hex * 16;
			else			color.R += hex;
		else if(i <= 4)
			if (i == 4)		color.G += hex * 16;
			else			color.G += hex;
		else 
			if (i == 6)		color.B += hex * 16;
			else			color.B += hex;
	}

	return color;
}