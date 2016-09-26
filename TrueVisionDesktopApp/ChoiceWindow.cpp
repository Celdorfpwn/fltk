#include "stdafx.h"
#include "ChoiceWindow.h"
#include "HardwareIndependentWindow.h"

void hdProductButtonCallback(Fl_Widget *widget, void*);
void hiProductButtonCallback(Fl_Widget *widget, void*);


ChoiceWindow* ChoiceWindow::instance;


ChoiceWindow::ChoiceWindow(): Fl_Window(300,100,"Choose Product Type")
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

void hdProductButtonCallback(Fl_Widget *widget, void*)
{

}
void hiProductButtonCallback(Fl_Widget *widget, void*)
{
	Fl_Window *window = new HardwareIndependentWindow();
	window->show();
}



