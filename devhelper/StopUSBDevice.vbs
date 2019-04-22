Dim dl
Set dl = CreateObject("DEVHELPER.DeviceList")
Dim helper
Set helper = CreateObject("DevHelper.USBSTORHelper")
Dim usbstor_handle
usbstor_handle = 0
For Index = 0 To dl.Count - 1 
	WScript.Echo dl.Handle(Index) _ 
	& ": " & dl.Description(Index) _ 
	& ": " & dl.LocationInformation (Index) _ 
	& " - " & dl.PhysicalDeviceObjectName(Index) _
	& " - " & dl.Service (Index)
	If  dl.Service(Index) = "USBSTOR" Then usbstor_handle = dl.Handle(Index)
Next
Set dl = Nothing
If usbstor_handle <> 0 Then
	WScript.Echo "������� ��������� �������� ������ USB, Handle = " & usbstor_handle & VbCrLf & "����� ����������� ������� ���������"
	helper.StopDevice (usbstor_handle)
	WScript.Echo "���������� �������� ������ USB ������� �����������"
End If
Set helper = Nothing
