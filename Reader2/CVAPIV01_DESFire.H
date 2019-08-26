#ifndef UCVAPIV01_DESFireH
#define UCVAPIV01_DESFireH


/*------define windows version---- */
#ifndef _WINDOWS_VERSION
#define _WINDOWS_VERSION
#endif


/*------define linux version----*/
//#ifndef _LINUX_VERSION
//#define _LINUX_VERSION
//#endif


#ifdef _WINDOWS_VERSION
    #ifdef CV_API_EXPORT
      #define extern__stdcall extern "C" __declspec(dllexport) int __stdcall
    #else
      #define extern__stdcall extern "C" __declspec(dllimport) int __stdcall
    #endif
#else
    #define extern__stdcall extern int

    typedef unsigned char byte;
    typedef unsigned char BYTE;
#endif

#ifndef _TOnAutoRead_
#define _TOnAutoRead_
typedef int (__stdcall *TOnAutoRead)(char *HexDataRead);
typedef int (__stdcall *TOnAutoReadEx)(char *HexDataRead,int *CommunicationType,char *CommunicationAddr);
#endif


/**************** System Functions ***********************/
extern__stdcall CV_SetCommunicationType(byte aType);//aType 0--COM RS232,1--USB,2--UDP
extern__stdcall CV_GetCommunicationType();//return 0--COM RS232,1--USB,2--UDP
extern__stdcall CV_UDPRun(int SvrPort); //ʼUDPͨ;
extern__stdcall CV_UDPStop();
//extern__stdcall CV_UDPSetCurrentSvrPort(int SvrPort);
extern__stdcall CV_SetRemoteIPPort(unsigned char *ip,int port);  //ԶIPַ

//32. Get the current API commuication version.
extern__stdcall CV_GetVersionAPI(char *VersionAPI);

//1. Set communciation baudrate.
extern__stdcall CV_OpenComm(char *com,int Baudrate);

//2. To close communication port.
extern__stdcall CV_CloseComm(void);

//3. Set device(firmware) address for RS485 communication.
extern__stdcall CV_SetDeviceAddress(int DeviceAddress,unsigned char &newAddress,unsigned char mode,unsigned char *buffer);

//4. Get device(firmware) address and serial number from target device.
extern__stdcall CV_GetSerialNum(int DeviceAddress,int &CurrentAddress, char *SerialNum);

//6. Get device(firmware) version number.
extern__stdcall CV_GetVersionNum(int DeviceAddress,char *VersionNum);

extern__stdcall CV_SetSerialNum(int DeviceAddress,char *SerialNum);

//xx Get user information
extern__stdcall CV_GetUserInfo(int DeviceAddress, char *user_info);

//xx Set the device(firmware) serial number.
extern__stdcall CV_SetUserInfo(int DeviceAddress,char *user_info);

// Set firmware communication baudrate
extern__stdcall CV_SetFirmwareBaudrate(int DeviceAddress,unsigned char Baudrate);

//11. Toggle LED ON OFF .
extern__stdcall CV_ActiveLED(int DeviceAddress,unsigned char NumLED,unsigned char time,unsigned char cycle);

//12. To ON LED forever.
extern__stdcall CV_SetLED(int DeviceAddress,unsigned char NumLED);

// Get IP through COM communication for DHCP
extern__stdcall CV_GetIP(int DeviceAddress, unsigned char* IP);

//Set IP Subnet Mask and default gateway through COM communication for DHCP
extern__stdcall CV_SetIP(int DeviceAddress, unsigned char* IP, unsigned char* Mask, unsigned char* Gateway);

extern__stdcall CV_ReaderReset(int DeviceAddress);

// Get MAC through COM communication for DHCP
extern__stdcall CV_GetMAC(int DeviceAddress, unsigned char* MAC);

// Set Default Setting
extern__stdcall CV_SetDefaultSetting(int DeviceAddress);

//14. To control buzzer ON/OFF or ON OFF ON OFF
extern__stdcall CV_ActiveBuzzer(int DeviceAddress,unsigned char mode,unsigned char *buffer);
extern__stdcall CV_ReaderC_EXT(int DeviceAddress,unsigned char iTime);

extern__stdcall CV_GenericCMD(int DeviceAddress,unsigned char mode, unsigned char *buffer, int &NumByte);
extern__stdcall CV_SetWiegandStatus(int DeviceAddress,unsigned char status);
extern__stdcall CV_GetWiegandMode(int DeviceAddress,unsigned char *reqbuffer);
extern__stdcall CV_ActiveWiegandMode(int DeviceAddress,unsigned char status);
extern__stdcall CV_WiegandMode(int DeviceAddress,unsigned char *data);
extern__stdcall CV_GetKey(int DeviceAddress,unsigned char *keybuffer);

extern__stdcall TamperAlarmButtonOn(int DeviceAddress);
extern__stdcall TamperAlarmButtonOff(int DeviceAddress);

// For Auto-Read mode
extern__stdcall  CV_SetOnAutoRead(TOnAutoRead aEventFun);
extern__stdcall  SetOnAutoReadEx(TOnAutoReadEx aEventFun);
extern__stdcall  CV_AutoRead_Run();
extern__stdcall  CV_AutoRead_Stop();
extern__stdcall  CV_IsAutoRead();

/**************** ISO14443 Functions ***********************/
//xx To place tag in halt state thus no more responding
extern__stdcall MF_Halt(int DeviceAddress,unsigned char mode);

extern__stdcall MF_ReaderHalt(int DeviceAddress,unsigned char mode);
//29. Send the generic command to tag.
extern__stdcall CV_SLE_Generic(int DeviceAddress,unsigned char CRC_Flag,unsigned char &length,unsigned char *buffer);
extern__stdcall CV_SLE_GenericEx(int DeviceAddress,unsigned char CRC_Flag,unsigned char TimeOut,unsigned char &length,unsigned char *buffer);  



/**************** MIFARE Functions ***********************/
//xx Mifare direct load key to Master Key Buffer
extern__stdcall MF_LoadKey(int DeviceAddress,unsigned char *key);
//xx MIFARE Authentication
extern__stdcall MF_Auth(int DeviceAddress,unsigned char mode, unsigned char *snr, unsigned char block);
// xx Mifare Read
extern__stdcall MF_Read(int DeviceAddress,unsigned char add_blk, unsigned char num_blk, unsigned char *buffer);
//xx Mifare Write
extern__stdcall MF_Write(int DeviceAddress,unsigned char add_blk, unsigned char num_blk, unsigned char *buffer);

//xx MIFARE Increment function
extern__stdcall MF_Increment(int DeviceAddress,unsigned char add_blk, int value);

//xx MIFARE Decrement function
extern__stdcall MF_Decrement(int DeviceAddress,unsigned char add_blk, int value);

//xx MIFARE Transfer function
extern__stdcall MF_Transfer(int DeviceAddress,unsigned char add_blk);

//xx MIFARE Restore function
extern__stdcall MF_Restore(int DeviceAddress,unsigned char add_blk);

// xx MIFARE Write Value function
extern__stdcall MF_InitValue(int DeviceAddress,unsigned char add_blk, int value);

//xx MIFARE Read Value function
extern__stdcall MF_ReadValue(int DeviceAddress,unsigned char add_blk, int *value);

//xx Mifare store Master key to EEPROM
extern__stdcall MF_StoreKeyToEE(int DeviceAddress,unsigned char Key_type,unsigned char Sector,unsigned char *Key);

//xx Mifare load Master key from EEPROM
extern__stdcall MF_LoadKeyFromEE(int DeviceAddress,unsigned char Key_type,unsigned char Sector);




//extern__stdcall MF_Request(int DeviceAddress, unsigned char inf_mode, unsigned char *buffer);
//extern__stdcall MF_Anticoll(int DeviceAddress,unsigned char *snr,unsigned char &status);
//extern__stdcall MF_Select(int DeviceAddress,unsigned char *snr);
//extern__stdcall MF_Select2(int DeviceAddress,unsigned char *snr);
//extern__stdcall MF_Select3(int DeviceAddress,unsigned char *snr);

/**************** MIFARE High Level Functions ***********************/
extern__stdcall MF_HLRead(int DeviceAddress,unsigned char mode,unsigned char blk_add,unsigned char num_blk,
                          unsigned char *snr, unsigned char *buffer);
extern__stdcall MF_HLWrite(int DeviceAddress,unsigned char mode,unsigned char blk_add,unsigned char num_blk,
                          unsigned char *snr, unsigned char *buffer);
extern__stdcall MF_HLInitVal(int DeviceAddress,unsigned char mode,unsigned char SectNum,unsigned char *snr, int value);
extern__stdcall MF_HLDec(int DeviceAddress,unsigned char mode,unsigned char SectNum,unsigned char *snr, int *value);
extern__stdcall MF_HLInc(int DeviceAddress,unsigned char mode,unsigned char SectNum,unsigned char *snr, int *value);

/**************** MIFARE Ultralight Functions ***********************/
//xx Mifare UltraLight Read
extern__stdcall MF_UL_Read(int DeviceAddress,int StartPage , unsigned char *FromData_16Bytes);
extern__stdcall MF_UL_Write(int DeviceAddress,int PageNum , unsigned char *ToData_4Bytes);
 
/**************** DESFire EV1 Commands execute ad Firmware***********************/
extern__stdcall  MF_DFEV1_DESELECT(int DeviceAddress,unsigned char CID);
extern__stdcall  MF_DFEV1_Authenticate(int DeviceAddress,unsigned char CID,unsigned char CryptoType,
								  unsigned char KeyNo, unsigned char *Key);
extern__stdcall  MF_DFEV1_ChangeKeySettings(int DeviceAddress,unsigned char CID,unsigned char MasterKeySettings);
extern__stdcall  MF_DFEV1_GetKeySettings(int DeviceAddress,unsigned char CID,unsigned char *MasterKeySettings,unsigned char *KeyNumber,unsigned char *CryptoType);
extern__stdcall  MF_DFEV1_ChangeKey(int DeviceAddress,unsigned char CID,unsigned char KeyNo, unsigned char CryptoType,
							   unsigned char KeyVersion, unsigned char *NewKey, unsigned char *OldKey);
extern__stdcall  MF_DFEV1_GetKeyVersion(int DeviceAddress,unsigned char CID, unsigned char KeyNo,unsigned char *KeyVersion);
extern__stdcall  MF_DFEV1_CreateApplication(int DeviceAddress,unsigned char CID, int AID,
						                    unsigned char MasterKeySettings, unsigned char KeyNum, unsigned char CryptoType);
extern__stdcall  MF_DFEV1_DeleteApplication(int DeviceAddress,unsigned char CID, int AID);
extern__stdcall  MF_DFEV1_GetApplicationIDs(int DeviceAddress,unsigned char CID, int *AIDs, int *AIDNum);
extern__stdcall  MF_DFEV1_SelectApplication(int DeviceAddress,unsigned char CID, int AID);
extern__stdcall  MF_DFEV1_FormatPICC(int DeviceAddress,unsigned char CID);
extern__stdcall  MF_DFEV1_GetVersion(int DeviceAddress,unsigned char CID, unsigned char *VersionInfo,unsigned int *VersionInfoLen);
extern__stdcall  MF_DFEV1_GetFreeMem(int DeviceAddress,unsigned char CID, int *RemainMemSize);
extern__stdcall  MF_DFEV1_GetCardUID(int DeviceAddress,unsigned char CID, unsigned char *UID,unsigned int *UIDLen);
extern__stdcall  MF_DFEV1_SetConfiguration(int DeviceAddress,unsigned char CID, unsigned char ConfigType, unsigned char *ConfigData,unsigned int ConfigDataLen);
extern__stdcall  MF_DFEV1_GetFileIDs(int DeviceAddress,unsigned char CID, unsigned char *FileIDs,unsigned int *FileIDsLen);
extern__stdcall  MF_DFEV1_GetFileSettings(int DeviceAddress,unsigned char CID,unsigned char FileID, unsigned char *FileSettings);
extern__stdcall  MF_DFEV1_ChangeFileSettings(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char CmtSet,unsigned short AccessRights,bool Is_Rights_Free);
extern__stdcall  MF_DFEV1_CreateDataFile(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char FileType,
									unsigned char CmtSet,unsigned short AccRights,unsigned int CreateSize);
extern__stdcall  MF_DFEV1_CreateValueFile(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char CmtSet,
									unsigned short AccRights,unsigned int LLimit,unsigned int ULimit,unsigned int InitVal,unsigned char LimitCredit);
extern__stdcall  MF_DFEV1_CreateRecordFile(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char FileType,unsigned char CmtSet,
									unsigned short AccRights,unsigned int SingleRecordSize,unsigned int RecordNumber);
extern__stdcall  MF_DFEV1_DeleteFile(int DeviceAddress,unsigned char CID, unsigned char FileID);
extern__stdcall  MF_DFEV1_ReadData(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char CmtSet,
									unsigned int Offset,unsigned int ReadLength,unsigned char *ReturnData,unsigned int *ReturnDataLen);
extern__stdcall  MF_DFEV1_WriteData(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char CmtSet,
									unsigned int Offset,unsigned int WriteDataLength,unsigned char *WriteData);
extern__stdcall  MF_DFEV1_GetValue(int DeviceAddress,unsigned char CID, unsigned char FileID, unsigned char CmtSet, int *RetValue);
extern__stdcall  MF_DFEV1_Credit(int DeviceAddress,unsigned char CID, unsigned char FileID, unsigned char CmtSet,unsigned int IncValue);
extern__stdcall  MF_DFEV1_LimitedCredit(int DeviceAddress,unsigned char CID, unsigned char FileID, unsigned char CmtSet,unsigned int IncValue);
extern__stdcall  MF_DFEV1_Debit(int DeviceAddress,unsigned char CID, unsigned char FileID, unsigned char CmtSet,unsigned int DecValue);
extern__stdcall  MF_DFEV1_WriteRecord(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char CmtSet,
									unsigned int Offset,unsigned int RecordLength,unsigned char *RecordData);
extern__stdcall  MF_DFEV1_ReadRecord(int DeviceAddress,unsigned char CID,unsigned char FileID,unsigned char CmtSet,
									unsigned int Offset,unsigned int ReadNumber,unsigned int RecSize,unsigned char *ReturnData,unsigned int *ReturnDataLen);
extern__stdcall  MF_DFEV1_ClearRecordFile(int DeviceAddress,unsigned char CID,unsigned char FileID);
extern__stdcall  MF_DFEV1_CommitTransaction(int DeviceAddress,unsigned char CID);
extern__stdcall  MF_DFEV1_AbortTransaction(int DeviceAddress,unsigned char CID); 
extern__stdcall MF_DFEV1_KeySetting(int DeviceAddress,unsigned char KeyNo,unsigned char CryptoType,unsigned char *Key);
extern__stdcall MF_DFEV1_FileSetting(int DeviceAddress,int AID,unsigned char KeyNo,unsigned char FileID,unsigned char FileType,
									unsigned char CmtSet,unsigned int Offset,unsigned int Length,unsigned int RecSize);  

 //add by zrj
extern__stdcall MF_NFC_T2T_PageSetting(int DeviceAddress,unsigned char Page);
extern__stdcall MF_NFC_T4T_PageSetting(int DeviceAddress,int P1,int P2,int Length);


extern__stdcall  MF_DFEV1HL_Read(int DeviceAddress,unsigned char CID,int AID,unsigned char KeyNo,
								 unsigned char FileID,unsigned char FileType,unsigned char CmtSet,unsigned int Offset,unsigned int Length,
								 unsigned int RecSize,unsigned char *Data,unsigned int *ReadLen);
extern__stdcall  MF_DFEV1HL_Write(int DeviceAddress,unsigned char CID,int AID,unsigned char KeyNo,
								 unsigned char FileID,unsigned char FileType,unsigned char CmtSet,unsigned int Offset,unsigned int Length,
								 unsigned char *Data);
extern__stdcall  MF_DFEV1HL_ClearReads(int DeviceAddress,unsigned char CID,int AID,unsigned char KeyNo, unsigned char FileID);
extern__stdcall  MF_DFEV1HL_GetValue(int DeviceAddress,unsigned char CID,int AID,unsigned char KeyNo, unsigned char FileID,unsigned char CmtSet, int *RetValue);
extern__stdcall  MF_DFEV1HL_Credit(int DeviceAddress,unsigned char CID,int AID,unsigned char KeyNo, unsigned char FileID,unsigned char CmtSet, unsigned int IncValue,bool IsLimited=false);
extern__stdcall  MF_DFEV1HL_Debit(int DeviceAddress,unsigned char CID, int AID,unsigned char KeyNo, unsigned char FileID,unsigned char CmtSet, unsigned int DecValue);
extern__stdcall  MF_DFEV1_TransportKey(int DeviceAddress, unsigned char *Key);


		//Mifare Plus ommands execute at firmware
extern__stdcall MF_Plus_WritePerso(int DeviceAddress,unsigned char CID,unsigned short BNr,unsigned char *Data);
extern__stdcall MF_Plus_CommitPerso(int DeviceAddress,unsigned char CID);
		//Mifare Plus SL1 commands execute at firmware
extern__stdcall MF_Plus_SL1AESAuth(int DeviceAddress,unsigned char *AESKey);
		//Mifare Plus SL2 commands execute at firmware
extern__stdcall MF_Plus_SL2AESAuth(int DeviceAddress,unsigned short BNr,unsigned char *AESKey,unsigned char *MFKey,unsigned char *MFSessionKey);
		//Mifare Plus SL3 commands execute at firmware
extern__stdcall MF_Plus_FirstAuth(int DeviceAddress,unsigned char CID,unsigned short BNr,unsigned char *AESKey);
extern__stdcall MF_Plus_FollowAuth(int DeviceAddress,unsigned char CID,bool IsPlusX,unsigned short BNr,unsigned char *AESKey);
extern__stdcall MF_Plus_SL3ResetAuth(int DeviceAddress,unsigned char CID);
extern__stdcall MF_Plus_SL3Read(int DeviceAddress,unsigned char CID,bool IsPlusX,unsigned short BNr,unsigned char BlockNum,
							bool MACC,bool Plaintext,bool MACR,unsigned char *DataRead,unsigned char *DataReadLen);
extern__stdcall MF_Plus_SL3Write(int DeviceAddress,unsigned char CID,bool IsPlusX,unsigned short BNr,
							 bool Plaintext,bool MACR,unsigned char *DataToWrite);
extern__stdcall MF_Plus_SL3Value(int DeviceAddress,unsigned char CID,unsigned char OPType,unsigned short BNr,bool MACR,int *Value);
extern__stdcall MF_Plus_AutoReadSetting(int DeviceAddress,unsigned char *Setting);
extern__stdcall MF_Plus_GetAutoReadSetting(int DeviceAddress,unsigned char *Setting);

/****************start PN532 Commands implemented at SDK ***********************/
extern__stdcall PN_InListPassiveTarget(int DeviceAddress,unsigned char CardType,unsigned char MaxTg,unsigned char BaudRate,unsigned char IniDataLen,
								   unsigned char *IniData,unsigned char *NbTg,unsigned char *RDataLen,unsigned char *RData);
extern__stdcall PN_SelectTarget(int DeviceAddress,unsigned char TargetNum);
extern__stdcall PN_ExchangeData(int DeviceAddress,unsigned char InTg,unsigned char BaudRate,unsigned char TimeOut,
							  unsigned char *NFCID3,unsigned char *Data,unsigned char *DataLen);
/****************end  PN532 Commands implemented at SDK ***********************/
/**************************start NFC command *********************************/
extern__stdcall NFC_LLCP_Symm(int DeviceAddress, unsigned char* RetData);
extern__stdcall NFC_LLCP_Connect(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char* MIUX, unsigned char RW, unsigned char* SN, unsigned char* RetData);
extern__stdcall NFC_LLCP_Cc(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char* MIUX, unsigned char RW, unsigned char* RetData);
extern__stdcall NFC_LLCP_Disc(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char* RetData);
extern__stdcall NFC_LLCP_I(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char SEQ, unsigned char* Data, unsigned char DataLen, unsigned char* RetData);
extern__stdcall NFC_LLCP_Rr(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char SEQ, unsigned char* RetData);
extern__stdcall NFC_LLCP_Rnr(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char SEQ, unsigned char* RetData);
extern__stdcall NFC_LLCP_Dm(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char RESON, unsigned char* RetData);
extern__stdcall NFC_LLCP_Frmr(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char* INFO, unsigned char* RetData);
extern__stdcall NFC_LLCP_Ui(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char* Data, unsigned char* RetData);
extern__stdcall NFC_LLCP_Sdreq(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char TID, unsigned char* SN_URI, unsigned char* RetData);
extern__stdcall NFC_LLCP_Sdres(int DeviceAddress, unsigned char DSAP, unsigned char SSAP, unsigned char TID, unsigned char SAP, unsigned char* RetData);
extern__stdcall NFC_LLCP_Poll(int DeviceAddress, unsigned char* RetData);

extern__stdcall NFC_T4TA_Select(int DeviceAddress, unsigned char P1, unsigned char P2, unsigned char length, unsigned char* data, unsigned char* RetData);
extern__stdcall NFC_T4TA_Read(int DeviceAddress, unsigned char P1, unsigned char P2, unsigned char length, unsigned char* RetData);
extern__stdcall NFC_T4TA_Write(int DeviceAddress, unsigned char P1, unsigned char P2, unsigned char length, unsigned char* data, unsigned char* RetData);

extern__stdcall NFC_T1T_Rall(int DeviceAddress, unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Read(int DeviceAddress, unsigned char add, unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Write_E(int DeviceAddress, unsigned char add, unsigned char data, unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Write_Ne(int DeviceAddress, unsigned char add, unsigned char data,  unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Rseg(int DeviceAddress, unsigned char add, unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Read8(int DeviceAddress, unsigned char add, unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Write_E8(int DeviceAddress, unsigned char add, unsigned char* data, unsigned char* uid, unsigned char* RetData);
extern__stdcall NFC_T1T_Write_Ne8(int DeviceAddress, unsigned char add, unsigned char* data, unsigned char* uid, unsigned char* RetData);

extern__stdcall NFC_T3T_Check(int DeviceAddress, unsigned char* uid, unsigned char svc, unsigned char* sc, unsigned char blk, unsigned char flag2, unsigned char* bl, unsigned char* RetData);
extern__stdcall NFC_T3T_Update(int DeviceAddress, unsigned char* uid, unsigned char svc, unsigned char* sc, unsigned char blk, unsigned char flag2, unsigned char* bl, unsigned char* data, unsigned char* RetData);

extern__stdcall NFC_Target(int DeviceAddress, unsigned char* RetData);

extern__stdcall NFC_Picc_Init(int DeviceAddress, unsigned char Mode, unsigned char* MParam,
								unsigned char* FParam, unsigned char* NFCID3t, unsigned char GtLen,
								unsigned char* Gt, unsigned char TkLen, unsigned char* Tk, unsigned char* RetData);
extern__stdcall NFC_Picc_Command(int DeviceAddress, unsigned char* RetData);
extern__stdcall NFC_Picc_Response(int DeviceAddress, unsigned char TgResLen, unsigned char* TgResponse, unsigned char* RetData);
/**************************end NFC command *********************************/

extern__stdcall Control_LED_Buzzer_Relay(int DeviceAddress,unsigned char head,unsigned char *LEDData ,unsigned char *BuzzerData, unsigned char RelayTime);
extern__stdcall CV_TCPRun(int RemotePort, unsigned char *RemoteIP);
extern__stdcall CV_TCPStop();
extern__stdcall CV_SendLocalIPPort(int DeviceAddress,int port,char* ip=NULL);

extern__stdcall GetPort(int DeviceAddress,unsigned char *status);

extern__stdcall StartSearchDeviceIP(); // add by wtz 2015-9-9
extern__stdcall StopSearchDeviceIP(); // add by wtz 2015-9-9
extern__stdcall GetDeviceIPNumber(int *pNumber); // add by wtz 2015-9-11
extern__stdcall GetDeviceInfo(int index, char *IP, int *DevAddress); // add by wtz 2015-9-11

extern__stdcall GetAutoReadTCPClientNum(int *number); // add by wtz 2015-9-15
extern__stdcall GetAutoReadTCPClientInfo(int index,char *IP, bool *bAlive,
										SYSTEMTIME *lastDeadTime); // add by wtz 2015-9-15



#endif
