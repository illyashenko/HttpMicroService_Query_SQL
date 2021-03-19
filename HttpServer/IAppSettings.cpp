#include "IAppSettings.h"

AppSettings::AppSettings()
{
}

AppSettings::AppSettings(string login, string pass)
{
	this->login = login;
	this->pass = pass;
}

AppSettings::~AppSettings()
{
}

bool AppSettings::operator == (AppSettings app)
{
	if (this->login == app.login && this->pass == app.pass)
		return true;

	return false;
}

bool AppSettings::operator != (AppSettings app)
{
	if (this->login != app.login && this->pass != app.pass)
		return true;

	return false;
}