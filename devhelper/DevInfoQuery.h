//---------------------------------------------------------------------------
#ifndef UDevInfoQueryH
#define UDevInfoQueryH
//---------------------------------------------------------------------------

struct DevPropValue
{
	DWORD Property;
	DWORD RegDataType;
	PBYTE PropertyValue;
};

class CDevInfoQuery
{
private:
	void *_buf;
  void FreeAndNullBuffer();
public:
	CDevInfoQuery();
  virtual ~CDevInfoQuery();
  DWORD GetPropValue(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, DWORD Property, DevPropValue *pValue);
};
#endif

