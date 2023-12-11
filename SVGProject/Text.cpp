#include "stdafx.h"
#include "Shape.h"

Text::Text() {
	font = "Times New Roman"; text = "";
	size = 1;
	position.x = position.y = 0;
}

Text::~Text() {}

void Text::SetElement(vector<string> data)
{
	string getter;
	stringstream words(data[0]);
	while (words >> getter)
		text += getter + " ";

	for (int i = 1; i < data.size(); ++i)
	{
		readFigure(data);

		if (data[i].compare("font-family") == 0)
			font = data[++i];
		else if (data[i].compare("font-size") == 0)
			size = stof(data[++i]);

		else if (data[i].compare("x") == 0)
			position.x = stof(data[++i]);
		else if (data[i].compare("y") == 0)
			position.y = stof(data[++i]);
	}
}

void Text::clear() {
	fillColor.color = strokeColor.color = "";
	fillColor.R = fillColor.G = fillColor.B = 0;
	strokeColor.R = strokeColor.G = strokeColor.B = 0;
	fillColor.A = strokeColor.A = 1;
	strokeWidth = 1;

	font = "Times New Roman"; text = "";
	size = 1;
	position.x = position.y = 0;
	Figure::Reset();
}

string Text::GetFont()
{
	return this->font;
}

string Text::GetText()
{
	return this->text;
}

float Text::GetSize()
{
	return this->size;
}

Point2D Text::GetPosition()
{
	return this->position;
}