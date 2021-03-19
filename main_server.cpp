#include <iostream>
#include "HttpServer/IServer.h"


int main(int argc, char* argv[]) 
{
	
	HttpServer* httpServer = new HttpServer();
	httpServer->FillAppSetting();
	httpServer->Start();

	return 0;
}