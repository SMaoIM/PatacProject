
#include <stdio.h> 
#include <winsock2.h> 
#include <iostream>
using namespace std;
#include "vtd_def.h"

#pragma comment(lib,"ws2_32.lib")  
#pragma warning(disable:4996)
RDB_DRIVER_CTRL_t driver_ctrl;
#define default_buffer_size 255

int main(int argc, char* argv[])
{
	size_t        bufferSize = sizeof(RDB_DRIVER_CTRL_t);

	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		return 0;
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int len = sizeof(sin);
	while(1)
	{
		
		cout<<"input playerId"<<endl;
		cin>>driver_ctrl.playerId;
		cout<<"input steeringWheel"<<endl;
		cin>>driver_ctrl.steeringWheel;
		cout<<"input validityFlags"<<endl;
		cin>>driver_ctrl.validityFlags;
		
		const char * sendData = (char *) &driver_ctrl;
		/*
		printf("driver data is %s\n", sendData);
		printf("playerId %lu\t", driver_ctrl.playerId);
		printf("steeringWheel %f\t", driver_ctrl.steeringWheel);
		printf("validityFlags %lu\n", driver_ctrl.validityFlags);
		*/
		sendto(sclient, sendData, bufferSize, 0, (sockaddr *)&sin, len);
		/*
		char recvData[default_buffer_size];
		int ret = recvfrom(sclient, recvData, default_buffer_size, 0, (sockaddr *)&sin, &len);
		printf("ret is %d\n",ret);
		if (ret > 0)
		{
			recvData[ret] = 0x00;
			printf(recvData);
			printf("\n");
		}
		*/
		printf("*****************************************************\n");
	}

	closesocket(sclient);
	WSACleanup();
	return 0;
}
