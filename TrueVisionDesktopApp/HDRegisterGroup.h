#pragma once
#include "stdafx.h"

class HDRegisterGroup : public Fl_Group
{
public:
	HDRegisterGroup(int x,int y,const char* t);
	~HDRegisterGroup();

private:

	void initializeComponent();
};