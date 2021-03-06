#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <windows.h>

#define PRINT_LOGS true
#define NO_LOGS false
#define IS_SUPPORTED_POSITION	8

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
	char recvBuff[255];
	char sendBuff[255] = "Get the seconds since the beginning of the month";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << recvBuff << " seconds had passed since the beginning of the month." << endl;
}

void GetWeekOfYear(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the week of year";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The week of year is: " << recvBuff << endl;
}

void GetDaylightSavings(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the daylight savings status";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << "The daylight savings status is " << recvBuff << endl;
}

void GetTimeWithoutDateInCity(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Get the time in city";

	char cityBuff[100];
	cout << "Please type the city name:\n";
	cin.get();
	cin.getline(cityBuff, sizeof(cityBuff));

	// Turn input city to lowercase letters
	for (int i = 0; cityBuff[i]; i++) {
		cityBuff[i] = tolower(cityBuff[i]);
	}
	
	// Add the city as a second string in the message
	int lenOfMessage = strlen("Get the time in city");
	strcpy_s(sendBuff + lenOfMessage, 255 - lenOfMessage, cityBuff);

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);

	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	if (recvBuff[IS_SUPPORTED_POSITION] == '1')
	{
		recvBuff[IS_SUPPORTED_POSITION] = '\0';
		cout << "The time in " << cityBuff << " is: " << recvBuff << endl;

	}
	else
	{
		recvBuff[IS_SUPPORTED_POSITION] = '\0';
		cout << "The city is not supported! The UTC time is: " << recvBuff << endl;
	}
}

void MeasureTimeLap(SOCKET connSocket, sockaddr_in server)
{
	char recvBuff[255];
	char sendBuff[255] = "Measure Time Lap";

	sendTimeMessage(connSocket, server, sendBuff, PRINT_LOGS);
	receiveTimeMessage(connSocket, recvBuff, PRINT_LOGS);
	cout << recvBuff << endl;
}
