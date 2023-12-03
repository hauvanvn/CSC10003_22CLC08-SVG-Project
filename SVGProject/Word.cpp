#include "Shape.h"

Word::Word()
{
	rotation = 0;
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
	rotation = 0;
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