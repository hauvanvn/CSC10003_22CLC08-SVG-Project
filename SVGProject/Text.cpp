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
		{
			size_t foundRGB = data[++i].find("rgb");
			if(foundRGB == string::npos)
				fillColor.color = data[i];
			else
			{
				for(int j = 0; j < data[i].length(); ++j)
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
				fillColor.color = data[i];
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

		else if (data[i].compare("fill-opacity") == 0)
			fillColor.A = stof(data[++i]);
		else if (data[i].compare("stroke-opacity") == 0)
			strokeColor.A = stof(data[++i]);
		else if (data[i].compare("stroke-width") == 0)
			strokeWidth = stof(data[++i]);					//Finish update attribute in Figure

		else if (data[i].compare("font-family") == 0)
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
