#include "HDCPKeySeperateTool.h"
using namespace std;

HDCPKeySeperateTool::HDCPKeySeperateTool(char * inFile, char* outFile) {
	if (openFiles(inFile, outFile)==-1) {
		cout << "Opening Files Error!" << endl;
		exit(-1);
	}

	keyCount = getHDCPKeyCountNew();
	if (keyCount<=0) {
		cout << "keyCount Error!" << endl;
		exit(-1);
	}
	else {
		cout << "Total Key Count Is : " << keyCount << endl;
	}
}

HDCPKeySeperateTool::~HDCPKeySeperateTool() {
	closeFiles();
}

int HDCPKeySeperateTool::openFiles(char * inFile, char* outFile) {
	InFile = fopen(inFile, "rb");
	OutFile = fopen(outFile, "ab");
	if (InFile == NULL || OutFile == NULL) {
		return -1;
	}
	return 0;
}

void HDCPKeySeperateTool::closeFiles() {
	if(InFile!=NULL)
		fclose(InFile);
	if(OutFile!=NULL)
		fclose(OutFile);
}

/*
do not use this function
*/
int HDCPKeySeperateTool::getHDCPKeyCount() {
	int m;//current byte that getted from file
	int sum = 0;//count of key
	int digit = 0;//a digit of current HEX byte
	int weights = 10000000;//weight of current digit

	for (int i = 0;i < 4;i++) {
		m = fgetc(InFile);
		digit = m / 16;
		sum += (digit*weights);
		weights /= 10;

		digit = m % 16;
		sum += (digit*weights);
		weights /= 10;
	}

	return sum;
}

/*
get HDCP key count from file
*/
int HDCPKeySeperateTool::getHDCPKeyCountNew() {
	int m;//current byte that getted from file
	int sum = 0;//count of key
	int weights = 1000000;//weight of current byte

	for (int i = 0;i < 4;i++) {
		m = fgetc(InFile);
		sum += m*weights;
		weights /= 100;
	}

	return sum;
}

int HDCPKeySeperateTool::getHDCPKeyCountThird() {
	int m;//current byte that getted from file
	int sum = 0;//count of key
	int weights = 256*256*256;//weight of current byte

	for (int i = 0;i < 4;i++) {
		m = fgetc(InFile);
		sum += m*weights;
		weights /= 256;
	}

	return sum;
}

/*
get a key from file then store in char* aKey.
return 0 when success
return -1 when fail
*/
int HDCPKeySeperateTool::getOneKey(char* aKey) {
	int ret = fread(aKey, sizeof(char), keySize, InFile);
	if (ret != keySize) {
		return -1;
	}
	return 0;
}

/*
put a key to file
return the size of key
*/
int HDCPKeySeperateTool::setOneKey(char* aKey) {
	int i = 0;
	for (;i < keySize;i++) {
		fputc(aKey[i], OutFile);
	}
	return i;
}

/*
do not use this function
change number of key int  to int array
prepare to write into file
*/
void HDCPKeySeperateTool::setHDCPKeyCountHelp(int sum,int* mm) {
	int m;
	int digit;

	for (int i = 3;i >=0;i--) {
		digit = sum % 10;
		m = digit;
		sum = (sum - digit)/10;

		digit = sum % 10;
		m += digit * 16;
		sum = (sum - digit) / 10;

		mm[i] = m;
	}
}

/*
change number of key int  to int array
prepare to write into file
*/
void HDCPKeySeperateTool::setHDCPKeyCountHelpNew(int sum,int* mm) {
	int weight = 1000000;
	for (int i = 0;i < 4;i++) {
		mm[i] = sum / weight;
		sum -= (weight*mm[i]);
		weight /= 100;
	}
}


void HDCPKeySeperateTool::setHDCPKeyCountHelpThird(int sum, int* mm) {
	int total = 0;
	for (int i = 3;i >= 0;i--) {
		mm[i] = sum%256;
		sum = (sum - mm[i])/256;
	}
}

/*
do not use this function
put 4 byte into file.represent the number of key in the file.
这个是将1000个key写为 00 00 10 00
*/
int HDCPKeySeperateTool::setHDCPKeyCount(int newKeyCount) {
	if (newKeyCount < 0)
		return -1;
	int mm[4];
	setHDCPKeyCountHelp(newKeyCount, mm);
	for (int i = 0;i < 4;i++) {
		fputc(mm[i], OutFile);
	}
	return 0;
}

/*
put 4 byte into file.represent the number of key in the file.
这个是将1000个key显示为 00 00 0a 00
*/
int HDCPKeySeperateTool::setHDCPKeyCountNew(int newKeyCount) {
	if (newKeyCount < 0)
		return -1;
	int mm[4];
	setHDCPKeyCountHelpNew(newKeyCount, mm);
	for (int i = 0;i < 4;i++) {
		fputc(mm[i], OutFile);
	}
	return 0;
}
/*
put 4 byte into file.represent the number of key in the file.
这个是将1000个key显示为 00 00 03 E8
*/
int HDCPKeySeperateTool::setHDCPKeyCountThird(int newKeyCount) {
	if (newKeyCount < 0)
		return -1;
	int mm[4];
	setHDCPKeyCountHelpThird(newKeyCount, mm);
	for (int i = 0;i < 4;i++) {
		fputc(mm[i], OutFile);
	}
	return 0;
}


/*
get current key location in inFile
*/
int HDCPKeySeperateTool::getLocationOfKey() {
	long loc = ftell(InFile);
	if (loc < 3)
		return 0;
	return (loc - 4) / keySize;
}

/*
set a new key location in inFile
*/
int HDCPKeySeperateTool::setLocationOfKey(int loc) {
	if (loc >= keyCount || loc < 0)
		return -1;
	fseek(InFile,loc*keySize+4, SEEK_SET);
	return getLocationOfKey();
}

int HDCPKeySeperateTool::seperateKeys(int newKeyCount,int newKeyLoc) {
	if (newKeyLoc < 0 || newKeyLoc >= keyCount || newKeyCount<=0 || (newKeyLoc+newKeyCount)>keyCount) {
		cout << "Target Key Range Error!" << endl;
		return -1;
	}

	if (setLocationOfKey(newKeyLoc) == -1) {
		cout << "Inner Error. setLocationOfKey" << endl;
		return -1;
	}

	cout << "Seperate From Key Index " << newKeyLoc << endl;
	cout << "Seperate Key Count " << newKeyCount << endl;

	//setHDCPKeyCountNew(newKeyCount);//不同的key计数格式需要选择不同的函数
	setHDCPKeyCountThird(newKeyCount);
	for (int i = 0;i<newKeyCount;i++) {
		if (getOneKey(tempKey) == -1) {
			cout << "Get Key From Source File Error!" << endl;
			return -1;
		}
		setOneKey(tempKey);
	}

	cout << "Seperate Success!" << endl;
	return 0;
}