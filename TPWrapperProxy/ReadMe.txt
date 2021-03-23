========================================================================
    DYNAMIC LINK LIBRARY : TPWrapperProxy Project Overview
========================================================================

AppWizard has created this TPWrapperProxy DLL for you.  

This file contains a summary of what you will find in each of the files that
make up your TPWrapperProxy application.

TPWrapperProxy.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

TPWrapperProxy.cpp
    This is the main DLL source file.

TPWrapperProxy.h
    This file contains a class declaration.

AssemblyInfo.cpp
	Contains custom attributes for modifying assembly metadata.
	
/////////////////////////////////////////////////////////////////////////////
TPWrapperProxy Usage:

HMODULE hDll = LoadLibrary("TPWrapperProxy.dll");
if (!hDll)
	return;

typedef outputType (__stdcall *NAME_OF_FUNCTION)(inputType, inputType, ...);

NAME_OF_FUNCTION NameOfFunction = (NAME_OF_FUNCTION)GetProcAddress(hDll, "NameOfFunction");
if (!NameOfFunction)
	return;

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
