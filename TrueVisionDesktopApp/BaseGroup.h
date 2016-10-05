#pragma once
#include "stdafx.h"

class BaseGroup: public Fl_Group
{
public:
	BaseGroup(int x,int y,const char* t);
	~BaseGroup();

	Fl_Input* createInput(const char* value, const char* labelName, bool active);

	Fl_Button* createCenterButton(const char* text);
private:

	int controlY;
	int maskY;
	

};
