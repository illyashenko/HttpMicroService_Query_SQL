#pragma once

#include <iostream>
#include <map>
#include <nanodbc/nanodbc.h>

using namespace std;
using namespace nanodbc;

class SqlService
{
public:
	SqlService();
	~SqlService();

	string ProcessSqlQuery(const string& connectionString, const string& sqlQuerty, bool& mistake);

private:
	vector<map<string, string>> GetListData(result& results);
	string GetJsonString(vector<map<string, string>>& vectorResponse);

};
