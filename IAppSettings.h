#pragma once
#include <iostream>

using namespace std;

struct AppSettings
{
	AppSettings();
	AppSettings(string login, string pass);
	~AppSettings();

	bool operator == (AppSettings app);
	bool operator != (AppSettings app);

	string login;
	string pass;
};
