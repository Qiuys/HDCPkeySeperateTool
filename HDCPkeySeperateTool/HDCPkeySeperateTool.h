#ifndef HDCP_KEY_SEPERATE_TOOL_H
#define HDCP_KEY_SEPERATE_TOOL_H
#include <cstdio>
#include <iostream>
class HDCPKeySeperateTool {
public:
	/*
	parameter:
	inFile:file path of input HDCP key file
	outFile:file path  of target HDCP key file
	*/
	HDCPKeySeperateTool(char * inFile,char* outFile);
	~HDCPKeySeperateTool();

	/*
	parameter:
	newKeyCount:the count of key that will seperated into target HDCP key file
	newKeyLoc:the first index of key in input HDCP key file that begin to seperate into target HDCP key file
	*/
	int seperateKeys(int newKeyCount, int newKeyLoc);

private:
	FILE * InFile, *OutFile;
	int keyCount;//key count of input file
	const static int keySize = 308;// size of one HDCP key
	char tempKey[keySize];

	int openFiles(char * inFile, char* outFile);
	void closeFiles();
	/*
	do not use this function
	change number of key int  to int array
	prepare to write into file
	*/
	void setHDCPKeyCountHelp(int sum, int* mm);

	/*
	change number of key int  to int array
	prepare to write into file
	*/
	void setHDCPKeyCountHelpNew(int sum, int* mm);

	void setHDCPKeyCountHelpThird(int sum, int* mm);

	/*
	do not use this function
	*/
	int getHDCPKeyCount();

	/*
	get HDCP key count from file
	*/
	int getHDCPKeyCountNew();

	int getHDCPKeyCountThird();

	/*
	get a key from file then store in char* aKey.
	return 0 when success
	return -1 when fail
	*/
	int getOneKey(char* aKey);

	/*
	put a key to file
	return the size of key
	*/
	int setOneKey(char* aKey);

	/*
	do not use this function
	put 4 byte into file.represent the number of key in the file.
	*/
	int setHDCPKeyCount(int newKeyCount);

	/*
	put 4 byte into file.represent the number of key in the file.
	*/
	int setHDCPKeyCountNew(int newKeyCount);

	int setHDCPKeyCountThird(int newKeyCount);

	/*
	get current key location in inFile
	*/
	int getLocationOfKey();

	/*
	set a new key location in inFile
	*/
	int setLocationOfKey(int loc);
};
#endif