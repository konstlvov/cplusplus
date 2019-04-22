// DeviceList.cpp : Implementation of CDeviceList
#include "stdafx.h"
#include "DevHelper.h"
#include "DeviceList.h"
#include <stdio.h>
#include <tchar.h>





//CDeviceList internal functions
CDeviceList::CDeviceList()
{
	if (! dl.empty() ) dl.clear();
	Refresh();
}

HRESULT CDeviceList::SetErrorInfo(const CString Description, const CString Source)
{
	ICreateErrorInfo *pcerrinfo;
	IErrorInfo *perrinfo;
	HRESULT hr;
	hr = CreateErrorInfo(&pcerrinfo);
	if ( FAILED(hr) ) return hr;
	hr = pcerrinfo->SetDescription( CComBSTR(Description) );
	if ( FAILED(hr) ) return hr;
	hr = pcerrinfo->SetSource( CComBSTR(Source) );
	if ( FAILED(hr) ) return hr;
  hr = pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &perrinfo);
  if (SUCCEEDED(hr))
  {
		hr = ::SetErrorInfo(0, perrinfo);
		perrinfo->Release();
	}
	pcerrinfo->Release();
	return S_OK;
}


// IDeviceList implementation
STDMETHODIMP CDeviceList::get_Count(long *pVal)
{
	*pVal = dl.size();
	return S_OK;
}


STDMETHODIMP CDeviceList::Refresh()
{
	//write some useless stuff
	if (! dl.empty() ) dl.clear();
	CDevInfo di; // device info, will be pushed in vector
	CDevInfoQuery diq; // helper class for quering device information
	DevPropValue dp; // structure for quering device properties
	ZeroMemory(&dp, sizeof (dp) );

	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i = 0; // counter
	
	// Create a HDEVINFO with all present devices.
	hDevInfo = SetupDiGetClassDevs(NULL, 0, /* Enumerator */ 0, DIGCF_PRESENT | DIGCF_ALLCLASSES );
  assert(INVALID_HANDLE_VALUE != hDevInfo);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		SetErrorInfo("Ќевозможно получить перечисление устройств: SetupDiGetClassDevs вернула INVALID_HANDLE_VALUE", "CDeviceList::Refresh()");
		return E_FAIL;
	}
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i=0;SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData);i++)
	{
					 di.Handle = DeviceInfoData.DevInst; // handle of device instance

           ZeroMemory(&dp, sizeof (dp) );
           DWORD ret = 0;
           // device description
           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, &dp);
           assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_DEVICEDESC"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.Description = (LPTSTR) dp.PropertyValue;


           //location information
           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_LOCATION_INFORMATION, &dp);
					 assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_LOCATION_INFORMATION"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.LocationInformation = (LPTSTR) dp.PropertyValue;

           //friendly name
           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME, &dp);
           assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_FRIENDLY_NAME"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.FriendlyName = (LPTSTR) dp.PropertyValue;

           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_SERVICE, &dp);
           assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_SERVICE"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.Service = (LPTSTR) dp.PropertyValue;

           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME, &dp);
           assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_PHYSICAL_DEVICE_OBJECT_NAME"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.PhysicalDeviceObjectName = (LPTSTR) dp.PropertyValue;

           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_DRIVER, &dp);
           assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_DRIVER"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.Driver = (LPTSTR) dp.PropertyValue;

           ret = diq.GetPropValue(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID, &dp);
           assert(0 == ret);
					 if (0 != ret)
					 {
							CString ei; // error info
							ei.Format( _T("ќшибка %d при попытке получить SPDRP_HARDWAREID"), ret);
							SetErrorInfo(ei, "CDeviceList::Refresh()");
							return E_FAIL;
					 }
					 di.HardwareID = (LPTSTR) dp.PropertyValue;

					 dl.push_back(di);
	}
	
	if ( GetLastError()!=NO_ERROR && GetLastError()!=ERROR_NO_MORE_ITEMS )
	{
		// Insert error handling here.
		return 1;
	}
	//  Cleanup
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return S_OK;
}




STDMETHODIMP CDeviceList::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDeviceList
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (IsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDeviceList::get_Description(long Index, BSTR *pVal)
{
	
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства Description: выход значени€ индекса за пределы массива", "CDeviceList::get_Description");
		return E_FAIL;
	}
	
	*pVal = dl.at(Index).Description.AllocSysString();
	return S_OK;
}


STDMETHODIMP CDeviceList::get_LocationInformation(long Index, BSTR *pVal)
{
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства LocationInformation: выход значени€ индекса за пределы массива", "CDeviceList::get_LocationInformation");
		return E_FAIL;
	}
	*pVal = dl.at(Index).LocationInformation.AllocSysString();
	return S_OK;
}

STDMETHODIMP CDeviceList::get_Handle(long Index, long *pVal)
{
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства LocationInformation: выход значени€ индекса за пределы массива", "CDeviceList::get_Handle");
		return E_FAIL;
	}
	*pVal = dl.at(Index).Handle;
	return S_OK;
}

STDMETHODIMP CDeviceList::get_FriendlyName(long Index, BSTR *pVal)
{
	
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства FriendlyName: выход значени€ индекса за пределы массива", "CDeviceList::get_FriendlyName");
		return E_FAIL;
	}
	
	*pVal = dl.at(Index).FriendlyName.AllocSysString();
	return S_OK;
}

	
STDMETHODIMP CDeviceList::get_Service(long Index, BSTR *pVal)
{
	
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства Service: выход значени€ индекса за пределы массива", "CDeviceList::get_Service");
		return E_FAIL;
	}
	
	*pVal = dl.at(Index).Service.AllocSysString();
	return S_OK;
}

	
STDMETHODIMP CDeviceList::get_PhysicalDeviceObjectName(long Index, BSTR *pVal)
{
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства PhysicalDeviceObjectName: выход значени€ индекса за пределы массива", "CDeviceList::get_PhysicalDeviceObjectName");
		return E_FAIL;
	}
	
	*pVal = dl.at(Index).PhysicalDeviceObjectName.AllocSysString();
	return S_OK;
}

	
STDMETHODIMP CDeviceList::get_Driver(long Index, BSTR *pVal)
{
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства Driver: выход значени€ индекса за пределы массива", "CDeviceList::get_Driver");
		return E_FAIL;
	}
	*pVal = dl.at(Index).Driver.AllocSysString();
	return S_OK;
}

	
STDMETHODIMP CDeviceList::get_HardwareID(long Index, BSTR *pVal)
{
	
	if (dl.size() < 0 || Index > dl.size() - 1)
	{
		SetErrorInfo("Ќевозможно вернуть значение свойства HardwareID: выход значени€ индекса за пределы массива", "CDeviceList::get_HardwareID");
		return E_FAIL;
	}
	
	*pVal = dl.at(Index).HardwareID.AllocSysString();
	return S_OK;
}
