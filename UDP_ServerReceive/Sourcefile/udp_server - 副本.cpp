
#include <stdio.h> 
#include <winsock2.h> 

#pragma comment(lib,"ws2_32.lib")  
#pragma warning(disable:4996)
#include "vtd_def.h"

int main(int argc, char* argv[])
{
	unsigned int  bytesInBuffer = 0;
	size_t        bufferSize = sizeof(RDB_DRIVER_CTRL_t);
	unsigned int  count = 0;
	unsigned char *pData = (unsigned char*)calloc(1, bufferSize);

	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(serSocket);
		return 0;
	}

	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	printf("start connecting\n");
	while (true)
	{
		char recvData[255];
		int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);

		printf("ret is %d\n",ret);
		if (ret > 0)
		{
			// do we have to grow the buffer??
			if ((bytesInBuffer + ret) > bufferSize)
			{
				pData = (unsigned char*)realloc(pData, bytesInBuffer + ret);
				bufferSize = bytesInBuffer + ret;
				printf("********************************************************************\n");
			}

			memmove(pData , recvData, ret);
			bytesInBuffer += ret;
			printf("bytesInBuffer is %d\n", bytesInBuffer);
			// already complete messagae?
			if (bytesInBuffer >= sizeof(RDB_DRIVER_CTRL_t))
			{
				RDB_DRIVER_CTRL_t* hdr = (RDB_DRIVER_CTRL_t*)pData;
				printf("playerID is: %lu,\tsteeringWheel is %f,\tvalidityFlags is %lu\t",hdr->playerId,hdr->steeringWheel,hdr->validityFlags);
			}
				/*
				// is this message containing the valid magic number?
				if (hdr->magicNo != RDB_MAGIC_NO)
				{
					printf("message receiving is out of sync; discarding data");
					bytesInBuffer = 0;
				}
				*/

			//recvData[ret] = 0x00;
			printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
			bytesInBuffer = 0;
			//printf(recvData);
		}
		/*
		const char * sendData = "一个来自服务端的UDPi数据包";
		printf("len is %d",strlen(sendData));
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
		*/
	}
	closesocket(serSocket);
	WSACleanup();
	return 0;
}
