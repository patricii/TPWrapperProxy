// This is the main DLL file.

#include "stdafx.h"
#include "TPWrapperProxy.h"

// TPWrapperProxy.h

#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace TPWrapper::LogParameters;
using namespace System::Runtime::InteropServices;
using namespace System::Threading;

namespace TPWrapperProxy
{
	public ref class Main
	{
	public:
		static bool DatabaseReaderFlag = false;
		
		static Dictionary<int, TPWrapper::LogDataAcquisition^>^ instancesOfDataAcquisition = 
			gcnew Dictionary<int, TPWrapper::LogDataAcquisition^>();
		
		static int  GetDataAcquisitionInstance(int index, TPWrapper::LogDataAcquisition^% currentLogProcess)
		{
			try
			{
				TPWrapperProxy::Main::instancesOfDataAcquisition->TryGetValue(index, currentLogProcess); 
				while(!currentLogProcess)
				{
					try
					{
						TPWrapperProxy::Main::instancesOfDataAcquisition->Add(index, 
							gcnew TPWrapper::LogDataAcquisition());
					}
					catch(...)
					{
					}
					TPWrapperProxy::Main::instancesOfDataAcquisition->TryGetValue(index, currentLogProcess); 
				}
				return 0;
			}
			catch(...)
			{
				return -1;
			}
		};
	};
}

int __stdcall InitLogAcquisition(int index, 
		 char* processCode,
		 char* stationCode,
		 char* softwareReleaseVersion,
		 char* siteCode,
		 char* logFormat, 
		 char* feedPath,
		 char* temporaryPath,
		 char* headerVersion,
		 char* testHeaderVersion,
		 char* fixtureId, 
		 char* computerMacAddress,
		 char* serverUri,
		 char* softwareVersion,
		 char** errorMessage)
{
	int nStatus = -1;
	// Get InitParametersInstance
	TPWrapper::LogParameters::InitParameters ^% currentParameters = gcnew TPWrapper::LogParameters::InitParameters();

	// Get DataAcquisitionInstance
	TPWrapper::LogDataAcquisition ^%currentLogProcess = gcnew TPWrapper::LogDataAcquisition();
	nStatus = TPWrapperProxy::Main::GetDataAcquisitionInstance(index, currentLogProcess);

	if (nStatus != 0)
	{
		return -1;
	}

	// Populate InitParameters
	currentParameters->serverUri = gcnew System::String(serverUri);
	currentParameters->computerMacAddress = gcnew System::String(computerMacAddress);
	currentParameters->feedPath = gcnew System::String(feedPath);
	currentParameters->fixtureId = gcnew System::String(fixtureId);
	currentParameters->headerVersion = gcnew System::String(headerVersion);
	currentParameters->processCode = gcnew System::String(processCode);
	currentParameters->siteCode = gcnew System::String(siteCode);
	currentParameters->softwareReleaseVersion = gcnew System::String(softwareReleaseVersion);
	currentParameters->softwareVersion = gcnew System::String(softwareVersion);
	currentParameters->stationCode = gcnew System::String(stationCode);
	currentParameters->temporaryPath = gcnew System::String(temporaryPath);
	currentParameters->testHeaderVersion = gcnew System::String(testHeaderVersion);
	currentParameters->logFormat = (TPWrapper::LogParameters::LogFileFormat) 
	Enum::Parse(TPWrapper::LogParameters::LogFileFormat::typeid, gcnew System::String(logFormat), true);

	// Call Init Function


	System::String ^%errorMessageSystemStringFormat = gcnew System::String(*errorMessage);
	nStatus = currentLogProcess->Init(currentParameters, errorMessageSystemStringFormat);
	
	*errorMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(errorMessageSystemStringFormat);

	if (nStatus != 0)
	{
		return -1;
	}

	return 0;
}

int __stdcall GetParameterValueFromStringResponse(char* stringResponse,
		 char* gpsParameterName, 
		 char** parameterValue)
{
	int nStatus = 0;

	System::String ^%parameterValueSystemStringFormat = gcnew System::String(*parameterValue);

	nStatus = TPWrapper::GpsAcquisition::GetParameterValueFromStringResponse(gcnew System::String(stringResponse),
											  gcnew System::String(gpsParameterName),
											  parameterValueSystemStringFormat);

	*parameterValue = (char*)(void*)Marshal::StringToHGlobalAnsi(parameterValueSystemStringFormat);

	return nStatus;
}

int __stdcall Request(char* unitTrackId, 
		 char* stationType,
		 char* stationCode,
		 char* testMachineId,
		 char* orderNumber,
		 char* Uri,
		 char** responseFromServer,
		 char** errorMessage)
{
	System::String ^%responseFromServerSystemStringFormat = gcnew System::String(*responseFromServer);
	System::String ^%errorMessageSystemStringFormat = gcnew System::String(*errorMessage);

	int nStatus = TPWrapper::GpsAcquisition::Request(gcnew System::String(unitTrackId), 
					gcnew System::String(stationType), 
					gcnew System::String(stationCode),
					gcnew System::String(testMachineId), 
					gcnew System::String(orderNumber), 
					gcnew System::String(Uri), 
					responseFromServerSystemStringFormat,
					errorMessageSystemStringFormat);

	*responseFromServer = (char*)(void*)Marshal::StringToHGlobalAnsi(responseFromServerSystemStringFormat);
	*errorMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(errorMessageSystemStringFormat);

	if (nStatus != 0)
	{
		return -1;
	}
	
	return 0;
}

int __stdcall StartRecipeLogAcquisition(int index, 
		 char* motorolaModel,
		 char* family,
		 char* technology,
		 char* XcvrNumber,
		 char* equipmentId, 
		 char* softwareId,
		 char* recipeName,
		 char* shopOrder,
		 char** errorMessage)
{
	int nStatus = -1;
	// Get StartRecipeParametersInstance
	TPWrapper::LogParameters::StartRecipeParameters ^% currentParameters = gcnew TPWrapper::LogParameters::StartRecipeParameters();

	// Get DataAcquisitionInstance
	TPWrapper::LogDataAcquisition ^%currentLogProcess = gcnew TPWrapper::LogDataAcquisition();
	nStatus = TPWrapperProxy::Main::GetDataAcquisitionInstance(index, currentLogProcess);

	if (nStatus != 0)
	{
		return -1;
	}

	// Populate StartRecipeParameters
	currentParameters->equipmentId = gcnew System::String(equipmentId);
	currentParameters->family = gcnew System::String(family);
	currentParameters->motorolaModel = gcnew System::String(motorolaModel);
	currentParameters->recipeName = gcnew System::String(recipeName);
	currentParameters->shopOrder = gcnew System::String(shopOrder);
	currentParameters->softwareId = gcnew System::String(softwareId);
	currentParameters->technology = gcnew System::String(technology);
	currentParameters->XcvrNumber = gcnew System::String(XcvrNumber);

	// Call Start Recipe Function
	System::String ^%errorMessageSystemStringFormat = gcnew System::String(*errorMessage);
	nStatus = currentLogProcess->StartRecipe(currentParameters, errorMessageSystemStringFormat);
		
	*errorMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(errorMessageSystemStringFormat);

	if (nStatus != 0)
	{
		return -1;
	}

	return 0;
}

int __stdcall EvalTestLogAcquisition(int index, 
		 char* testName, 
		 char* testResult,
		 double testValue,
		 double highLimit,
		 double lowLimit,
		 int attempts,
		 int retestFlag,
		 char* testCode,
		 char* testErrorMessage, 
		 char* testGroup,
		 char* testSpecName,
		 char* testSubGroup,
		 char* testTextValue,
		 char* testFailCode,
		 char** errorMessage)
{
	int nStatus = -1;
	// Get Eval ParametersInstance
	TPWrapper::LogParameters::EvalTestParameters ^% currentParameters = gcnew TPWrapper::LogParameters::EvalTestParameters();

	// Get DataAcquisitionInstance
	TPWrapper::LogDataAcquisition ^%currentLogProcess = gcnew TPWrapper::LogDataAcquisition();
	nStatus = TPWrapperProxy::Main::GetDataAcquisitionInstance(index, currentLogProcess);

	if (nStatus != 0)
	{
		return -1;
	}

	// Populate Eval Parameters
	currentParameters->attempts = attempts;
	currentParameters->highLimit = highLimit;
	currentParameters->lowLimit = lowLimit;
	currentParameters->retestFlag = retestFlag;
	currentParameters->testCode = gcnew System::String(testCode);
	currentParameters->testErrorMessage = gcnew System::String(testErrorMessage);
	currentParameters->testFailCode = gcnew System::String(testFailCode);
	currentParameters->testGroup = gcnew System::String(testGroup);
	currentParameters->testName = gcnew System::String(testName);
	currentParameters->testResult = (TPWrapper::LogParameters::TestResult) 
		Enum::Parse(TPWrapper::LogParameters::TestResult::typeid, gcnew System::String(testResult), true);
	currentParameters->testSpecName = gcnew System::String(testSpecName);
	currentParameters->testSubGroup = gcnew System::String(testSubGroup);
	currentParameters->testTextValue = gcnew System::String(testTextValue);
	currentParameters->testValue = testValue;

	// Call Eval test Function
	System::String ^%errorMessageSystemStringFormat = gcnew System::String(*errorMessage);
	nStatus = currentLogProcess->EvalTest(currentParameters, errorMessageSystemStringFormat);
		
	*errorMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(errorMessageSystemStringFormat);

	if (nStatus != 0)
	{
		return -1;
	}

	return 0;
}

int __stdcall EndRecipeLogAcquisition(int index, 
		 char* masterTestResult,
		 char* trackId,
		 char** errorMessage)
{
	int nStatus = -1;
	// Get EndRecipeParametersInstance
	TPWrapper::LogParameters::EndRecipeParameters ^% currentParameters = gcnew TPWrapper::LogParameters::EndRecipeParameters();
	
	// Get DataAcquisitionInstance
	TPWrapper::LogDataAcquisition ^%currentLogProcess = gcnew TPWrapper::LogDataAcquisition();
	nStatus = TPWrapperProxy::Main::GetDataAcquisitionInstance(index, currentLogProcess);

	if (nStatus != 0)
	{
		return -1;
	}

	// Populate EndRecipeParameters
	currentParameters->masterTestResult = (TPWrapper::LogParameters::TestResult) 
		Enum::Parse(TPWrapper::LogParameters::TestResult::typeid, gcnew System::String(masterTestResult), true);
	currentParameters->trackId = gcnew System::String(trackId);

	// Call End Recipe Function
	System::String ^%errorMessageSystemStringFormat = gcnew System::String(*errorMessage);
	nStatus = currentLogProcess->EndRecipe(currentParameters, errorMessageSystemStringFormat);
		
	*errorMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(errorMessageSystemStringFormat);

	if (nStatus != 0)
	{
		return -1;
	}

	return 0;
}

