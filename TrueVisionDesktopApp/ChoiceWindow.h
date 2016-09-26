#pragma once
#include "stdafx.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>


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

	void initializeComponent();
};