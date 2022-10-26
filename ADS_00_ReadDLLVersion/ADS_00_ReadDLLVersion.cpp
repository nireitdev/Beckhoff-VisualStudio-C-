// ADS_00_ReadDLLVersion.cpp 
// Lectura de Version del DLL ADS
// 
// @autor: José
//
#include <iostream>
#include <conio.h>
#include <windows.h>


// ADS headers for TwinCAT 3
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h"

using namespace std;

int main()
{
	long    nTemp;
	AdsVersion* pDLLVersion;

	nTemp = AdsGetDllVersion();
	pDLLVersion = (AdsVersion*)&nTemp;
	cout << "Version: " << (int)pDLLVersion->version << '\n';
	cout << "Revision: " << (int)pDLLVersion->revision << '\n';
	cout << "Build: " << pDLLVersion->build << '\n';
	cout.flush();
	_getch();
}
