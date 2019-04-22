// USBSTORHelper.cpp : Implementation of CUSBSTORHelper
#include "stdafx.h"
#include "DevHelper.h"
#include "USBSTORHelper.h"



//ISupportErrorInfo
STDMETHODIMP CUSBSTORHelper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUSBSTORHelper
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (IsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CUSBSTORHelper
HRESULT CUSBSTORHelper::SetErrorInfo(const CString Description, const CString Source)
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


STDMETHODIMP CUSBSTORHelper::StopDevice(long DevHandle)
{
	HMACHINE hMachine = 0;
  long res = CM_Connect_Machine(NULL, &hMachine);
  
  if (CR_SUCCESS != res)
  {
		CString em;
		em.Format(_T("CM_Connect_Machine could not obtain machine handle, returned value = 0x%X, passed DevHandle = %d"), res, DevHandle);
		SetErrorInfo(em, _T("CUSBSTORHelper::StopDevice"));
    return E_FAIL;
  }

	res = CM_Request_Device_Eject_Ex(
  	DevHandle,
    NULL,
    NULL,
    0,
    NULL,
    hMachine);
	if (CR_SUCCESS != res)
	{
		CString em;
		em.Format(_T("CM_Request_Device_Eject_Ex failed, returned value = 0x%X, passed DevHandle = %d"), res, DevHandle);
		SetErrorInfo(em, _T("CUSBSTORHelper::StopDevice") );
    return E_FAIL;
	}
	return S_OK;
}


//STDMETHODIMP CUSBSTORHelper::DoSomething()
//{	MessageBox(0, _T("Doing something"), _T("DevHelper.USBSTORHelper test method"), MB_OK);
//	return S_OK;
//}
