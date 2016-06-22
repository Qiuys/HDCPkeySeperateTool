#include <iostream>
#include <stdlib.h>
using namespace std;
#include "HDCPKeySeperateTool.h"
int main() {
	char *inFile = "E:/work/GS KEY/GS HDCP key/HDCP_Key.bin";
	//char *outFile = "E:/work/GS HDCP key/20151226/HDCP_KEY_500_24211-24710.bin";

	int newKeyLoc = 126710;//起始下标
	int newKeyCount = 1040;//每个文件要包含多少个KEY
	int filesCount = 1;//247;//总共要多少个文件

	for (int i=1;i <= filesCount;i++) {
		char *outFile = "E:/work/GS KEY/GS HDCP key/20160222/HDCP_LIENCE_";
		char newfileName[1000] = "";
		strcpy(newfileName, outFile);//构造文件名前缀

		char newKeyFirstLocString[1000] = "";
		_itoa((newKeyLoc+1), newKeyFirstLocString, 10);
		strcat(newfileName, newKeyFirstLocString);//将起始key编号写到文件名中

		strcat(newfileName, "_");

		char newKeyLastLocString[1000] = "";
		_itoa((newKeyLoc+newKeyCount), newKeyLastLocString, 10);
		strcat(newfileName, newKeyLastLocString);//将末尾key编号写到文件名中

		strcat(newfileName, "_");

		char newKeyCountString[100];
		_itoa(newKeyCount, newKeyCountString, 10);
		strcat(newfileName, newKeyCountString);//将key数量写到文件名中


		HDCPKeySeperateTool myTool(inFile, newfileName);
		myTool.seperateKeys(newKeyCount, newKeyLoc);

		newKeyLoc += newKeyCount;//更新下标
	}

	

	return 0;
}