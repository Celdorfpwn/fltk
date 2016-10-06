#include "stdafx.h"

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace pplx;

HIVerifyGroup::HIVerifyGroup(int x, int y, const char* t) : BaseGroup(x, y, t)
{
	this->initializeComponent();
}

HIVerifyGroup ::~HIVerifyGroup()
{
}

void HIVerifyGroup::initializeComponent()
{
	this->userInfoInput = BaseGroup::createInput(HILicenseFileReader::Instance()->getUserInfoId().c_str(), "User Id:", false);
	this->hardwareKeyInput = BaseGroup::createInput(Configuration::Instance()->HIHardwareId().c_str(), "Hardware Key", false);
	this->productIdInput = BaseGroup::createInput(Configuration::Instance()->HIProductId().c_str(), "Product Id:", false);
	this->licenseIdInput = BaseGroup::createInput(HILicenseFileReader::Instance()->getLicenseId().c_str(), "License Id:", false);
	this->licenseKeyInput = BaseGroup::createInput(HILicenseFileReader::Instance()->getLicenseKey().c_str(), "License Key:", false);

	this->verifyButton = BaseGroup::createCenterButton("Verify");
	this->verifyButton->callback(this->verifyButtonCallback, (void*)this);
	this->end();
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
		http_client client(conversions::to_string_t(Configuration::Instance()->ServerUrl()));
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