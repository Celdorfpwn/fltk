#include "stdafx.h"

BaseGroup::BaseGroup(int x, int y, const char* t):Fl_Group(x, y, 400, 1000, t)
{
	this->controlY = 20;
	this->maskY = 20;
}

BaseGroup::~BaseGroup()
{
}

Fl_Input* BaseGroup::createInput(const char* value, const char* maskText, bool active)
{
	Fl_Box *mask = new Fl_Box(this->x() + 10, this->y() + this->maskY, 50, 30, maskText);
	mask->align(FL_ALIGN_POSITION_MASK);
	Fl_Input *input = new Fl_Input(this->x() + 10, this->y() + this->controlY, this->w(), 30);
	
	if (value)
	{
		input->value(value);
	}

	if (!active)
	{
		input->deactivate();
	}

	this->controlY += 60;
	this->maskY += 120;

	return input;
}

Fl_Button* BaseGroup::createCenterButton(const char* text)
{
	Fl_Button* button = new Fl_Button(this->x() + 150, this->y() + this->controlY, 100, 30, text);
	this->controlY += 60;
	return button;
}