// TPWrapperProxy.h

#pragma once

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
		 char* softwareVersion,
		 char** errorMessage);

int __stdcall StartRecipeLogAcquisition(int index, 
		 char* motorolaModel,
		 char* family,
		 char* technology,
		 char* XcvrNumber,
		 char* equipmentId, 
		 char* softwareId,
		 char* recipeName,
		 char* shopOrder,
		 char** errorMessage);


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
		 char** errorMessage);
	

int __stdcall EndRecipeLogAcquisition(int index, 
		 char* masterTestResult,
		 char* trackId,
		 char** errorMessage);

char* __stdcall GetParameterValueFromStringResponse(char* stringResponse,
		 char* gpsParameterName);

int __stdcall Request(char* unitTrackId, 
		 char* stationType,
		 char* stationCode,
		 char* testMachineId,
		 char* orderNumber,
		 char* Uri,
		 char** responseFromServer,
		 char** errorMessage);