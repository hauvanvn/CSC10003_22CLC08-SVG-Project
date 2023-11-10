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

	type = s[0]; // Assigns the first string in the vector as the 'type'.

	for (int i = 1; i < s.size(); ++i) {
		int gap = 0;

		// Reconnects elements if the last character of the current string is not a double quote
		if (s[i + 1][s[i + 1].length() - 1] != '"') {
			// Concatenates subsequent strings until finding a closing quote
			for (int j = i + 2; s[j - 1].back() != '"'; ++j) {
				s[i + 1] = s[i + 1] + " " + s[j];
				gap++;
			}
		}

		// Removes double quotes from the string for conversion to numerical values
		for (char& c : s[i + 1]) {
			if (c == '"') {
				c = ' ';
			}
		}

		// Matches property keys and sets attributes accordingly
		if (s[i] == "fill-opacity") {
			color.A = stof(s[++i]) * 255;
		}
		else if (s[i] == "stroke-opacity") {
			stroke_color.A = stof(s[++i]) * 255;
		}
		else if (s[i] == "stroke-width") {
			stroke_width = stof(s[++i]);
		}
		else if (s[i] == "height") {
			height = stof(s[++i]);
		}
		else if (s[i] == "width") {
			width = stof(s[++i]);
		}
		else if (s[i] == "stroke") {
			i++;
			for (char& c : s[i]) {
				if ((c < '0' || c > '9') && c != '.') {
					c = ' ';
				}
			}
			stringstream str(s[i]);
			string temp;
			str >> temp;
			stroke_color.R = stof(temp);
			str >> temp;
			stroke_color.G = stof(temp);
			str >> temp;
			stroke_color.B = stof(temp);
		}
		else if (s[i] == "fill") {
			i++;
			for (char& c : s[i]) {
				if ((c < '0' || c > '9') && c != '.') {
					c = ' ';
				}
			}
			stringstream str(s[i]);
			string temp;
			str >> temp;
			color.R = stof(temp);
			str >> temp;
			color.G = stof(temp);
			str >> temp;
			color.B = stof(temp);
		}
		else if (s[i] == "x" || s[i] == "y") {
			if (point.size() != 1) {
				Point temp;
				if (s[i] == "x") {
					temp.x = stof(s[++i]);
				}
				else {
					temp.y = stof(s[++i]);
				}
				point.push_back(temp);
			}
			else {
				if (s[i] == "x") {
					point[0].x = stof(s[++i]);
				}
				else {
					point[0].y = stof(s[++i]);
				}
			}
		}
		else if (s[i] == "points") {
			i++;
			stringstream str(s[i]);
			string temp1;
			for (int j = 0; str >> temp1; ++j) {
				if (j % 2 == 0) {
					Point temp2;
					temp2.x = stof(temp1);
					point.push_back(temp2);
				}
				else {
					point[j / 2].y = stof(temp1);
				}
			}
		}
		// ... (handling various other properties like 'stroke', 'fill', 'x', 'y', 'points')

		i += gap; // Adjusts the index if there was reconnection
	}

	// If the point vector contains only one point, generates additional points to represent the corners of the polygon
	if (point.size() == 1) {
		point.push_back({ point[0].x, point[0].y + height });
		point.push_back({ point[0].x + width, point[0].y + height });
		point.push_back({ point[0].x + width, point[0].y });
	}
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

    int gap = 0;
    text += s[s.size() - 2]; // Set the text

    // Reconnect string elements until reaching a double quote or the start of the vector
    for (int i = s.size() - 3; i >= 0; --i) {
        if (s[i][s[i].length() - 1] == '"') {
            break;
        } else {
            text = s[i] + " " + text;
            gap++;
        }
    }

    int length = s.size() - 2 - gap;

    for (int i = 1; i < length; ++i) {
        gap = 0;

        // Reconnect elements that were dislocated due to stringstream usage
        if (s[i + 1][s[i + 1].length() - 1] != '"') {
            for (int j = i + 2; s[j - 1].back() != '"'; ++j) {
                s[i + 1] = s[i + 1] + " " + s[j];
                gap++;
            }
        }

        // Prepare for conversion to numerical values by removing double quotes
        for (int j = 0; j < s[i + 1].length(); ++j) {
            if (s[i + 1][j] == '"') {
                s[i + 1][j] = ' ';
            }
        }

        // Match property keys and assign attributes
        if (s[i].compare("font-size") == 0) {
            size = stof(s[++i]); // Set font size
        } else if (s[i].compare("x") == 0) {
            position.x = stof(s[++i]); // Set x position
        } else if (s[i].compare("y") == 0) {
            position.y = stof(s[++i]); // Set y position
        } else if (s[i].compare("fill") == 0) {
            i++;

            // Extract RGB color components and convert to float
            for (int j = 0; j < s[i].length(); ++j) {
                if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.') {
                    s[i][j] = ' ';
                }
            }

            stringstream str(s[i]);
            string temp;

            str >> temp;
            color.R = stof(temp);

            str >> temp;
            color.G = stof(temp);

            str >> temp;
            color.B = stof(temp);
        }

        i += gap; // Adjust index if elements were reconnected
    }
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

void Ellipse::SetElement(vector<string> s) {
    for (int i = 1; i < s.size(); ++i) {
        int gap = 0;

        if (s[i + 1][s[i + 1].length() - 1] != '"') {
            for (int j = i + 2; s[j - 1].back() != '"'; ++j) {
                s[i + 1] = s[i + 1] + " " + s[j];
                gap++;
            }
        }

        for (int j = 0; j < s[i + 1].length(); ++j) {
            if (s[i + 1][j] == '"') {
                s[i + 1][j] = ' ';
            }
        }

        if (s[i] == "fill-opacity") {
            color.A = stof(s[++i]) * 255;
        } else if (s[i] == "stroke-opacity") {
            stroke_color.A = stof(s[++i]) * 255;
        } else if (s[i] == "stroke-width") {
            stroke_width = stof(s[++i]);
        } else if (s[i] == "cx") {
            position.x = stof(s[++i]);
        } else if (s[i] == "cy") {
            position.y = stof(s[++i]);
        } else if (s[i] == "rx") {
            m_radius.x = stof(s[++i]);
        } else if (s[i] == "ry") {
            m_radius.y = stof(s[++i]);
        } else if (s[i] == "r") {
            i++; // Skipping radius element for Circle use
        } else if (s[i] == "stroke") {
            i++;
            for (int j = 0; j < s[i].length(); ++j) {
                if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.') {
                    s[i][j] = ' ';
                }
            }
            stringstream str(s[i]);
            string temp;
            str >> temp;
            stroke_color.R = stof(temp);
            str >> temp;
            stroke_color.G = stof(temp);
            str >> temp;
            stroke_color.B = stof(temp);
        } else if (s[i] == "fill") {
            i++;
            for (int j = 0; j < s[i].length(); ++j) {
                if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.') {
                    s[i][j] = ' ';
                }
            }
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

////////////////////////// Polyline \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void Polyline::SetElement(vector<string> s) {
    for (int i = 1; i < s.size(); ++i) {
        int gap = 0;

        if (s[i + 1][s[i + 1].length() - 1] != '"') {
            for (int j = i + 2; s[j - 1].back() != '"'; ++j) {
                s[i + 1] = s[i + 1] + " " + s[j];
                gap++;
            }
        }

        for (int j = 0; j < s[i + 1].length(); ++j) {
            if (s[i + 1][j] == '"') {
                s[i + 1][j] = ' ';
            }
        }

        if (s[i] == "fill-opacity") {
            color.A = stof(s[++i]) * 255; // Opacity for fill color
        } else if (s[i] == "stroke-opacity") {
            stroke_color.A = stof(s[++i]) * 255; // Opacity for stroke color
        } else if (s[i] == "stroke-width") {
            stroke_width = stof(s[++i]); // Width of the stroke
        } else if (s[i] == "stroke") {
            i++;
            for (int j = 0; j < s[i].length(); ++j) {
                if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.') {
                    s[i][j] = ' '; // Clean stroke color data
                }
            }
            stringstream str(s[i]);
            string temp;
            str >> temp;
            stroke_color.R = stof(temp); // Red component
            str >> temp;
            stroke_color.G = stof(temp); // Green component
            str >> temp;
            stroke_color.B = stof(temp); // Blue component
        } else if (s[i] == "fill") {
            i++;
            for (int j = 0; j < s[i].length(); ++j) {
                if ((s[i][j] < '0' || s[i][j] > '9') && s[i][j] != '.') {
                    s[i][j] = ' '; // Clean fill color data
                }
            }
            stringstream str(s[i]);
            string temp;
            str >> temp;
            color.R = stof(temp); // Red component
            str >> temp;
            color.G = stof(temp); // Green component
            str >> temp;
            color.B = stof(temp); // Blue component
        } else if (s[i] == "x1" || s[i] == "y1" || s[i] == "x2" || s[i] == "y2") {
            if (points.size() != 2) {
                if (points.size() != 1) {
                    Point temp;
                    if (s[i][0] == 'x') temp.x = stof(s[++i]);
                    else temp.y = stof(s[++i]);
                    points.push_back(temp); // First point
                } else {
                    if (s[i][0] == 'x') points[0].x = stof(s[++i]);
                    else points[0].y = stof(s[++i]);
                    Point temp;
                    points.push_back(temp); // Second point
                }
            } else {
                if (s[i][0] == 'x') points[1].x = stof(s[++i]);
                else points[1].y = stof(s[++i]);
            }
        } else if (s[i] == "points") {
            i++;
            stringstream str(s[i]);
            string temp1;

            for (int j = 0; str >> temp1; ++j) {
                if (j % 2 == 0) {
                    Point temp2;
                    temp2.x = stof(temp1);
                    points.push_back(temp2); // New point
                } else {
                    points[j / 2].y = stof(temp1); // Set y coordinate
                }
            }
        }

        i += gap; // Update index if there was a reconnecting action
    }
}
