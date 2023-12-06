#include "stdafx.h"
#include "Shape.h"
////////////////////////////// Figure \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

///////////////////////// Drawer \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Drawer::Drawer() {}

Drawer::~Drawer() {}

void Drawer::processData(vector<string> collector, string tag)
{
	PolygonShape tempP;		//temp object to hold data
	Text tempT;
	EllipseShape tempE;
	PolylineShape tempL;
	Path tempPa;

	if (tag.compare("rect") == 0 || tag.compare("polygon") == 0)
	{
		tempP.SetElement(collector);
		polygon.push_back(tempP);
		shapeID.push_back(1);
		tempP.clear();
	}
	else if (tag.compare("text") == 0)
	{
		tempT.SetElement(collector);
		text.push_back(tempT);
		shapeID.push_back(2);
		tempT.clear();
	}
	else if (tag.compare("ellipse") == 0 || tag.compare("circle") == 0)
	{
		tempE.SetElement(collector);
		ellipse.push_back(tempE);
		shapeID.push_back(3);
		tempE.clear();
	}
	else if (tag.compare("line") == 0 || tag.compare("polyline") == 0)
	{
		tempL.SetElement(collector);
		polyline.push_back(tempL);
		shapeID.push_back(4);
		tempL.clear();
	}
	else if (tag.compare("path") == 0)
	{
		tempPa.SetElement(collector);
		path.push_back(tempPa);
		shapeID.push_back(5);
		tempPa.clear();
	}
}

Group Drawer::readGroup(xml_node<>* node, vector<string> data)
{
	Group result;
	result.SetElement(data);

	Drawer drawer;			//temp object to hold data
	Group tempG;

	xml_node<>* child = node->first_node();

	vector<string> collector;
	xml_attribute<>* attribute;
	string attributeName;
	string attributeValue;

	while (child != NULL)
	{
		string tag = child->name();
		attribute = child->first_attribute();
		attributeName = attribute->name();
		attributeValue = attribute->value();

		collector.push_back(attributeName);
		collector.push_back(attributeValue);

		while (attribute != child->last_attribute())
		{
			attribute = attribute->next_attribute();
			attributeName = attribute->name();
			attributeValue = attribute->value();
			collector.push_back(attributeName);
			collector.push_back(attributeValue);
		}

		if (tag.compare("g") == 0)
		{
			tempG = readGroup(child, collector);
			result.setGroup(tempG);
			tempG.clear();
		}
		else	drawer.processData(collector, tag);

		collector.clear();
		child = child->next_sibling();
	}

	result.setPolygon(drawer.polygon);
	result.setText(drawer.text);
	result.setEllipse(drawer.ellipse);
	result.setPolyline(drawer.polyline);
	result.setPath(drawer.path);
	result.setShapeID(drawer.shapeID);

	return result;
}

void Drawer::readData(string filename)
{
	xml_document<> doc;
	xml_node<>* rootNode;
	// Read the xml file into a vector
	ifstream file(filename);
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);

	rootNode = doc.first_node();
	xml_node<>* node = rootNode->first_node();

	vector<string> collector;
	xml_attribute<>* attribute;
	string attributeName;
	string attributeValue;

	while (node != NULL) {
		string nodeName = node->name();
		if (nodeName.compare("text") == 0)
			collector.push_back(node->value());

		attribute = node->first_attribute();
		attributeName = attribute->name();
		attributeValue = attribute->value();

		collector.push_back(attributeName);
		collector.push_back(attributeValue);

		while (attribute != node->last_attribute())
		{
			attribute = attribute->next_attribute();
			attributeName = attribute->name();
			attributeValue = attribute->value();
			collector.push_back(attributeName);
			collector.push_back(attributeValue);
		}

		if (nodeName.compare("g") == 0)
		{
			Group tempG = readGroup(node, collector);
			group.push_back(tempG);
			shapeID.push_back(6);
			tempG.clear();
		}
		else	processData(collector, nodeName);

		collector.clear();
		node = node->next_sibling();
	}
}

VOID Drawer::Draw(HDC hdc)
{
	vector<int> index(6, 0);

	for (int i : shapeID)
	{
		switch (i)
		{
		case 1:
			DrawPolygon(hdc, polygon[index[i]++]);
			break;

		case 2:
			DrawText(hdc, text[index[i]++]);
			break;

		case 3:
			DrawEllipse(hdc, ellipse[index[i]++]);
			break;

		case 4:
			DrawPolyline(hdc, polyline[index[i]++]);
			break;

		case 5:
			//DrawPath(hdc, path[index[i]++]);
			break;

		case 6:
			//DrawGroup(hdc, group[index[i]++]);
			break;

		default:
			break;
		}
	}
}

VOID Drawer::DrawPolygon(HDC hdc, PolygonShape shape)
{
	Graphics graphics(hdc);

	RGBA color = shape.GetStrokeColor();
	Pen pen(Color(255 * color.A, color.R, color.G, color.B));
	pen.SetWidth(shape.GetStrokeWidth());

	color = shape.GetFillColor();
	SolidBrush brush(Color(255 * color.A, color.R, color.G, color.B));

	vector<Point2D> p = shape.GetPoints();
	if (p.size() > 1)
	{
		Point* pt = new Point[p.size()];
		for (int i = 0; i < p.size(); ++i)
		{
			pt[i].X = p[i].x;
			pt[i].Y = p[i].y;
		}

		graphics.FillPolygon(&brush, pt, p.size());
		graphics.DrawPolygon(&pen, pt, p.size());

		delete[] pt;
	}
	else
	{
		graphics.FillRectangle(&brush, p[0].x, p[0].y, shape.GetWidth(), shape.GetHeight());
		graphics.DrawRectangle(&pen, p[0].x, p[0].y, shape.GetWidth(), shape.GetHeight());
	}
}

VOID Drawer::DrawText(HDC hdc, Text shape)
{
	Graphics graphics(hdc);

	RGBA color = shape.GetFillColor();

	FontFamily fontFamily(String2Wstring(shape.GetFont()).c_str());
	Font font(&fontFamily, shape.GetSize(), FontStyleRegular, UnitPixel);
	PointF point(shape.GetPosition().x, shape.GetPosition().y - shape.GetSize());
	SolidBrush solidBrush(Color(255 * color.A, color.R, color.G, color.B));

	graphics.DrawString(String2Wstring(shape.GetText()).c_str(), -1, &font, point, &solidBrush);
}

VOID Drawer::DrawEllipse(HDC hdc, EllipseShape shape)
{
	Graphics graphics(hdc);

	RGBA color = shape.GetStrokeColor();
	Pen pen(Color(255 * color.A, color.R, color.G, color.B));
	pen.SetWidth(shape.GetStrokeWidth());

	color = shape.GetFillColor();
	SolidBrush brush(Color(255 * color.A, color.R, color.G, color.B));

	RectF ellipseRect(shape.GetPosition().x - shape.GetWidth(), shape.GetPosition().y - shape.GetHeight(), shape.GetWidth() * 2, shape.GetHeight() * 2);

	graphics.FillEllipse(&brush, ellipseRect);
	graphics.DrawEllipse(&pen, ellipseRect);
}

VOID Drawer::DrawPolyline(HDC hdc, PolylineShape shape)
{
	Graphics graphics(hdc);

	RGBA color = shape.GetStrokeColor();
	Pen pen(Color(255 * color.A, color.R, color.G, color.B));
	pen.SetWidth(shape.GetStrokeWidth());

	color = shape.GetFillColor();
	SolidBrush brush(Color(255 * color.A, color.R, color.G, color.B));

	vector<Point2D> p = shape.GetPoints();
	Point* pt = new Point[p.size()];
	for (int i = 0; i < p.size(); ++i)
	{
		pt[i].X = p[i].x;
		pt[i].Y = p[i].y;
	}

	graphics.FillPolygon(&brush, pt, p.size());
	graphics.DrawLines(&pen, pt, p.size());

	delete[] pt;
}

VOID Drawer::DrawGroup(HDC hdc, Group shape)
{
	Graphics graphics(hdc);

	Pen pen(Color::Black);

	vector<GraphicsPath> paths;

	vector<int> index(6, 0);
	for (int i : shapeID)
	{
		//switch (i)
		//{
		//case 0:
		//	GraphicsPath polygonPath;
		//	//if (polygon[index[i]].GetWidth() == -1)
		//	//	polygonPath.AddRectangle()
		//	DrawPolygon(hdc, polygon[index[i]++]);
		//	break;

		//case 1:
		//	DrawText(hdc, text[index[i]++]);
		//	break;

		//case 2:
		//	DrawEllipse(hdc, ellipse[index[i]++]);
		//	break;

		//case 3:
		//	DrawPolyline(hdc, polyline[index[i]++]);
		//	break;

		//case 4:
		//	//DrawPath(hdc, path[index[i]++]);
		//	break;
		//
		//case 5:
		//	DrawGroup(hdc, group[index[i]++]);
		//	break;

		//default:
		//	break;
		//}
	}
}

//Point FindIntersectionPoint(Point A, Point B, Point C, Point D)
//{
//	float a1 = B.y - A.y;
//	float b1 = A.x - B.x;
//	float c1 = a1 * A.x + b1 * A.y;
//
//	float a2 = D.y - C.y;
//	float b2 = C.x - D.x;
//	float c2 = a2 * C.x + b2 * C.y;
//
//
//	float determinant = a1 * b2 - a2 * b1;
//
//	if (determinant == 0)
//	{
//		return { -1, -1 };
//	}
//	else
//	{
//		float x = (b2 * c1 - b1 * c2) / determinant;
//		float y = (a1 * c2 - a2 * c1) / determinant;
//		{
//			return { x, y };
//		}
//	}
//}

wstring String2Wstring(string s)
{
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring wContent = converter.from_bytes(s);
	return wContent;
}
