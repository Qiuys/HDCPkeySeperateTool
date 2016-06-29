#include "KeyToolManager.h"
using namespace std;

int KeyToolManager::setInFile(char * in) {
	FILE * InFile = fopen(in, "rb");
	if (InFile == NULL) {
		cout << "Key file is not exist!" << endl;
		return -1;
	}
	fclose(InFile);
	inFile = in;
	return 0;
}

int KeyToolManager::setOutFile(char * out) {
	if (out == NULL) {
		return -1;
	}
	//TODO: do some check here!
	outFile = out;
	return 0;
}

/*根据keyType选择不同key的参数检查流程。当前只支持 keyType==1（HDCP key)*/
int KeyToolManager::setParameters(int keyType, int headLength, int keyLength, int keyCountFormat) {
	cout << "Key Type is " << keyType<< endl;
	if (headLength <= 0 || headLength <= 0) {
		cout << "headLength or headLength is unavailable! " << endl;
		return 1;
	}
	switch (keyType) {
	case 1:
		if (0 != newHDCPKeySeperateTool()) {
			return 2;
		}
		int cresult = HDCP_Tool->checkKeyFormat(inFile, headLength, keyLength, keyCountFormat);
		if (cresult != 0) {
			return 3;
		}
		break;
	default:
		cout << "Unavailable Key Type: " << keyType << endl;
		return 10;
	}
	return 0;
}

int KeyToolManager::newHDCPKeySeperateTool() {
	HDCP_Tool =new HDCPKeySeperateTool();
	return 0;
}


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