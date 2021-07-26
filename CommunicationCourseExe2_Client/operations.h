#include <winsock2.h> 

void GetTime(SOCKET connSocket, sockaddr_in server);
void GetTimeWithoutDate(SOCKET connSocket, sockaddr_in server);
void GetTimeSinceEpoch(SOCKET connSocket, sockaddr_in server);
void GetClientToServerDelayEstimation(SOCKET connSocket, sockaddr_in server);
void MeasureRTT(SOCKET connSocket, sockaddr_in server);
void GetTimeWithoutDateOrSeconds(SOCKET connSocket, sockaddr_in server);
void GetYear(SOCKET connSocket, sockaddr_in server);
void GetMonthAndDay(SOCKET connSocket, sockaddr_in server);
void GetSecondsSinceBeginingOfMonth(SOCKET connSocket, sockaddr_in server);
void GetWeekOfYear(SOCKET connSocket, sockaddr_in server);
void GetDaylightSavings(SOCKET connSocket, sockaddr_in server);
void GetTimeWithoutDateInCity(SOCKET connSocket, sockaddr_in server);
void MeasureTimeLap(SOCKET connSocket, sockaddr_in server);