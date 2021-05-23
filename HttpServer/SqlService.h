#pragma once

#include <iostream>
#include <map>
#include <nanodbc/nanodbc.h>
#include <picojson/picojson.h>

using namespace std;
using namespace nanodbc;

class SqlService
{
public:
	SqlService();
	~SqlService();

	string ProcessSqlQuery(const string& connectionString, const string& sqlQuerty, bool& mistake);

private:
	string GetListData(result& results);
};
