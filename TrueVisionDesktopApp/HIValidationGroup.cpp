#include "stdafx.h"
#include "HIValidationGroup.h"


HIValidationGroup::HIValidationGroup(int x, int y, const char* t): Fl_Group(x, y, 400, 300, t)
{
	this->initializeComponent();
}

HIValidationGroup::~HIValidationGroup()
{
}

void HIValidationGroup::initializeComponent()
{
	this->activationKeyLabel = new Fl_Box(this->x() + 10, this->y() + 20, 50, 30, "Activation Key:");
	this->activationKeyLabel->align(FL_ALIGN_POSITION_MASK);
	this->activationKeyInput = new Fl_Input(this->x() + 10, this->y() + 20, this->w(), 30);

	this->hardwareKeyLabel = new Fl_Box(this->x() + 10, this->y() + 140, 50, 30, "Hardware Key:");
	this->hardwareKeyLabel->align(FL_ALIGN_POSITION_MASK);
	this->hardwareKeyInput = new Fl_Input(this->x() + 10, this->y() + 80, this->w(), 30);

	this->productIdLabel = new Fl_Box(this->x() + 10, this->y() + 260, 50, 30, "Product Id:");
	this->productIdLabel->align(FL_ALIGN_POSITION_MASK);
	this->productIdInput = new Fl_Input(this->x() + 10, this->y() + 140, this->w(), 30);

	this->validateButton = new Fl_Button(this->x() + 150, this->y() + 190, 100, 30, "Validate");
	//this->registerButton->callback(registerButtonCallback, (void*)this);
	this->end();
}