#include "IServer.h"

vector<AppSettings> vector_users;

HttpServer::HttpServer() : port_(0) {}
HttpServer::~HttpServer() {}

int GetAuth(const string& login, const string& pass) 
{
	auto numAppCount = boolinq::from(vector_users).
		where([&](const AppSettings& appSetting)
			      { return appSetting.login == login && appSetting.pass == pass;
			      }).count();

	return numAppCount;
}

void FillConnectionData(json& j, string& connectionString, string& stringRequest)
{
	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		if (it.key() == "ConnectionString") { connectionString = it.value(); }
		if (it.key() == "StringRequest") { stringRequest = it.value(); }
	}
}

void Controller_api(const Request& req, Response& res)
{
	bool mistake = false;
	auto j = json::parse(req.body);

	//*****authorization*******
	string login = req.get_param_value("log");
	string pass = req.get_param_value("pass");

	if (GetAuth(login, pass) == 0)
	{
		res.status = 401;
		return;
	}
	//**********************//

	string connectionString;
	string stringRequest;

	FillConnectionData(j, connectionString, stringRequest);

	if (connectionString == "" || stringRequest == "")
	{
		res.status = 400;
		return;
	}

	SqlService sqlService;

	string listData = sqlService.ProcessSqlQuery(connectionString, stringRequest, mistake);

	if (mistake) { res.status = 404; }

	res.set_header("Content-Type", "application/json; charset=Windows-1251");
	res.body = listData;

}

void HttpServer::Start()
{
	Server serv;
	serv.Post("/", Controller_api);

	string path = GetPath();
	int port = GetPort();

	serv.listen(path.c_str(), port);
}

void HttpServer::FillAppSetting()
{
	pugi::xml_document doc;
	doc.load_file(L"..\\API.SQL.version\\ServerSettings.xml");

	for (pugi::xml_node el : doc.child("Users").children("user"))
	{
		AppSettings app;

		app.login = el.attribute("login").value();
		app.pass = el.attribute("pass").value();

		vector_users.push_back(app);
	}

	for (pugi::xml_node el : doc.child("Users").children("ServerPath"))
	{
		string path = el.attribute("path").value();
		string port_str = el.attribute("port").value();
		int port = stoi(port_str);

		SetServerPath(path);
		SetServerPort(port);
	}
}

string HttpServer::GetPath() { return path_; }
int HttpServer::GetPort() { return port_; }
void HttpServer::SetServerPath(string path) { this->path_ = path; }
void HttpServer::SetServerPort(int port) { this->port_ = port; }
