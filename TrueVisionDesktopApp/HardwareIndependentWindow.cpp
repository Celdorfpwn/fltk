#include "stdafx.h"
#include "HardwareIndependentWindow.h"

HardwareIndependentWindow* HardwareIndependentWindow::instance;
void registrationButtonCallback(Fl_Widget *widgent, void* data);

HardwareIndependentWindow::HardwareIndependentWindow() : Fl_Window(490, 500, "Hardware Independent Product")
{
	this->initializeComponent();
}

HardwareIndependentWindow::~HardwareIndependentWindow()
{
}

HardwareIndependentWindow* HardwareIndependentWindow::Instance()
{
	if (!HardwareIndependentWindow::instance)
	{
		HardwareIndependentWindow::instance = new HardwareIndependentWindow();
	}

	return HardwareIndependentWindow::instance;
}

void HardwareIndependentWindow::initializeComponent()
{
	this->registrationButton = new Fl_Button(10, 10, 150, 30, "Registration");

	this->registrationButton->callback(registrationButtonCallback, (void*)this);

	this->validationButton = new Fl_Button(170, 10, 150, 30, "Validation");
	this->verifyButton = new Fl_Button(330, 10, 150, 30, "Verify");
	this->end();
}

void HardwareIndependentWindow::addRegistrationForm()
{
	this->begin();
	HIRegistrationGroup *testBox = new HIRegistrationGroup(50, 100, "Registration Form");
	this->end();
	this->redraw();
}


void registrationButtonCallback(Fl_Widget *widgent, void* data)
{
	HardwareIndependentWindow* window = (HardwareIndependentWindow*)data;
	window->addRegistrationForm();
}