#include "stdafx.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_ask.H>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>


using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

Fl_Box* CreateLabel(int x, int y, char* text);
Fl_Input* CreateInput(int x, int y);
Fl_Button* CreateButton(int x, int y, char* text);
void buttonCallBack(Fl_Widget *widget, void*);
pplx::task<void> GetAll();

int col1 = 0;
int col2 = 150;
int row1 = 10;
int row2 = 40;



Fl_Input *usernameInput;
Fl_Input *emailInput;
Fl_Box *result;
string text;
Fl_Button *requestButton;


Fl_Window* Create()
{
	Fl_Window *window = new Fl_Window(500, 300);

	CreateLabel(col1, row1, "Username");
	CreateLabel(col1, row2, "Email");
	usernameInput = CreateInput(col2, row1);
	emailInput = CreateInput(col2, row2);

	requestButton = CreateButton(200, 100, "Register");

	result = new Fl_Box(10, 200, 400, 30, "");
	result->box(FL_UP_BOX);
	window->end();

	requestButton->callback(buttonCallBack);
	return window;
}

Fl_Box* CreateLabel(int x, int y, char* text)
{
	Fl_Box *box = new Fl_Box(x, y, 50, 30, text);
	box->box(FL_NO_BOX);
	box->align(FL_ALIGN_RIGHT);
	return box;
}

Fl_Input* CreateInput(int x, int y)
{
	Fl_Input *input = new Fl_Input(x, y, 300, 30);
	return input;
}

Fl_Button* CreateButton(int x, int y, char* text)
{
	Fl_Button *button = new Fl_Button(x, y, 100, 30, text);
	return button;
}

void buttonCallBack(Fl_Widget *widget, void*)
{
	GetAll().wait();
}

pplx::task<void> GetAll()
{
	return pplx::create_task([]
	{
		string_t url = string_t(conversions::to_string_t("test?username=")) +
			conversions::to_string_t(string(usernameInput->value())) +
			conversions::to_string_t(string("&email=")) +
			(conversions::to_string_t(string(emailInput->value())));
		http_client client(L"http://localhost:28652");

		uri_builder builder = uri_builder(U("api"));
		builder.append(url);

		return client.request(methods::GET, builder.to_string());
	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		return pplx::create_task([] { return json::value(); });

	}).then([](json::value jsonValue)
	{
		if (jsonValue.is_null())
			return;

		text = conversions::to_utf8string(jsonValue.serialize());

		result->label(text.c_str());
		result->redraw();
	});
}