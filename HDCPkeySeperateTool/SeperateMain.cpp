#include <iostream>
#include <stdlib.h>
using namespace std;
#include "HDCPKeySeperateTool.h"
int main() {
	char *inFile = "E:/work/GS KEY/GS HDCP key/HDCP_Key.bin";
	//char *outFile = "E:/work/GS HDCP key/20151226/HDCP_KEY_500_24211-24710.bin";

	int newKeyLoc = 126710;//��ʼ�±�
	int newKeyCount = 1040;//ÿ���ļ�Ҫ�������ٸ�KEY
	int filesCount = 1;//247;//�ܹ�Ҫ���ٸ��ļ�

	for (int i=1;i <= filesCount;i++) {
		char *outFile = "E:/work/GS KEY/GS HDCP key/20160222/HDCP_LIENCE_";
		char newfileName[1000] = "";
		strcpy(newfileName, outFile);//�����ļ���ǰ׺

		char newKeyFirstLocString[1000] = "";
		_itoa((newKeyLoc+1), newKeyFirstLocString, 10);
		strcat(newfileName, newKeyFirstLocString);//����ʼkey���д���ļ�����

		strcat(newfileName, "_");

		char newKeyLastLocString[1000] = "";
		_itoa((newKeyLoc+newKeyCount), newKeyLastLocString, 10);
		strcat(newfileName, newKeyLastLocString);//��ĩβkey���д���ļ�����

		strcat(newfileName, "_");

		char newKeyCountString[100];
		_itoa(newKeyCount, newKeyCountString, 10);
		strcat(newfileName, newKeyCountString);//��key����д���ļ�����


		HDCPKeySeperateTool myTool(inFile, newfileName);
		myTool.seperateKeys(newKeyCount, newKeyLoc);

		newKeyLoc += newKeyCount;//�����±�
	}

	

	return 0;
}