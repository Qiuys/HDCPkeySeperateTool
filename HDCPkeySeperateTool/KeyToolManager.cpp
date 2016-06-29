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

/*����keyTypeѡ��ͬkey�Ĳ���������̡���ǰֻ֧�� keyType==1��HDCP key)*/
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
}*/