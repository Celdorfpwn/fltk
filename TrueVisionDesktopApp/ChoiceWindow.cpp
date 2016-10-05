#include "stdafx.h"
#include "ChoiceWindow.h"
#include "HardwareIndependent.h"




ChoiceWindow* ChoiceWindow::instance;


ChoiceWindow::ChoiceWindow() : Fl_Window(300, 100, "Choose Product Type")
{
	this->initializeComponent();
}

ChoiceWindow::~ChoiceWindow()
{
	Fl_Window::~Fl_Window();
}

ChoiceWindow* ChoiceWindow::Instance()
{
	if (!ChoiceWindow::instance)
	{
		ChoiceWindow::instance = new ChoiceWindow();
	}

	return ChoiceWindow::instance;
}

void ChoiceWindow::initializeComponent()
{
	this->hdProductButton = new Fl_Button(10, 10, 280, 30, "Hardware Dependent");
	this->hiProductButton = new Fl_Button(10, 50, 280, 30, "Hardware Independent");

	this->hdProductButton->callback(hdProductButtonCallback);
	this->hiProductButton->callback(hiProductButtonCallback);
	this->end();
}

void ChoiceWindow::hdProductButtonCallback(Fl_Widget *widget, void*)
{
	Fl_Window *window = HardwareDependentWindow::Instance();
	window->show();
}
void ChoiceWindow::hiProductButtonCallback(Fl_Widget *widget, void*)
{
	Fl_Window *window = HardwareIndependentWindow::Instance();
	window->show();
}



