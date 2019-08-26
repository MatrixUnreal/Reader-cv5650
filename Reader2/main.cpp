#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "CVAPIV01_DESFire.H"


using namespace std;

auto hDll = ::LoadLibrary("CVAPIV01_DESFire.dll");

int __stdcall callbackfromRFID(char *HexDataRead)
{
	return 0;
}


int main()
{
	int intResult = -1;
	int boolResult = -1;

	string ipstring = "192.168.1.100";
	unsigned char* uIP = (unsigned char*)ipstring.c_str();
	unsigned char* getWiegandMode = new unsigned char[50];
	string ipstringRemote = "192.168.1.101";
	int port = 2000;
	int DeviceAddress = 0;

	
	if (hDll == NULL)
	{
		cout << "Can't load dll of RFID";
		return -1;
	}
	

	auto isAutoReadRFID = (int(_stdcall*)())GetProcAddress(hDll, "CV_IsAutoRead");
	auto AutoRead_Run = (int(_stdcall*)())GetProcAddress(hDll, "CV_AutoRead_Run");
	auto setLed = (int(_stdcall*)(int, unsigned char))GetProcAddress(hDll, "CV_SetLED");
	auto TCPRun = (int(_stdcall*)(int, unsigned char*))GetProcAddress(hDll, "CV_TCPRun");
	auto GetIP = (int(_stdcall*)(int, unsigned char*))GetProcAddress(hDll, "CV_GetIP");
	auto GetVersionAPI = (int(_stdcall*)(char*))GetProcAddress(hDll, "CV_GetVersionAPI");
	auto GetMAC = (int(_stdcall*)(int, unsigned char*))GetProcAddress(hDll, "CV_GetMAC");
	auto GetPortRFID = (int(_stdcall*)(int, unsigned char *))GetProcAddress(hDll, "GetPort");
	auto SetOnAutoRead = (int(_stdcall*)(TOnAutoRead))GetProcAddress(hDll, "CV_SetOnAutoRead");
	auto GetVersionlNum = (int(_stdcall*)(int, char*))GetProcAddress(hDll, "CV_GetVersionNum");
	auto GetVersionNum = (int(_stdcall*)(int, char *))GetProcAddress(hDll, "CV_GetVersionNum");
	auto GetCommunicationType = (int(_stdcall*)())GetProcAddress(hDll, "CV_GetCommunicationType");
	auto SendLocalIPPort = (int(_stdcall*)(int, int, char*))GetProcAddress(hDll, "CV_SendLocalIPPort");
	auto GetWiegandMode = (int(_stdcall*)(int, unsigned  char*))GetProcAddress(hDll, "CV_GetWiegandMode");
	auto SetCommunicationType = (int(_stdcall*)(byte aType))GetProcAddress(hDll, "CV_SetCommunicationType");
	auto ActiveWiegandMode = (int(_stdcall*)(int, unsigned  char))GetProcAddress(hDll, "CV_ActiveWiegandMode");
	auto ActiveBuzzer = (int(_stdcall*)(int, unsigned char, unsigned char *))GetProcAddress(hDll, "CV_ActiveBuzzer");
	auto ActiveLED = (int(_stdcall*)(int, unsigned char, unsigned char, unsigned char))GetProcAddress(hDll, "CV_ActiveLED");
	auto WiegandMode = (int(_stdcall*)(int, unsigned char*))GetProcAddress(hDll, "CV_WiegandMode");
	auto SetRemoteIPPort = (int(_stdcall*)(unsigned char *, int))GetProcAddress(hDll, "CV_SetRemoteIPPort");
	

	//char *HexDataRead=new char[1];
	//HexDataRead[0] = 1;
	boolResult = SetCommunicationType(3);

	TOnAutoRead onAutoReadCallback = (TOnAutoRead)&callbackfromRFID;
	//int x2 = (*onAutoReadCallback)(HexDataRead);
	boolResult = SetOnAutoRead(onAutoReadCallback);
	int connectToRFID = TCPRun(port, uIP);//conect to RFID
	if (connectToRFID)
	{
		cout << "Can't connect to RFID";
	}
	


	// TODO: Add your control notification handler code here
	int status = -1;
	unsigned char CardType = 0;
	unsigned char MaxTg = 2;
	unsigned char IniDataLen = 0, RDataLen = 0, NbTg = 0;
	unsigned char IniData[64], RData[64];
	unsigned short Begin;
	unsigned char MFUID[32];
	unsigned short UIDLen;
	int block = 7;

	memset(IniData, 0x00, 64);
	memset(RData, 0x00, 64);
	memset(MFUID, 0x00, 32);
	UIDLen = 0;
	

	auto InListPassiveTarget = (int(_stdcall*)(int, unsigned char, unsigned char, unsigned char, unsigned char,
		unsigned char *, unsigned char *, unsigned char *, unsigned char *))GetProcAddress(hDll, "PN_InListPassiveTarget");
	if (InListPassiveTarget != NULL)
	{
		status = InListPassiveTarget(DeviceAddress, CardType, MaxTg, 0, IniDataLen, IniData, &NbTg, &RDataLen, RData);
		if (0 == status)
		{
			cout << "PN_InListPassive OK\r\n";
			int i;
			UIDLen = RData[4];	Begin = 5;
			for (i = 0; i < UIDLen; i++)
			{
				MFUID[i] = RData[Begin + i];
				printf("%.2X", MFUID[i]);
			}
			
		}
		else
			cout << "PN_InListPassive Error\r\n";
	}
	
	status = -1;
	unsigned char TargetNum = 1;
	auto SelectTarget = (int(_stdcall*)(int , unsigned char ))GetProcAddress(hDll, "PN_SelectTarget");
	if (SelectTarget != NULL)
	{
		status = SelectTarget(DeviceAddress, TargetNum);
		if (0 == status)
			cout<<"PN_SelectTarget OK\r\n";
		else
			cout << "PN_SelectTarget Error\r\n";
	}

	status = -1;
	unsigned char buffer[32];

	memset(buffer, 0x00, 32);
	auto MF_Read = (int(_stdcall*)(int , unsigned char , unsigned char , unsigned char *))GetProcAddress(hDll, "MF_Read");

	if (MF_Read != NULL)
	{
		for (int j = 0; j < 0x0f; j+=4)
		{
			status = MF_Read(DeviceAddress, j, 0x01, buffer);
			if (0 == status)
			{
				for (int i = 0; i < 16; i++)
				{
					//printf("%.2X", buffer[i]);
					cout << buffer[i];
				}
				cout << "|\n";
				//cout << "MF_Read OK\r\n";
			}
			else
				cout << "MF_Read Error\r\n";
		}
		cout << "***********************" << endl;
	}










	/*int intResult = GetCommunicationType();
	boolResult = GetIP(DeviceAddress, uIP);
	boolResult = ActiveLED(DeviceAddress, 2, 2, 5);

	unsigned char *pattern = new unsigned char(5);
	pattern[0] = 1;
	pattern[1] = 1;
	pattern[2] = 1;
	pattern[3] = 1;
	pattern[4] = 1;

	int a11 = ActiveBuzzer(DeviceAddress, 4, pattern);

	boolResult = SendLocalIPPort(DeviceAddress, port, (char*)ipstring.c_str());
	//boolResult = SetRemoteIPPort((unsigned char*)ipstring.c_str(), port);
	*/

	
	
	//int a13 = ActiveWiegandMode(DeviceAddress, activeWiegandMode);

	unsigned char data[11];
	data[0] = 0;//0x00;
	data[1] = 0;//  'the block//0x00;
	data[2] = 38;//0x26;//0x52;
	data[3] = 19;//0x08;
	data[4] = 1;//0x01;
	data[5] = 46;//0x04;
	data[6] = 255;//0xff;
	data[7] = 0;//0x00;
	data[8] = 0;//0x00;
	data[9] = 0;//0x00;
	data[10] = 0;//0x00;

	int resultInt1 = WiegandMode(DeviceAddress, data);

	boolResult = AutoRead_Run();
	intResult = isAutoReadRFID();




	
/*
	// TODO: Add your control notification handler code here
	int status = -1;
	unsigned char buffer[32];
	string strTemp;

	memset(buffer, 0x00, 32);

	auto MF_Read = (int(_stdcall*)(int, unsigned char, unsigned char, unsigned char *))GetProcAddress(hDll, "MF_Read");
	if (MF_Read != NULL)
	{
		for (int j = 0; j < 0xff; j++)
		{
			status = MF_Read(0, j, 0x01, buffer);
			if (0 == status)
			{
				for (int i = 0; i < 16; i++)
				{
					cout << buffer[i];
				}

				cout << "\nMF_Read OK\r\n";
			}
			else
				cout << "\nMF_Read Error\r\n";
		}
	}
	*/

















	//int a13 = ActiveWiegandMode(DeviceAddress, activeWiegandMode);
	
	//const char c_test[10] = { 0x02,0x00,0x1D,01,0x00,0x03 };
	//const char c_test[10] = { 0x02,0x00,0x19,0x01,0x00,0x03 };// reset?
	//QByteArray qba_test(QByteArray::fromRawData(c_test, 10));

	//tcpSocketRFIDReg->write(qba_test);

	//const char c_test[10] = { 0x02,0x00,0x03,0x00,0x02,0x01,0x03 };
	//QByteArray qba_test(QByteArray::fromRawData(c_test, 10));

	//tcpSocketRFIDReg->write(qba_test);
	//#02ê#00A#03#00#02#01—#03
	while (1)
	{
	//	boolResult = GetWiegandMode(DeviceAddress, getWiegandMode);



	}

	_getch();
	return 0;
}