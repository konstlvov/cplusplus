// USBSTORHelper.h : Declaration of the CUSBSTORHelper

#ifndef __USBSTORHELPER_H_
#define __USBSTORHELPER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUSBSTORHelper
class ATL_NO_VTABLE CUSBSTORHelper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUSBSTORHelper, &CLSID_USBSTORHelper>,
	public ISupportErrorInfo,
	public IDispatchImpl<IUSBSTORHelper, &IID_IUSBSTORHelper, &LIBID_DEVHELPER>
{
public:
	CUSBSTORHelper()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_USBSTORHELPER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUSBSTORHelper)
	COM_INTERFACE_ENTRY(IUSBSTORHelper)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

//ISupportErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUSBSTORHelper
private:
		HRESULT SetErrorInfo (const CString Description, const CString Source);
public:
	//STDMETHOD(DoSomething)();
	STDMETHOD(StopDevice)(/*[in]*/ long DevHandle);
};

#endif //__USBSTORHELPER_H_
