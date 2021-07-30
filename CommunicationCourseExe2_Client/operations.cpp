#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>

void SendTimeMessage(SOCKET connSocket, sockaddr_in server, char message[])
{
	// Send and receive data.

	int bytesSent = 0;
	char sendBuff[255];

	strcpy_s(sendBuff, message);

	// Asks the server what's the currnet time.
	// The send function sends data on a connected socket.
	// The buffer to be sent and its size are needed.
	// The fourth argument is an idicator specifying the way in which the call is made (0 for default).
	// The two last arguments hold the details of the server to communicate with. 
	// NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
	bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
}

void ReceiveTimeMessage(SOCKET connSocket, char recvBuff[])
{
	int bytesRecv = 0;

	// Gets the server's answer using simple recieve (no need to hold the server's address).
	bytesRecv = recv(connSocket, recvBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
}

void GetTime(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	SendTimeMessage(connSocket, server, "Get the time");
	ReceiveTimeMessage(connSocket, recvBuff);
	cout << "The time is: " << recvBuff << endl;
}

void GetTimeWithoutDate(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	SendTimeMessage(connSocket, server, "Get the time without date");
	ReceiveTimeMessage(connSocket, recvBuff);
	cout << "The time is: " << recvBuff << endl;
}

void GetTimeSinceEpoch(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	SendTimeMessage(connSocket, server, "Get the time since epoch");
	ReceiveTimeMessage(connSocket, recvBuff);
	cout << "The time since epoch is: " << recvBuff << endl;
}

void GetClientToServerDelayEstimation(SOCKET connSocket, sockaddr_in server)
{
	for (int i = 0; i < 100; i++)
	{
		SendTimeMessage(connSocket, server, "Get the time in ticks");
	}

	char recvBuff[255];
	int delaySum = 0;
	int currTime;

	ReceiveTimeMessage(connSocket, recvBuff);
	int lastTime = atoi(recvBuff);
	for (int i = 0; i < 99; i++)
	{
		ReceiveTimeMessage(connSocket, recvBuff);
		currTime = atoi(recvBuff);
		delaySum += (currTime - lastTime);
		lastTime = currTime;
	}
	cout << "The client-server delay estimation is: " << delaySum / 100. << endl;
}

void MeasureRTT(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetTimeWithoutDateOrSeconds(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetYear(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetMonthAndDay(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetSecondsSinceBeginingOfMonth(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetWeekOfYear(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetDaylightSavings(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void GetTimeWithoutDateInCity(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}

void MeasureTimeLap(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
}
