; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Cloaddata
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HaarDWT.h"

ClassCount=4
Class1=CHaarDWTApp
Class2=CHaarDWTDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_HAARDWT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=Cloaddata
Resource4=IDD_INPUTDIG

[CLS:CHaarDWTApp]
Type=0
HeaderFile=HaarDWT.h
ImplementationFile=HaarDWT.cpp
Filter=N
LastObject=CHaarDWTApp

[CLS:CHaarDWTDlg]
Type=0
HeaderFile=HaarDWTDlg.h
ImplementationFile=HaarDWTDlg.cpp
Filter=D
LastObject=IDC_INVERSE_DWT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=HaarDWTDlg.h
ImplementationFile=HaarDWTDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_HAARDWT_DIALOG]
Type=1
Class=CHaarDWTDlg
ControlCount=18
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_LEN,edit,1350631552
Control6=IDC_EDIT_LEVL,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177543
Control10=IDC_LOAD,button,1342242816
Control11=IDC_DWT,button,1342242816
Control12=IDC_INVERSE_DWT,button,1342242816
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC1,static,1342177280
Control17=IDC_STATIC2,static,1342177280
Control18=IDC_STATIC3,static,1342177280

[DLG:IDD_INPUTDIG]
Type=1
Class=Cloaddata
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_ADDDTA,button,1342242816
Control3=IDC_ADDEDIT,edit,1350631552
Control4=IDC_FILEADD,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_INPUTLIST,SysListView32,1350631425

[CLS:Cloaddata]
Type=0
HeaderFile=loaddata.h
ImplementationFile=loaddata.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Cloaddata

