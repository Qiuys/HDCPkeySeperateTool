#ifndef KEY_TOOL_MANAGER_H
#define KEY_TOOL_MANAGER_H
#include <cstdio>
#include <iostream>
#include "HDCPkeySeperateTool.h"
class KeyToolManager {
public:
	int setInFile(char * inFile);
	int setOutFile(char * out, char * filePrefix);
	int setKeyType(int keyType);
	int setHDCPKeyFormat(int headLength, int keyLength, int keyCountFormat, int aimkeyCountFormat);
	int setHDCPKeySeperateParam(int KeyBeginNum, int KeyEachFile, int KeyFileCount);
	int startSeperate();

private:
	HDCPKeySeperateTool * HDCP_Tool;
	char * inFile, *outFolder, *filePrefix;
	int keyType;
	int keyBeginNum, keyEachFile, keyFileCount;
};
#endif