// ADS_03_ReadVariables
// Leer variables de un  PLC Beckhoff conectado (CX2040)
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
	long nErr, nPort;
	AmsAddr Addr;
	PAmsAddr pAddr = &Addr;
	ULONG lHdlVar;
	short nData; //C++ "short" = PLC "INT" = 16 bits
	char szVar[] = { "GVL.ncounter" }; 

	// Open communication port on the ADS router
	nPort = AdsPortOpen();
	nErr = AdsGetLocalAddress(pAddr);
	if (nErr) cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';

	// TwinCAT 3 PLC1 = 851
	pAddr->port = 851;

	// Fetch handle for an <szVar> PLC variable 
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, sizeof(szVar), szVar);
	cout << "Handle: " << lHdlVar << '\n';
	if (nErr) cerr << "Error: AdsSyncReadWriteReq: " << nErr << '\n';
	do
	{
		// Read value of a PLC variable (by handle)
		nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(nData), &nData);
		if (nErr)
			cerr << "ERROR: AdsSyncReadReq: " << nErr << '\n';
		else
			cout << "Valor Leido: " << nData << '\n';
		cout.flush();
		if (nData > 10)
		{
			// Reset the value of the PLC variable to 0 
			nData = 0;
			nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(nData), &nData);
			if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
		}
	} while (_getch() == '\r'); // read next value with RETURN, else end


	//Release handle of plc variable
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';

	// Close communication port
	nErr = AdsPortClose();
	if (nErr) cerr << "Error: AdsPortClose: " << nErr << '\n';
}
