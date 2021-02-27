#pragma once
#include <iostream>
#include <map>
#include <httplib.h>
#include <pugixml.hpp>
#include <nlohmann/json.hpp>
#include "IServiceSQL.h"
#include "IAppSettings.h"
#include <boolinq/boolinq.h>

using namespace httplib;
using namespace std;

using json = nlohmann::json;

class HttpServer
{
public:
	HttpServer();
	~HttpServer();
	void Start();
	void FillAppSetting();
	string GetPath();
	int GetPort();
	void SetServerPath(string path);
	void SetServerPort(int port);

private:
	string path_;
	int port_;
};
