#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include "operations.h"

#define TIME_PORT	27015
#define EXIT	0

void RunInputLoop(SOCKET connSocket, sockaddr_in server)
{
	int input = -1;
	while (input != EXIT)
	{
		cout << "Please choose an action:" << endl;
		cout << "0. Exit" << endl;
		cout << "1. Get the time." << endl;
		cout << "2. Get the time without date." << endl;
		cout << "3. Get the time since epoch." << endl;
		cout << "4. Get the client to server delay estimation." << endl;
		cout << "5. Get round trip time measure." << endl;
		cout << "6. Get the time without date or seconds." << endl;
		cout << "7. Get the year." << endl;
		cout << "8. Get the month and the day." << endl;
		cout << "9. Get the seconds since the beginning of the month." << endl;
		cout << "10. Get the week of the year." << endl;
		cout << "11. Get the daylight savings status." << endl;
		cout << "12. Get the time without date in a specific city." << endl;
		cout << "13. Measure the time lap." << endl;
		cin >> input;
		if (input < 0 || input > 13)
		{
			cout << "The input is invalid. Please enter a number from 0 to 13.";
		}
		else
		{
			switch (input)
			{
			case 1:
				GetTime(connSocket, server);
				break;
			case 2:
				GetTimeWithoutDate(connSocket, server);
				break;
			case 3:
				GetTimeSinceEpoch(connSocket, server);
				break;
			case 4:
				GetClientToServerDelayEstimation(connSocket, server);
				break;
			case 5:
				MeasureRTT(connSocket, server);
				break;
			case 6:
				GetTimeWithoutDateOrSeconds(connSocket, server);
				break;
			case 7:
				GetYear(connSocket, server);
				break;
			case 8:
				GetMonthAndDay(connSocket, server);
				break;
			case 9:
				GetSecondsSinceBeginingOfMonth(connSocket, server);
				break;
			case 10:
				GetWeekOfYear(connSocket, server);
				break;
			case 11:
				GetDaylightSavings(connSocket, server);
				break;
			case 12:
				GetTimeWithoutDateInCity(connSocket, server);
				break;
			case 13:
				MeasureTimeLap(connSocket, server);
				break;
			default:
				break;
			}
		}
	}
}

void main()
{

	// Initialize Winsock (Windows Sockets).

	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}

	// Client side:
	// Create a socket and connect to an internet address.

	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// For a client to communicate on a network, it must connect to a server.

	// Need to assemble the required data for connection in sockaddr structure.

	// Create a sockaddr_in object called server. 
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);

	RunInputLoop(connSocket, server);

	// Closing connections and Winsock.
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}