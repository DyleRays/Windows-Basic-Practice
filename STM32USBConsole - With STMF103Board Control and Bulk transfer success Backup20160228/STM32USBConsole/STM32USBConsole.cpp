// STM32USBConsole.cpp : 定义控制台应用程序的入口点。
//


#include "USBHeaders.h"
#include "stdio.h"

LONG __cdecl _tmain(LONG Argc, LPTSTR* Argv)
{
	printf("Hellow USB\n");	
	printf("\n");
	printf("\n");

	/* use API OpenDevice*/
	/*
	DEVICE_DATA STM32Dev;
	BOOL OpenR;
	OpenDevice(&STM32Dev,&OpenR);
	*/

	
	CHAR DevicePath[512];
	BOOL R2;
	BOOL R3;
	R3 = RetrieveDevicePath(DevicePath,512,&R2);
	printf("==============STM32USB Device Path=========\n");
	printf("STM32USBDevice DevicePath:%s\n", DevicePath);
	printf("R2:%x\n",R2);
	printf("R3:%x\n",R3);
	printf("\n");
	printf("\n");

	HANDLE hDev = NULL;
	hDev = CreateFile(DevicePath,
					  GENERIC_WRITE | GENERIC_READ,FILE_SHARE_WRITE | FILE_SHARE_READ,
					  NULL,
					  OPEN_EXISTING,
					  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
					  NULL);
	printf("===========Handle Created by CreateFile Func=========\n");
	printf("Created Handle:%04x\n",hDev);
	if (hDev == INVALID_HANDLE_VALUE)
	{
		printf("Handle Invalid\n");
	}
	else
	{
		printf("hDev:%8x\n", hDev);
		printf("Handle is OK\n");
	}
	printf("\n");
	printf("\n");

	WINUSB_INTERFACE_HANDLE STM32USBInterfaceHandle;
	WinUsb_Initialize(hDev, &STM32USBInterfaceHandle);
	printf("===Interface Handle Created by WinUsb_Initialize===\n");
	printf("InterfaceHandle:%8x\n",STM32USBInterfaceHandle);
	printf("\n");
	printf("\n");
	


	ULONG SpeedLen=1;
	void* Buffer;
	Buffer = malloc(1);
	BOOL SpeedR;
	SpeedR = WinUsb_QueryDeviceInformation(STM32USBInterfaceHandle,DEVICE_SPEED,&SpeedLen,Buffer);
	printf("==============USB Device Information==============\n");
	printf("SpeedResult:%04x\n",SpeedR);
	printf("Speed:%04x\n", *(unsigned char*)Buffer);
	printf("\n");
	printf("\n");
	
	USB_INTERFACE_DESCRIPTOR STM32InterfaceDes;
	WinUsb_QueryInterfaceSettings(STM32USBInterfaceHandle,0,&STM32InterfaceDes);
	printf("===========Interface Descripter ==========\n");
	printf("Interface Alternate Setting:%2x\n",STM32InterfaceDes.bAlternateSetting);
	printf("EndpointNum:%2x\n",STM32InterfaceDes.bNumEndpoints);
	printf("InterfaceNum:%2x\n",STM32InterfaceDes.bInterfaceNumber);
	printf("Length:%2x\n",STM32InterfaceDes.bLength);
	printf("DescriptorType:%2x\n",STM32InterfaceDes.bDescriptorType);
	printf("InterfaceClass:%2x\n",STM32InterfaceDes.bInterfaceClass);
	printf("InterfaceProtocol:%2x\n",STM32InterfaceDes.bInterfaceProtocol);
	printf("InterfaceSubClass:%2x\n",STM32InterfaceDes.bInterfaceSubClass);
	printf("Interface:%2x\n",STM32InterfaceDes.iInterface);
	printf("\n");
	printf("\n");

	WINUSB_PIPE_INFORMATION PipeInfo;
	WinUsb_QueryPipe(STM32USBInterfaceHandle,0,0,&PipeInfo);
	printf("============Interface Pipe Information===========\n");
	printf("Pipe 0 Type:%04x\n",PipeInfo.PipeType);
	printf("Pipe 0 ID:%2x\n",PipeInfo.PipeId);
	printf("Pipe 0 MaxPacketSize:%4x\n",PipeInfo.MaximumPacketSize);
	printf("Pipe 0 Interval:%4x\n",PipeInfo.Interval);
	printf("\n");
	WinUsb_QueryPipe(STM32USBInterfaceHandle, 0, 1, &PipeInfo);
	printf("Pipe 1 Type:%04x\n", PipeInfo.PipeType);
	printf("Pipe 1 ID:%2x\n", PipeInfo.PipeId);
	printf("Pipe 1 MaxPacketSize:%4x\n", PipeInfo.MaximumPacketSize);
	printf("Pipe 1 Interval:%4x\n", PipeInfo.Interval);
	printf("\n");
	printf("\n");

	PIPE_ID STM32PipeID;
	BOOL PipeRes;
	PipeRes = QueryDeviceEndpoints(STM32USBInterfaceHandle,&STM32PipeID);
	printf("============Pipe Information===========\n");
	printf("PipeRes:%2x\n",PipeRes);
	printf("STM32PipeID.PipeInId:%2x\n",STM32PipeID.PipeInId);
	printf("STM32PipeID.PipeOutId:%2x\n",STM32PipeID.PipeOutId);
	printf("\n");
	printf("\n");

	/*
	ULONG ValueLen = 256;
	ULONG PipeBuff[256] = { 0 };
	void* pPipeBuff = PipeBuff;
	WinUsb_GetPipePolicy(STM32USBInterfaceHandle,0x18,0x01,&ValueLen,pPipeBuff);
	printf("============Interface PipePolicy===========\n");
	printf("xxxxx:%04x",PipeBuff[0]);
	printf("\n");
	printf("\n");
	*/

	
	/*
	WINUSB_SETUP_PACKET USBStandGetDescriptorSetup;
	USBStandGetDescriptorSetup.RequestType = 0x80;
	USBStandGetDescriptorSetup.Request     = 0x06;
	USBStandGetDescriptorSetup.Value       = 0x0100;
	USBStandGetDescriptorSetup.Index       = 0x0000;
	USBStandGetDescriptorSetup.Length      = 0x0012;

	UCHAR Command[18] = {};
	ULONG TransLen = 1;
	BOOL TransRes;
	TransRes = WinUsb_ControlTransfer(STM32USBInterfaceHandle, USBStandGetDescriptorSetup, Command, 18, &TransLen, NULL);
	printf("============Control Transfer one byte example===========\n");
	printf("Transfer Result:%04x\n",TransRes);
	printf("TransLen:%04x",TransLen);
	printf("Command return Data:");
	for (int index = 0; index < 18; index++)
	{
		printf("%2x", Command[index]);
	}
	printf("\n");
	printf("\n");
	

	
	WINUSB_SETUP_PACKET USBStandGetConfig;
	USBStandGetConfig.RequestType = 0x80;
	USBStandGetConfig.Request = 0x08;
	USBStandGetConfig.Value = 0x0000;
	USBStandGetConfig.Index = 0x0000;
	USBStandGetConfig.Length = 0x0001;
	TransRes = WinUsb_ControlTransfer(STM32USBInterfaceHandle, USBStandGetConfig, Command, 9, &TransLen, NULL);
	printf("============Control Transfer GetConfig===========\n");
	printf("Transfer Result:%04x\n", TransRes);
	printf("TransLen:%04x", TransLen);
	printf("Command return Data:");
	for (int index = 0; index < 9; index++)
	{
		printf("%2x", Command[index]);
	}
	printf("\n");
	printf("\n");
	*/
	
	
	/*
	WINUSB_SETUP_PACKET USBSetConfig;
	USBSetConfig.RequestType = 0x00;
	USBSetConfig.Request = 0x09;
	USBSetConfig.Value = 0x0001;
	USBSetConfig.Index = 0x0000;
	USBSetConfig.Length = 0x0000;
	UCHAR SendBUFF[6] = {0};
	ULONG SetLen = 1;
	BOOL SetRes;
	SetRes = WinUsb_ControlTransfer(STM32USBInterfaceHandle,USBSetConfig,SendBUFF,0,&SetLen,NULL);
	printf("============Set USB Into Configuration 1 ==============");
	printf("SetRes:%2x\n",SetRes);
	printf("\n");
	printf("\n");
	*/
	

	
	UCHAR ExampleData[4] = { 0x00, 0x01, 0xfe, 0xff };
	ULONG BulkLen=1;
	BOOL BulkRes;
	BulkRes = WinUsb_WritePipe(STM32USBInterfaceHandle,0x01,ExampleData,4,&BulkLen,NULL);
	printf("============Bulk Transfer four byte example===========\n");
	printf("Transfer Result:%2x\n", BulkRes);
	printf("TransLen:%04x", BulkLen);
	printf("\n");
	printf("\n");
	

	CloseHandle(hDev);
	getchar();
	return 0;
}

