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
HDCPKeySeperateTool::HDCPKeySeperateTool() {
	//empty
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


//1.第一步，检查输入的参数与key文件是否匹配。
int HDCPKeySeperateTool::checkKeyFormat(char * inFile, int headLength, int keyLength, int keyCountFormat) {
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

/*将1000个key显示为 00 00 03 E8*/
int HDCPKeySeperateTool::readKeyCountFormat1(FILE * InFile, int headLength) {
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


//2.第二步，检查需要提取的key数量是否会超出key文件的范围
/*
param keyBeginNum : The number of first key to be seperated from file.
param keyCount : The count of keys to be seperated from file.
return : 0:Can be seperated successfully 1:param is unavailable
2:The keys in file are not enough
*/
int HDCPKeySeperateTool::checkCommand(int keyBeginNum, int keyCount) {
	if (keyBeginNum <= 0 || keyCount <= 0) {
		cout << "keyBeginNum or keyCount is unavailable!" << endl;
		return 1;
	}
	int keyLastNum = keyBeginNum + keyCount - 1;
	if (keyLastNum > keyCount) {
		cout << "keys are not enough for you!" << endl;
		return 2;
	}
	return 0;
}