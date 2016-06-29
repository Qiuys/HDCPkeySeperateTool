#ifndef KEY_TOOL_MANAGER_H
#define KEY_TOOL_MANAGER_H
#include <cstdio>
#include <iostream>
#include "HDCPkeySeperateTool.h"
class KeyToolManager {
public:
	int setInFile(char * inFile);
	int setOutFile(char * outFile);
	int setParameters(int keyType, int headLength, int keyLength, int keyCountFormat);
	
private:
	int newHDCPKeySeperateTool();
	HDCPKeySeperateTool * HDCP_Tool;
	char * inFile, * outFile;
	int keyType;
};
#endif