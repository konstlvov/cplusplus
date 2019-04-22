#include "stdafx.h"
#include "DevInfoQuery.h"

CDevInfoQuery::CDevInfoQuery()
{
	_buf = 0;
}


CDevInfoQuery::~CDevInfoQuery()
{
	FreeAndNullBuffer();
}


void CDevInfoQuery::FreeAndNullBuffer()
{
	if (_buf)
  {
  	LocalFree(_buf);
    _buf = 0;
  }
}

DWORD CDevInfoQuery::GetPropValue(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, DWORD Property, DevPropValue *pValue)
{
	FreeAndNullBuffer();
	DWORD buffersize = 0;
	DWORD dwLastError = 0;
	//
	// Call function with null to begin with,
	// then use the returned buffer size
	// to Alloc the buffer. Keep calling until
	// success or an unknown failure.
	//
	while (!SetupDiGetDeviceRegistryProperty(
		DeviceInfoSet,
		DeviceInfoData,
		Property,
		&pValue->RegDataType,
		(PBYTE)_buf,
		buffersize,
		&buffersize))
	{
		dwLastError = GetLastError();
		if (ERROR_INSUFFICIENT_BUFFER == dwLastError)
		{
			// Change the buffer size.
			FreeAndNullBuffer();
			_buf = (char*) LocalAlloc(LPTR,buffersize);
		}
		else
		{
			// Insert error handling here.
			dwLastError = GetLastError();
			break;
    }
  }
  pValue->PropertyValue = (PBYTE)_buf;
	//return dwLastError; // 0 - no error
	return 0;
}
