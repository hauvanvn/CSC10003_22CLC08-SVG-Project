#include "stdafx.h"
#include "Shape.h"

Text::Text() {
	font = text = "";
	size = 1;
	position.x = position.y = 0;
}

Text::~Text() {}

void Text::SetElement(vector<string> data)
{
	text = data[0];

	for (int i = 1; i < data.size(); ++i)
	{
		if (data[i].compare("fill") == 0)
			fillColor = data[++i];
		else if (data[i].compare("stroke") == 0)
			strokeColor = data[++i];

		else if (data[i].compare("fill-opacity") == 0)
			fillColor_opa = stof(data[++i]);
		else if (data[i].compare("stroke-opacity") == 0)
			strokeColor_opa = stof(data[++i]);
		else if (data[i].compare("stroke-width") == 0)
			strokeWidth = stof(data[++i]);					//Finish update attribute in Figure

		else if (data[i].compare("font-size") == 0)
			size = stof(data[++i]);

		else if (data[i].compare("x") == 0)
			position.x = stof(data[++i]);
		else if (data[i].compare("y") == 0)
			position.y = stof(data[++i]);
	}
}

void Text::clear() {
	fillColor = strokeColor = "black";
	fillColor_opa = strokeColor_opa = 1;
	strokeWidth = 1;

	font = text = "";
	size = 1;
	position.x = position.y = 0;
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
