#include "stdafx.h"
#include "Shape.h"
////////////////////////////// Figure \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//void Figure::SetColor(RGBA color)
//{
//	this->color = color;
//}
//
//void Figure::SetStrokeWidth(float width)
//{
//	this->stroke_width = width;
//}
//
//void Figure::SetStrokeColor(RGBA color)
//{
//	this->stroke_color = color;
//}
//
//RGBA Figure::GetColor()
//{
//	return this->color;
//}
//
//float Figure::GetStrokeWidth()
//{
//	return this->stroke_width;
//}
//
//RGBA Figure::GetStrokeColor()
//{
//	return this->stroke_color;
//}

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

