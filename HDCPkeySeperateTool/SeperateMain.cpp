#include <iostream>
#include <stdlib.h>
#include <afx.h>
using namespace std;
#include "HDCPKeySeperateTool.h"
/*int main() {
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
}*/
/*
int readKeyCountFormat1(FILE * InFile, int headLength);
int checkKeyFormat(char * inFile, int headLength, int keyLength, int keyCountFormat);
int checkCommand(int keyBeginNum, int keyCount);
int totalKeyCount = 10;//文件中key的总个数
*/
/*将1000个key显示为 00 00 03 E8*/
/*
int readKeyCountFormat1(FILE * InFile, int headLength) {
	int m;//current byte that getted from file
	int sum = 0;//count of key
	int weights = 1;//weight of current byte
	for (int i = 1;i < headLength;i++) {
		weights *= 256;
	}

	for (int i = 0;i < headLength;i++) {
		m = fgetc(InFile);
		sum += m*weights;
		weights /= 256;
	}
	return sum;
}
*/
//1.第一步，检查输入的参数与key文件是否匹配。
/*int checkKeyFormat(char * inFile, int headLength, int keyLength ,int keyCountFormat) {
	//1. check inFile
	FILE * tempInFile;
	tempInFile = fopen(inFile, "rb");
	if (tempInFile == NULL) {
		//open file failed
		cout << "Open Key File Error!" << endl;
		fclose(tempInFile);
		return 1;// return -1,means the key file can not be opened.Maybe it is not exist.
	}

	//2. check headLength
	fseek(tempInFile, 0, SEEK_END);
	int fileSize = ftell(tempInFile);
	cout << "File size is : " << fileSize << endl;
	if (headLength >= fileSize) {
		cout << "headLength is longer then the file!" << endl;
		fclose(tempInFile);
		return 2;
	}
	fseek(tempInFile, 0, SEEK_SET);

	//3. check keyLength
	if (keyLength <= 0) {
		cout << "keyLength is wrong!" << endl;
		fclose(tempInFile);
		return 3;
	}

	//4. check keyLength and keyCountFormat
	int readKeyCount1 = readKeyCountFormat1(tempInFile, headLength);
	cout << "readKeyCountFormat1 = " << readKeyCount1 << endl;
	if (headLength + readKeyCount1*keyLength != fileSize) {
		cout << "keyLength or keyCountFormat not mach the file!" << endl;
		fclose(tempInFile);
		return 4;
	}

	cout << "Check Successful!" << endl;
	fclose(tempInFile);
	return 0;
}
*/

//2.第二步，检查需要提取的key数量是否会超出key文件的范围
/*
param keyBeginNum : The number of first key to be seperated from file.
param keyCount : The count of keys to be seperated from file.
return : 0:Can be seperated successfully 1:param is unavailable
		 2:The keys in file are not enough
*/
/*
int checkCommand(int keyBeginNum, int keyCount) {
	if (keyBeginNum <= 0 || keyCount <= 0) {
		cout << "keyBeginNum or keyCount is unavailable!" << endl;
		return 1;
	}
	int keyLastNum = keyBeginNum + keyCount - 1;
	if (keyLastNum > totalKeyCount) {
		cout << "keys are not enough for you!" << endl;
		return 2;
	}
	return 0;
}

*/


//test function checkKeyFormat
int main() {
	//char *inFile = "E:/work/VS/tempTestKey/HDCP_KEY_10_1-10.bin";
	//checkKeyFormat(inFile,4,308,1);

	char *  out = "C:/Users/sorou/Desktop/testfolder/";
	char * name = "ha|ha";
	
	// \ / : * ? " < > |
	
	if (name != NULL && name !="") {
		char * temp = NULL;
		char * donotuse[10] = { "/","\\",":","*","?","\"","<",">","|"," "};
		int donotuseLen = sizeof(donotuse) / sizeof(char*);
		for (int i = 0;i < donotuseLen;i++) {
			cout << "Finding " << donotuse[i]<< endl;
			temp = strstr(name, donotuse[i]);
			if (temp != NULL) {
				cout << "Error file prefix! Contains \'" << donotuse[i]<< "\'" << endl;
				temp = NULL;
			}
		}
	}
	cout << "Finish" << endl;

	return 0;
}

