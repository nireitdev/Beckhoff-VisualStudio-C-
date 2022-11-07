// ADS_01_ReadADSStatus.cpp : 
// Leer el estado del PLC Beckhoff conectado (CX2040)
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
    USHORT nAdsState;
    USHORT nDeviceState = 0;
    long    nErr, nPort;
    int     ch;
    void* pData = NULL;
    AmsAddr Addr;
    PAmsAddr pAddr = &Addr;

    // Open communication port on the ADS router
    nPort = AdsPortOpen();
    nErr = AdsGetLocalAddress(pAddr);
    if (nErr) cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';

    
    //TC3 runtime 1: 851, system manager: 10000 
    pAddr->port = 10000;

    cout << "(R) -> PLC Run\n";     
    cout << "(C) -> PLC Config Mode\n";

    cout << "\n(S) -> PLC Stop - OJO: stop completamente el PLC!!\n";
    cout.flush();
    ch = _getch();
    ch = toupper(ch);
    while ((ch == 'R') || (ch == 'S') || (ch == 'C'))
    {
        switch (ch)
        {
        case 'R':
            nAdsState = ADSSTATE_RESET; //Start PLC;
            break;
        case 'S':
            nAdsState = ADSSTATE_STOP; //Stop completamente el plc
            break;        
        case 'C':
            nAdsState = ADSSTATE_RECONFIG; //Config; 
            break;
        }
        nErr = AdsSyncWriteControlReq(pAddr, nAdsState, nDeviceState, 0, pData);
        if (nErr) cerr << "Error: AdsSyncWriteControlReq: " << nErr << '\n ';
        ch = _getch();
        ch = toupper(ch);
    }

    // Close communication port
    nErr = AdsPortClose();
    if (nErr) cerr << "Error: AdsPortClose: " << nErr << '\n';
}
