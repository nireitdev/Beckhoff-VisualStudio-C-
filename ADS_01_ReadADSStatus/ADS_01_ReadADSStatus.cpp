// ADS_01_ReadADSStatus.cpp : 
// Simple ejemplo para leer el estado del PLC
// 
// @autor: José
//

#include <iostream>
#include <windows.h>
#include <conio.h>

// ADS headers for TwinCAT 3
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h"

using namespace std;

int main()
{
	unsigned short nAdsState;
	USHORT    nDeviceState;
	long nErr, nPort;
	AmsAddr Addr;
	PAmsAddr pAddr = &Addr;

	// Open communication port on the ADS router
	nPort = AdsPortOpen();
	nErr = AdsGetLocalAddress(pAddr);
	if (nErr) cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';

	// TwinCAT3 PLC1 = 851
	pAddr->port = 851;

	do
	{
		nErr = AdsSyncReadStateReq(pAddr, &nAdsState, &nDeviceState);
		if (nErr)
			cerr << "Error: AdsSyncReadStateReq: " << nErr << '\n';
		else
		{
			cout << "AdsState: " << nAdsState << '\n';
			cout << "DeviceState: " << nDeviceState << '\n';
		}
		cout.flush();
	} while (_getch() == '\r'); // continue on a carriage return, finish for any other key

	// Close communication port
	nErr = AdsPortClose();
	if (nErr) cerr << "Error: AdsPortClose: " << nErr << '\n';
}
