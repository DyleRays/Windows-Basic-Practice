//
// Define below GUIDs
//

#pragma once

#include <initguid.h>
//
// Device Interface GUID.
// Used by all WinUsb devices that this application talks to.
// Must match "DeviceInterfaceGUIDs" registry value specified in the INF file.
// 5d807e8a-2b68-4b07-a677-2182c2ac23fb
//
DEFINE_GUID(GUID_DEVINTERFACE_STM32USBDriver,0x5d807e8a, 0x2b68, 0x4b07, 0xa6, 0x77, 0x21, 0x82, 0xc2, 0xac, 0x23, 0xfb);

typedef struct _DEVICE_DATA 
{
	BOOL                    HandlesOpen;
	WINUSB_INTERFACE_HANDLE WinusbHandle;
	HANDLE                  DeviceHandle;
	TCHAR                   DevicePath[MAX_PATH];
} DEVICE_DATA, *PDEVICE_DATA;

typedef struct _PIPE_ID
{
	UCHAR  PipeInId;
	UCHAR  PipeOutId;
}PIPE_ID,*PPIPE_ID;

HRESULT OpenDevice( _Out_     PDEVICE_DATA DeviceData,
					_Out_opt_ PBOOL        FailureDeviceNotFound);

VOID CloseDevice( _Inout_ PDEVICE_DATA DeviceData);

HRESULT RetrieveDevicePath(_Out_bytecap_(BufLen) LPTSTR DevicePath,
						   _In_                  ULONG  BufLen,
						   _Out_opt_             PBOOL  FailureDeviceNotFound);

BOOL SendDatatoDefaultEndpoint(WINUSB_INTERFACE_HANDLE hDeviceHandle);
BOOL QueryDeviceEndpoints(WINUSB_INTERFACE_HANDLE hDeviceHandle, PIPE_ID* pipeid);
