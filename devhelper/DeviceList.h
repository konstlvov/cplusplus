// DeviceList.h : Declaration of the CDeviceList

#ifndef __DEVICELIST_H_
#define __DEVICELIST_H_

#include "resource.h"       // main symbols

#include <assert.h>

#include <vector>

#include "DevInfoQuery.h"


using namespace std;

struct CDevInfo
{
	DEVINST Handle;
	CString Description;
	CString LocationInformation;
	CString FriendlyName;
	CString Service;
	CString PhysicalDeviceObjectName;
	CString Driver;
	CString HardwareID;
	CDevInfo()
	{
		Handle = 0;
		Description = "";
		LocationInformation = "";
		FriendlyName = "";	
		Service = "";
		PhysicalDeviceObjectName = "";
		Driver = "";
		HardwareID = "";
	}
};

/////////////////////////////////////////////////////////////////////////////
// CDeviceList
class ATL_NO_VTABLE CDeviceList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDeviceList, &CLSID_DeviceList>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDeviceList, &IID_IDeviceList, &LIBID_DEVHELPER>
{
public:
	CDeviceList();
DECLARE_REGISTRY_RESOURCEID(IDR_DEVICELIST)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDeviceList)
	COM_INTERFACE_ENTRY(IDeviceList)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

//CDeviceList members and functions
private:
	vector <CDevInfo> dl; // device list
	HRESULT SetErrorInfo (const CString Description, const CString Source);
// IDeviceList
public:
	STDMETHOD(get_Handle)(/*[in]*/ long Index, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_LocationInformation)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);


	STDMETHOD(get_FriendlyName)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Service)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_PhysicalDeviceObjectName)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Driver)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_HardwareID)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);

	STDMETHOD(Refresh)();
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
};

#endif //__DEVICELIST_H_
