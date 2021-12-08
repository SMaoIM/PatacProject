
#include <stdio.h> 
#include <winsock2.h> 

#pragma comment(lib,"ws2_32.lib")  
#pragma warning(disable:4996)
#include "viRDBIcd.h"

typedef struct
{
    RDB_MSG_HDR_t           hdr;              
    RDB_MSG_ENTRY_HDR_t     entrySOF;    
    RDB_MSG_ENTRY_HDR_t     entrydrivercontrol;
    RDB_DRIVER_CTRL_t       drivercontrol;
    /*
    RDB_MSG_ENTRY_HDR_t     entryObjectState; 
    RDB_OBJECT_STATE_t      objectState;
    RDB_MSG_ENTRY_HDR_t     entryWheelState; 
    RDB_WHEEL_BASE_t        wheelState[4];
    RDB_MSG_ENTRY_HDR_t     entryEngine; 
    RDB_ENGINE_BASE_t       engine;
    RDB_MSG_ENTRY_HDR_t     entryDrivetrain; 
    RDB_DRIVETRAIN_BASE_t   drivetrain;
    RDB_MSG_ENTRY_HDR_t     entryVehicleSystems; 
    RDB_VEHICLE_SYSTEMS_t   vehicleSystems;
    */
    RDB_MSG_ENTRY_HDR_t     entryEOF;
} MY_RDB_MSG_t;

MY_RDB_MSG_t driver_ctrl;

int main(int argc, char* argv[])
{
	unsigned int  bytesInBuffer = 0;
	size_t        bufferSize = sizeof(MY_RDB_MSG_t);
	unsigned int  count = 0;
	unsigned char *pData = (unsigned char*)calloc(1, bufferSize);

	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//server receive, 127.0.0.1:7770
	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//client send, 192.168.1.118:8890 
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (serSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//server
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(7770);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//client
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8890);
	sin.sin_addr.S_un.S_addr = inet_addr("192.168.1.118");
	int len = sizeof(sin);

	if (bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(serSocket);
		return 0;
	}

	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	while (true)
	{
		char recvData[255];
		printf("***********receriving**************************\n");
		int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);

		//printf("ret is %d\n",ret);
		if (ret > 0)
		{
			// do we have to grow the buffer??
			if ((bytesInBuffer + ret) > bufferSize)
			{
				pData = (unsigned char*)realloc(pData, bytesInBuffer + ret);
				bufferSize = bytesInBuffer + ret;
				//printf("********************************************************************\n");
			}

			memmove(pData , recvData, ret);
			bytesInBuffer += ret;
			//printf("bytesInBuffer is %d\n", bytesInBuffer);
			// already complete messagae?
			if (bytesInBuffer >= sizeof(MY_RDB_MSG_t))
			{
				MY_RDB_MSG_t* hdr = (MY_RDB_MSG_t*)pData;
				printf("sim time is %f\n",hdr->hdr.simTime);
				printf("playerID is: %lu,\tsteeringWheel is %f,\tvalidityFlags is %lu\n",hdr->drivercontrol.playerId,hdr->drivercontrol.steeringWheel,hdr->drivercontrol.validityFlags);
				

			
				/*
				// is this message containing the valid magic number?
				if (hdr->magicNo != RDB_MAGIC_NO)
				{
					printf("message receiving is out of sync; discarding data");
					bytesInBuffer = 0;
				}
				*/

			//recvData[ret] = 0x00;
			//printf("接收到来自%s的信息 \r\n", inet_ntoa(remoteAddr.sin_addr));
			bytesInBuffer = 0;

			const char * sendData = (char *)&hdr;
			printf("send data is: %u,\t%f,\t,%u\n", hdr->drivercontrol.playerId,hdr->drivercontrol.steeringWheel,hdr->drivercontrol.validityFlags);
			printf("****************end*****************\n\n");
			sendto(sclient, sendData, bufferSize, 0, (sockaddr *)&sin, len);
			}


			//printf(recvData);
		}
		/*
		const char * sendData = "һ�����Է���˵�UDPi���ݰ�";
		printf("len is %d",strlen(sendData));
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
		*/
	}
	closesocket(serSocket);
	WSACleanup();
	return 0;
}
