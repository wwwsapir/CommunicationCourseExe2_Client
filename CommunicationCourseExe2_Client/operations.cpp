#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>

void SendMessage(SOCKET connSocket, sockaddr_in server, char message[])
{
	// Send and receive data.

	int bytesSent = 0;
	int bytesRecv = 0;
	char sendBuff[255];
	char recvBuff[255];

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
	SendMessage(connSocket, server, "Get the time");
}

void GetTimeWithoutDate(SOCKET connSocket, sockaddr_in server)
{
	SendMessage(connSocket, server, "Get the time without date");
}

void GetTimeSinceEpoch(SOCKET connSocket, sockaddr_in server)
{
	SendMessage(connSocket, server, "Get the time since epoch");
}

void GetClientToServerDelayEstimation(SOCKET connSocket, sockaddr_in server)
{
	cout << "Not Implemented!";
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
