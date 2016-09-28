#pragma once
#include "stdafx.h"

class HIValidationGroup : public Fl_Group
{
public:
	HIValidationGroup(int x, int y, const char* t);
	~HIValidationGroup();

private:

	Fl_Box* activationKeyLabel;
	Fl_Box* hardwareKeyLabel;
	Fl_Box* productIdLabel;

	Fl_Input* activationKeyInput;
	Fl_Input* hardwareKeyInput;
	Fl_Input* productIdInput;

	Fl_Button* validateButton;

	void initializeComponent();
};