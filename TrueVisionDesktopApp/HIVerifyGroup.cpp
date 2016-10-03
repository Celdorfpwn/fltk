#include "stdafx.h"
#include "HIVerifyGroup.h"

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace pplx;

HIVerifyGroup::HIVerifyGroup(int x, int y, const char* t) : Fl_Group(x, y, 400, 400, t)
{
	this->initializeComponent();
	this->initializeInputsValues();
}

HIVerifyGroup ::~HIVerifyGroup()
{
}

void HIVerifyGroup::initializeComponent()
{
	this->userInfoIdLabel = new Fl_Box(this->x() + 10, this->y() + 20, 50, 30, "User Id:");
	this->userInfoIdLabel->align(FL_ALIGN_POSITION_MASK);
	this->userInfoInput = new Fl_Input(this->x() + 10, this->y() + 20, this->w(), 30);
	this->userInfoInput->deactivate();

	this->hardwareKeyLabel = new Fl_Box(this->x() + 10, this->y() + 140, 50, 30, "Hardware Key:");
	this->hardwareKeyLabel->align(FL_ALIGN_POSITION_MASK);
	this->hardwareKeyInput = new Fl_Input(this->x() + 10, this->y() + 80, this->w(), 30);
	this->hardwareKeyInput->deactivate();

	this->productIdLabel = new Fl_Box(this->x() + 10, this->y() + 260, 50, 30, "Product Id:");
	this->productIdLabel->align(FL_ALIGN_POSITION_MASK);
	this->productIdInput = new Fl_Input(this->x() + 10, this->y() + 140, this->w(), 30);
	this->productIdInput->deactivate();

	this->licenseIdLabel = new Fl_Box(this->x() + 10, this->y() + 380, 50, 30, "License Id:");
	this->licenseIdLabel->align(FL_ALIGN_POSITION_MASK);
	this->licenseIdInput = new Fl_Input(this->x() + 10, this->y() + 200, this->w(), 30);
	this->licenseIdInput->deactivate();

	this->licenseKeyLabel = new Fl_Box(this->x() + 10, this->y() + 500, 50, 30, "License Key:");
	this->licenseKeyLabel->align(FL_ALIGN_POSITION_MASK);
	this->licenseKeyInput = new Fl_Input(this->x() + 10, this->y() + 260, this->w(), 30);
	this->licenseKeyInput->deactivate();

	this->verifyButton = new Fl_Button(this->x() + 150, this->y() + 310, 100, 30, "Verify");
	this->verifyButton->callback(this->verifyButtonCallback, (void*)this);

	this->end();
}

void HIVerifyGroup::initializeInputsValues()
{
	this->userInfoInput->value(HILicenseFileReader::Instance()->getUserInfoId().c_str());
	this->hardwareKeyInput->value(Configuration::Instance()->getDefaultHardwareId().c_str());
	this->productIdInput->value(Configuration::Instance()->getDefaultProductId().c_str());
	this->licenseIdInput->value(HILicenseFileReader::Instance()->getLicenseId().c_str());
	this->licenseKeyInput->value(HILicenseFileReader::Instance()->getLicenseKey().c_str());
}

void HIVerifyGroup::verifyButtonCallback(Fl_Widget *widget, void* data)
{
	HIVerifyGroup *group = (HIVerifyGroup*)data;
	try
	{
		group->getRequestTask().wait();
		group->showMessage();
	}
	catch (const std::exception &e)
	{
		fl_alert(e.what());
	}
}

task<void> HIVerifyGroup::getRequestTask()
{
	return create_task([&]
	{
		http_client client(conversions::to_string_t(Configuration::Instance()->getServerUrl()));
		uri_builder builder = uri_builder(U("api"));
		builder.append(U("external"));
		builder.append(U("checkProductLicense"));


		json::value body;
		body[L"UserInfoId"] = json::value::string(conversions::to_string_t(this->userInfoInput->value()));
		body[L"HardwareKey"] = json::value::string(conversions::to_string_t(this->hardwareKeyInput->value()));
		body[L"ProductId"] = json::value::string(conversions::to_string_t(this->productIdInput->value()));
		body[L"LicenseId"] = json::value::string(conversions::to_string_t(this->licenseIdInput->value()));
		body[L"LicenseKey"] = json::value::string(conversions::to_string_t(this->licenseKeyInput->value()));



		return client.request(methods::POST, builder.to_string(),body);
	}).then([&](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			this->messageType = Info;
			this->messageResult = "Valid licese";
		}
		else
		{
			this->messageResult = "Invalid license";
			this->messageType = Error;
		}
	});
}

void HIVerifyGroup::showMessage()
{
	switch (this->messageType)
	{
	case Info: fl_message(this->messageResult.c_str()); break;
	case Error: fl_alert(messageResult.c_str()); break;
	}
}