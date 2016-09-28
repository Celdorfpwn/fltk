#pragma once
#include "stdafx.h"


class ChoiceWindow : public Fl_Window
{
public:
	static ChoiceWindow* Instance();
	~ChoiceWindow();

private:
	ChoiceWindow();

	Fl_Button* hdProductButton;
	Fl_Button* hiProductButton;
	static ChoiceWindow* instance;

	static void hdProductButtonCallback(Fl_Widget *widget, void*);
	static void hiProductButtonCallback(Fl_Widget *widget, void*);

	void initializeComponent();
};