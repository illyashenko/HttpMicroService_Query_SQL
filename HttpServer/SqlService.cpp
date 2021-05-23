#include "SqlService.h"

SqlService::SqlService(){}
SqlService::~SqlService(){}

string SqlService::GetListData(result& results)
{
	short const column = results.columns();
	picojson::array list_;

	while (results.next())
	{
		picojson::object map_;
		for (short i = 0; i < column; i++)
		{
			string key = results.column_name(i);
			string val = results.get<string>(i);
			picojson::value strVal(val);
			map_.emplace(key, strVal);
		}
		picojson::value valMap(map_);
		list_.push_back(valMap);
	}
	picojson::value res(list_);
	string str_rez = res.serialize();

	return str_rez;
}

string SqlService::ProcessSqlQuery(const string& connectionString, const string& sqlQuerty, bool& mistake)
{
	string str_result;

	try
	{
		connection conn(connectionString);
		result results = execute(conn, sqlQuerty);
		string vector_result = GetListData(results);
	}
	catch (const exception& exception_)
	{
		mistake = true;
		return exception_.what();
	}
	return str_result;
}

