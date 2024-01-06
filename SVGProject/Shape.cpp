#include "stdafx.h"
#include "Shape.h"
#define Kappa 0.551915024494
#define Pakka 1.5707963267948966
Drawer::Drawer() {}

Drawer::~Drawer() {}

void Drawer::readGradient(xml_node<>* root)
{
	xml_node<>* node = root->first_node();

	string nodeName;

	xml_attribute<>* attribute;
	string attributeName;
	string attributeValue;
	vector<string> collector;

	GradientColor gradient;

	while (node != NULL)
	{
		nodeName = node->name();
		if (nodeName.compare("linearGradient") != 0)
		{
			node = node->next_sibling();
			continue;
		}

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

		gradient.SetElement(collector);

		collector.clear();

		StopGradient stopG;
		xml_node<>* child = node->first_node();

		while (child != NULL)
		{
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

			for (int i = 0; i < collector.size(); ++i)
			{
				if (collector[i].compare("stop-color") == 0)
				{
					size_t foundRGB = collector[++i].find("rgb");
					if (foundRGB == string::npos)
						if (collector[i][0] != '#')
							stopG.stop_color.color = collector[i];
						else
							stopG.stop_color = Hex2RGBA(collector[i]);
					else
					{
						for (int j = 0; j < collector[i].length(); ++j)
							if ((collector[i][j] < '0' || collector[i][j] > '9') && collector[i][j] != '.' && collector[i][j] != '-')
								collector[i][j] = ' ';

						stringstream str(collector[i]);
						string getter;

						str >> getter;
						stopG.stop_color.R = stof(getter);
						str >> getter;
						stopG.stop_color.G = stof(getter);
						str >> getter;
						stopG.stop_color.B = stof(getter);
					}
				}
				else if (collector[i].compare("offset") == 0)
					stopG.offset = stof(collector[++i]);
				else if (collector[i].compare("stop-opacity") == 0)
					stopG.opacity = stof(collector[++i]);
			}

			gradient.addStopGradient(stopG);
			stopG.opacity = 1;

			collector.clear();
			child = child->next_sibling();
		}

		ListLinearGradient.push_back(gradient);

		gradient.clear();
		node = node->next_sibling();
	}
}

GradientColor Drawer::GetGradient(string ID)
{
	for (int i = 0; i < ListLinearGradient.size(); ++i)
		if (ID == ListLinearGradient[i].GetID())
			return ListLinearGradient[i];

	return GradientColor();
}

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
		if (tag.compare("text") == 0)
			collector.push_back(child->value());

		attribute = child->first_attribute();
		if (attribute == NULL)
		{
			if (tag.compare("g") == 0)
			{
				tempG = readGroup(child, collector);
				result.setGroup(tempG);
				drawer.shapeID.push_back(6);
				tempG.clear();
			}

			child = child->next_sibling();
			continue;
		}

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
			drawer.shapeID.push_back(6);
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

	string nodeName = rootNode->name();
	while (nodeName.compare("svg") != 0)
	{
		rootNode = rootNode->next_sibling();
		nodeName = rootNode->name();
	}
	xml_node<>* node = rootNode->first_node();

	vector<string> collector;
	xml_attribute<>* attribute;
	string attributeName;
	string attributeValue;

	while (node != NULL)
	{
		nodeName = node->name();
		if (nodeName.compare("text") == 0)
			collector.push_back(node->value());

		attribute = node->first_attribute();
		if (attribute == NULL)
		{
			if (nodeName.compare("g") == 0)
			{
				Group tempG = readGroup(node, collector);
				group.push_back(tempG);
				shapeID.push_back(6);
				tempG.clear();
			}
			else if (nodeName.compare("defs") == 0)		readGradient(node);

			node = node->next_sibling();
			continue;
		}

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
	vector<int> index(7, 0);

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
			DrawPath(hdc, path[index[i]++]);
			break;

		case 6:
			DrawGroup(hdc, group[index[i]++]);
			break;

		default:
			break;
		}
	}
}

VOID Drawer::DrawPolygon(HDC hdc, PolygonShape shape)
{
	Graphics graphics(hdc);

	graphics.SetTransform(shape.GetTransform());

	RGBA color = shape.GetFillColor();

	vector<Point2D> p = shape.GetPoints();
	string id = getGradientId(color.color);
	if (p.size() > 1)
	{
		Point* pt = new Point[p.size()];
		for (int i = 0; i < p.size(); ++i)
		{
			pt[i].X = p[i].x;
			pt[i].Y = p[i].y;
		}

		if (id != "")
		{
			if (GetGradient(id).GetID() != "")
				graphics.FillPolygon(shape.GetLinearGradient(GetGradient(id)), pt, p.size());
			else
				if (color.color != "none")
					graphics.FillPolygon(shape.GetFill(), pt, p.size());
		}
		else
			if (color.color != "none")
				graphics.FillPolygon(shape.GetFill(), pt, p.size());
		graphics.DrawPolygon(shape.GetStroke(), pt, p.size());

		delete[] pt;
	}
	else
	{
		if (id != "")
			graphics.FillRectangle(shape.GetLinearGradient(GetGradient(id)), p[0].x, p[0].y, shape.GetWidth(), shape.GetHeight());
		else
			if (color.color != "none")
				graphics.FillRectangle(shape.GetFill(), p[0].x, p[0].y, shape.GetWidth(), shape.GetHeight());
		graphics.DrawRectangle(shape.GetStroke(), p[0].x, p[0].y, shape.GetWidth(), shape.GetHeight());
	}
}

VOID Drawer::DrawText(HDC hdc, Text shape)
{
	Graphics graphics(hdc);

	graphics.SetTransform(shape.GetTransform());

	RGBA color = shape.GetFillColor();

	FontFamily fontFamily(String2Wstring(shape.GetFont()).c_str());
	Font font(&fontFamily, shape.GetSize(), FontStyleRegular, UnitPixel);
	PointF point(shape.GetPosition().x, shape.GetPosition().y - shape.GetSize());

	string id = getGradientId(color.color);
	if (id != "")
	{
		if (GetGradient(id).GetID() != "")
			graphics.DrawString(String2Wstring(shape.GetText()).c_str(), -1, &font, point, shape.GetLinearGradient(GetGradient(id)));
		else
			if (color.color != "none")
				graphics.DrawString(String2Wstring(shape.GetText()).c_str(), -1, &font, point, shape.GetFill());
	}
	else
		if (color.color != "none")
			graphics.DrawString(String2Wstring(shape.GetText()).c_str(), -1, &font, point, shape.GetFill());
}

VOID Drawer::DrawEllipse(HDC hdc, EllipseShape shape)
{
	Graphics graphics(hdc);

	graphics.SetTransform(shape.GetTransform());

	RectF ellipseRect(shape.GetPosition().x - shape.GetWidth(), shape.GetPosition().y - shape.GetHeight(), shape.GetWidth() * 2, shape.GetHeight() * 2);

	RGBA color = shape.GetFillColor();
	string id = getGradientId(color.color);
	if (id != "")
	{
		if (GetGradient(id).GetID() != "")
			graphics.FillEllipse(shape.GetLinearGradient(GetGradient(id)), ellipseRect);
		else
			if (color.color != "none")
				graphics.FillEllipse(shape.GetFill(), ellipseRect);
	}
	else
		if (color.color != "none")
			graphics.FillEllipse(shape.GetFill(), ellipseRect);
	graphics.DrawEllipse(shape.GetStroke(), ellipseRect);
}

VOID Drawer::DrawPolyline(HDC hdc, PolylineShape shape)
{
	Graphics graphics(hdc);

	graphics.SetTransform(shape.GetTransform());

	RGBA color = shape.GetFillColor();
	vector<Point2D> p = shape.GetPoints();
	Point* pt = new Point[p.size()];
	for (int i = 0; i < p.size(); ++i)
	{
		pt[i].X = p[i].x;
		pt[i].Y = p[i].y;
	}

	string id = getGradientId(color.color);
	if (id != "")
	{
		if (GetGradient(id).GetID() != "")
			graphics.FillPolygon(shape.GetLinearGradient(GetGradient(id)), pt, p.size());
		else
			if (color.color != "none")
				graphics.FillPolygon(shape.GetFill(), pt, p.size());
	}
	else
		if (color.color != "none")
			graphics.FillPolygon(shape.GetFill(), pt, p.size());
	graphics.DrawLines(shape.GetStroke(), pt, p.size());

	delete[] pt;
}

VOID Drawer::DrawPath(HDC hdc, Path shape)
{
	Graphics graphics(hdc);

	graphics.SetTransform(shape.GetTransform());

	RGBA color = shape.GetFillColor();
	vector<PathShapes> pShape = shape.GetPathShapes();
	GraphicsPath path;

	PointF pre, first;
	first.X = pShape[0].points[0].x;
	first.Y = pShape[0].points[0].y;
	pre = first;
	bool newPath = true;

	for (int i = 0; i < pShape.size(); ++i)
	{
		int n = pShape[i].points.size();
		PointF* pt = new PointF[n];
		for (int j = 0; j < n; ++j)
		{
			pt[j].X = pShape[i].points[j].x;
			pt[j].Y = pShape[i].points[j].y;
		}

		switch (pShape[i].type)
		{
		case 'M': case 'm':
		{
			if (pShape[i].type == 'm')
			{
				pre.X += pt[0].X;
				pre.Y += pt[0].Y;
			}
			else pre = pt[n - 1];
			break;
		}

		case 'L':
			path.AddLine(pre, pt[0]);
			pre = pt[n - 1];
			break;

		case 'H': case 'V':
		{
			if (pt[0].X == 0) pt[0].X = pre.X;
			if (pt[0].Y == 0) pt[0].Y = pre.Y;

			path.AddLine(pre, pt[0]);
			pre = pt[n - 1];
			break;
		}

		case 'l': case 'h': case 'v':
		{
			PointF newPoint = pre;
			newPoint.X += pt[0].X;
			newPoint.Y += pt[0].Y;
			path.AddLine(pre, newPoint);
			pre = newPoint;
			break;
		}

		case 'C': case 'c':
		{
			if (pShape[i].type == 'c')
				for (int j = 0; j < 3; ++j)
				{
					pt[j].X += pre.X;
					pt[j].Y += pre.Y;

					pShape[i].points[j].x += pre.X;
					pShape[i].points[j].y += pre.Y;
				}

			path.AddBezier(pre, pt[0], pt[1], pt[2]);
			pre = pt[n - 1];
			break;
		}

		case 'S': case 's':
		{
			PointF controlP = pre;

			if (pShape[i].type == 's')
				for (int j = 0; j < 2; ++j)
				{
					pt[j].X += pre.X;
					pt[j].Y += pre.Y;

					pShape[i].points[j].x += pre.X;
					pShape[i].points[j].y += pre.Y;
				}
			if (i > 0 && (pShape[i - 1].type == 'S' || pShape[i - 1].type == 's' || pShape[i - 1].type == 'C' || pShape[i - 1].type == 'c'))
			{
				PointF oldControlP;
				if (pShape[i - 1].points.size() == 3)
				{
					oldControlP.X = pShape[i - 1].points[1].x;
					oldControlP.Y = pShape[i - 1].points[1].y;
				}
				else
				{
					oldControlP.X = pShape[i - 1].points[0].x;
					oldControlP.Y = pShape[i - 1].points[0].y;
				}
				controlP.X = 2 * pre.X - oldControlP.X;
				controlP.Y = 2 * pre.Y - oldControlP.Y;
			}

			path.AddBezier(pre, controlP, pt[0], pt[1]);
			pre = pt[n - 1];
			break;
		}

		case 'Q': case 'q':
		{
			if (pShape[i].type == 'q')
				for (int j = 0; j < 2; ++j)
				{
					pt[j].X += pre.X;
					pt[j].Y += pre.Y;

					pShape[i].points[j].x += pre.X;
					pShape[i].points[j].y += pre.Y;
				}

			path.AddBezier(pre, pt[0], pt[1], pt[1]);
			pre = pt[n - 1];
			break;
		}

		case 'T': case 't':
		{
			PointF controlP = pre;
			PointF oldControlP;

			if (pShape[i].type == 't')
			{
				pt[0].X += pre.X;
				pt[0].Y += pre.Y;
			}

			if (i > 0 && (pShape[i - 1].type == 'T' || pShape[i - 1].type == 't' || pShape[i - 1].type == 'Q' || pShape[i - 1].type == 'q'))
			{
				oldControlP.X = pShape[i - 1].points[0].x;
				oldControlP.Y = pShape[i - 1].points[0].y;

				controlP.X = 2 * pre.X - oldControlP.X;
				controlP.Y = 2 * pre.Y - oldControlP.Y;
			}

			path.AddBezier(pre, controlP, pt[0], pt[0]);
			pre = pt[n - 1];

			pt[0].X = oldControlP.X;
			pt[0].Y = oldControlP.Y;
			break;
		}

		case 'A': case 'a':
		{
			if (pShape[i].type == 'a')
			{
				pt[3].X += pre.X;
				pt[3].Y += pre.Y;
			}

			double pi = atan(1) * 4.f;
			double angle = pt[1].X * pi / 180.f;
			double cosAngle = cos(pt[1].X);
			double sinAngle = sin(pt[1].X);

			PointF point1;
			point1.X = cosAngle * (pre.X - pt[3].X) / 2 + sinAngle * (pre.Y - pt[3].Y) / 2.f;
			point1.Y = -sinAngle * (pre.X - pt[3].X) / 2 + cosAngle * (pre.Y - pt[3].Y) / 2.f;

			double radiiCheck = (point1.X * point1.X) / (pt[0].X * pt[0].X) + (point1.Y * point1.Y) / (pt[0].Y * pt[0].Y);
			if (radiiCheck > 1.0f)
			{
				pt[0].X = sqrt(radiiCheck) * pt[0].X;
				pt[0].Y = sqrt(radiiCheck) * pt[0].Y;
			}

			PointF centerTemp;
			double sign = 1; //positive
			if (pt[2].X == pt[2].Y)	sign = -1.f;

			centerTemp.X = sign * sqrt(abs(((pt[0].X * pt[0].X * pt[0].Y * pt[0].Y) - (pt[0].X * pt[0].X * point1.Y * point1.Y) - (point1.X * point1.X * pt[0].Y * pt[0].Y)) / ((pt[0].X * pt[0].X * point1.Y * point1.Y) + (point1.X * point1.X * pt[0].Y * pt[0].Y)))) * (pt[0].X * point1.Y / pt[0].Y);
			centerTemp.Y = sign * sqrt(abs(((pt[0].X * pt[0].X * pt[0].Y * pt[0].Y) - (pt[0].X * pt[0].X * point1.Y * point1.Y) - (point1.X * point1.X * pt[0].Y * pt[0].Y)) / ((pt[0].X * pt[0].X * point1.Y * point1.Y) + (point1.X * point1.X * pt[0].Y * pt[0].Y)))) * (-pt[0].Y * point1.X / pt[0].X);

			PointF center;
			center.X = (cosAngle * centerTemp.X - sinAngle * +centerTemp.Y) + (pre.X + pt[3].X) / 2.f;
			center.Y = (sinAngle * centerTemp.X + cosAngle * +centerTemp.Y) + (pre.Y + pt[3].Y) / 2.f;

			PointF startPoint;
			startPoint.X = (point1.X - centerTemp.X) / pt[0].X;
			startPoint.Y = (point1.Y - centerTemp.Y) / pt[0].Y;

			sign = 1.f;
			if (startPoint.Y < 0)	sign = -1.f;
			double temp = startPoint.X / (sqrt(startPoint.X * startPoint.X + startPoint.Y * startPoint.Y));
			if (temp < -1)	temp = -1.f;
			else if (temp > 1)	temp = 1.f;
			double startAngle = sign * acos(temp);

			PointF endPoint;
			endPoint.X = (-point1.X - centerTemp.X) / pt[0].X;
			endPoint.Y = (-point1.Y - centerTemp.Y) / pt[0].Y;

			if (startPoint.X * endPoint.Y - startPoint.Y * endPoint.X < 0)	sign = -1.f;
			else	sign = 1.f;
			temp = (startPoint.X * endPoint.X + startPoint.Y * endPoint.Y) / (sqrt(startPoint.X * startPoint.X + startPoint.Y * startPoint.Y) * sqrt(endPoint.X * endPoint.X + endPoint.Y * endPoint.Y));
			if (temp < -1)	temp = -1.f;
			else if (temp > 1)	temp = 1.f;

			if (startPoint.X * endPoint.X + startPoint.Y * endPoint.Y < 0)	sign = -1.f;
			double deltaAngle = sign * acos(temp);

			if (pt[2].Y && deltaAngle < 0)	deltaAngle += 2.f * pi;
			else if (!pt[2].Y && deltaAngle > 0) deltaAngle -= 2.f * pi;

			double ratio = abs(deltaAngle) / (pi / 2.f);
			if (abs(1.f - ratio) < 0.00001)		ratio = 1.f;
			int segment = max(static_cast<int>(ceil(ratio)), 1);
			deltaAngle /= segment;

			vector<vector<vector<double>>> curves;
			vector<vector<double>> curve;
			for (int t = 0; t < segment; ++t)
			{
				double kappa = (deltaAngle == Pakka) ? Kappa : (deltaAngle == -Pakka) ? -Kappa : 4.f / 3.f * tan(deltaAngle / 4.f);
				double x3 = cos(startAngle);
				double y3 = sin(startAngle);
				double x4 = cos(startAngle + deltaAngle);
				double y4 = sin(startAngle + deltaAngle);

				curve.push_back({ x3 - y3 * kappa, y3 + x3 * kappa });
				curve.push_back({ x4 + y4 * kappa, y4 - x4 * kappa });
				curve.push_back({ x4, y4 });

				curves.push_back(curve);

				curve.clear();
				startAngle += deltaAngle;
			}

			for (auto& cur : curves)
			{
				auto mapped_curve_0 = { (cosAngle * cur[0][0] * pt[0].X - sinAngle * cur[0][1] * pt[0].Y) + center.X, (sinAngle * cur[0][0] * pt[0].X + cosAngle * cur[0][1] * pt[0].Y) + center.Y };
				auto mapped_curve_1 = { (cosAngle * cur[1][0] * pt[0].X - sinAngle * cur[1][1] * pt[0].Y) + center.X, (sinAngle * cur[1][0] * pt[0].X + cosAngle * cur[1][1] * pt[0].Y) + center.Y };
				auto mapped_curve_2 = { (cosAngle * cur[2][0] * pt[0].X - sinAngle * cur[2][1] * pt[0].Y) + center.X, (sinAngle * cur[2][0] * pt[0].X + cosAngle * cur[2][1] * pt[0].Y) + center.Y };

				cur = { mapped_curve_0, mapped_curve_1, mapped_curve_2 };

				for (size_t j = 0; j < cur.size(); j += 3)
					if (j + 2 < cur.size())
					{
						PointF P1(cur[j][0], cur[j][1]);
						PointF P2(cur[j + 1][0], cur[j + 1][1]);
						PointF P3(cur[j + 2][0], cur[j + 2][1]);

						path.AddBezier(pre, P1, P2, P3);
						pre = P3;
					}
			}

			pre = pt[n - 1];
			break;
		}

		case 'Z': case 'z':
		{
			path.AddLine(pre, first);
			pre = first;
			break;
		}

		default:
			break;
		}

		delete[] pt;
	}

	string id = getGradientId(color.color);
	if (id != "")
	{
		if (GetGradient(id).GetID() != "")
			graphics.FillPath(shape.GetLinearGradient(GetGradient(id)), &path);
		else graphics.FillPath(shape.GetFill(), &path);
	}
	else graphics.FillPath(shape.GetFill(), &path);
	graphics.DrawPath(shape.GetStroke(), &path);
}

VOID Drawer::DrawGroup(HDC hdc, Group shape)
{
	shape.ApplyGroup2Child();
	vector<int> index(7, 0);
	vector<PolygonShape> polygon = shape.GetPolygon();
	vector<Text> text = shape.GetText();
	vector<EllipseShape> ellipse = shape.GetEllipse();
	vector<PolylineShape> polyline = shape.GetPolyline();
	vector<Path> path = shape.GetPath();
	vector<Group> group = shape.GetGroup();
	vector<int> shapeID = shape.GetShapeID();

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
			DrawPath(hdc, path[index[i]++]);
			break;

		case 6:
			DrawGroup(hdc, group[index[i]++]);
			break;

		default:
			break;
		}
	}
}

wstring String2Wstring(string s)
{
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring wContent = converter.from_bytes(s);
	return wContent;
}

