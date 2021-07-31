#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <windows.h>

#define PRINT_LOGS true
#define NO_LOGS false

void sendTimeMessage(SOCKET connSocket, sockaddr_in server, char readySendBuff[], bool printLogs)
{
	// Send and receive data.

	int bytesSent = 0;

	// Asks the server what's the currnet time.
	// The send function sends data on a connected socket.
	// The buffer to be sent and its size are needed.
	// The fourth argument is an idicator specifying the way in which the call is made (0 for default).
	// The two last arguments hold the details of the server to communicate with. 
	// NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
	bytesSent = sendto(connSocket, readySendBuff, (int)strlen(readySendBuff), 0, (const sockaddr *)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}
	if (printLogs)
		cout << "Time Client: Sent: " << bytesSent << "/" << strlen(readySendBuff) << " bytes of \"" << readySendBuff << "\" message.\n";
}

void receiveTimeMessage(SOCKET connSocket, char recvBuff[], bool printLogs)
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
	if (printLogs)
		cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
}

void GetTime(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the time";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The time is: " << recvBuff << endl;
}

void GetTimeWithoutDate(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the time without date";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The time is: " << recvBuff << endl;
}

void GetTimeSinceEpoch(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the time since epoch";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The time in seconds since epoch is: " << recvBuff << endl;
}

void GetClientToServerDelayEstimation(SOCKET connSocket, sockaddr_in server)
{
	char sendBuff[255] = "Get the time in ticks";
	for (int i = 0; i < 100; i++)
	{
		sendTimeMessage(connSocket, server, sendBuff, NO_LOGS);
	}

	char recvBuff[255];
	int delaySum = 0;
	int currTime;

	receiveTimeMessage(connSocket, recvBuff, NO_LOGS);
	int lastTime = atoi(recvBuff);
	for (int i = 0; i < 99; i++)
	{
		receiveTimeMessage(connSocket, recvBuff, NO_LOGS);
		currTime = atoi(recvBuff);
		delaySum += (currTime - lastTime);
		lastTime = currTime;
	}
	cout << "The client-server delay estimation is: " << delaySum / 100. << endl;
}

void MeasureRTT(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the time in ticks";
	int rttSum = 0;
	int before;
	int after;

	for (int i = 0; i < 100; i++)
	{
		before = GetTickCount();
		sendTimeMessage(connSocket, server, sendBuff, NO_LOGS);
		receiveTimeMessage(connSocket, recvBuff, NO_LOGS);
		after = GetTickCount();
		rttSum += (after - before);
	}
	cout << "The measured RTT is: " << rttSum / 100. << endl;
}

void GetTimeWithoutDateOrSeconds(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the time without date or seconds";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The time is: " << recvBuff << endl;
}

void GetYear(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the year";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The year is: " << recvBuff << endl;
}

void GetMonthAndDay(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the month and day";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The month and day are: " << recvBuff << endl;
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
