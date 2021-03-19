#include "SqlService.h"

SqlService::SqlService()
{
}

SqlService::~SqlService()
{
}

string SqlService::ProcessSqlQuery(const string& connectionString, const string& sqlQuerty, bool& mistake)
{
	vector<map<string, string>> vector_result;

	try
	{
		connection conn(connectionString);
		result result = execute(conn, sqlQuerty);
		short const col = result.columns();

		while (result.next())
		{
			map<string, string> map_result;

			for (short i = 0; i < col; i++)
			{
				string col_name = result.column_name(i);
				string res = result.get<string>(i);

				map_result.insert(make_pair(col_name, res));
				
			}

			vector_result.push_back(map_result);
		}

	}
	catch (const exception& e)
	{
		mistake = true;
		return e.what();
	}

	string str_result = GetJsonString(vector_result);

	return str_result;
}

string SqlService::GetJsonString(vector<map<string, string>>& vectorResponse)
{
	string str_array;
	int a = 1;
	str_array += '[';
	for (map<string, string> it_vector : vectorResponse)
	{
		string struct_map;
		int s = 1;
		struct_map += '{';
		for (const auto& it : it_vector)
		{
			struct_map += '"' + it.first + '"' + " : " + '"' + it.second + '"';
			struct_map += (it_vector.size() != s) ? "," : "";
			s++;
		}
		struct_map += '}';
		str_array += struct_map;
		str_array += (vectorResponse.size() != a) ? "," : "";
		a++;
	}
	str_array += ']';
	return str_array;
}