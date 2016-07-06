#include "KeyToolManager.h"
#include <afx.h>
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

/*ѡ��Ҫ�ָ����Կ����keyType ��ǰֻ֧�� keyType==1��HDCP key)*/
int KeyToolManager::setKeyType(int keyType) {
	cout << "Key Type is " << keyType<< endl;
	switch (keyType) {
	case 1:
		keyType = 1;
		break;
	default:
		cout << "Unavailable Key Type: " << keyType << endl;
		keyType = 0;
		return 10;
	}
	return 0;
}


int KeyToolManager::setHDCPKeyFormat(int headLength, int keyLength, int keyCountFormat,int aimkeyCountFormat) {
	HDCP_Tool =new HDCPKeySeperateTool();
	if (HDCP_Tool->checkKeyFormat(inFile, headLength, keyLength, keyCountFormat, aimkeyCountFormat) != 0) {
		return 1;
	}
	return 0;
}


int KeyToolManager::setHDCPKeySeperateParam(int keyBeginNum, int keyEachFile, int keyFileCount){
	if (keyBeginNum <= 0 || keyEachFile <= 0 || keyFileCount <= 0) {
		cout << "setHDCPKeySeperateParam is wrong!" << endl;
		return 1;
	}

	if (HDCP_Tool->checkCommand(keyBeginNum, keyEachFile*keyFileCount) != 0) {
		return 2;
	}
	KeyToolManager::keyBeginNum = keyBeginNum;
	KeyToolManager::keyEachFile = keyEachFile;
	KeyToolManager::keyFileCount = keyFileCount;
	cout << "setHDCPKeySeperateParam finish." << endl;
	return 0;
}

int KeyToolManager::startSeperate() {
	return 0;
}

int KeyToolManager::setOutFile(char * out,char * fprefix) {
	if (out == NULL || out == "" || fprefix == NULL){
		cout << "Wrong out put folder or file prefix!" << endl;
		return 1;
	}
	//TODO: Check space of the folder is enough or not.
	//TODO: Check the folder is writable or not.

	//Check wether the out put folder url is end with "/"
	int outLen = strlen(out);
	if (out[outLen - 1] != '/') {
		char * aimOut = (char *)malloc(1024);
		strcpy(aimOut, out);
		strcat(aimOut, "/");
		out = aimOut;
	}

	//Check wether the out put file name contains  \ / : * ? " < > |
	if (fprefix != "") {
		char * temp = NULL;
		char * donotuse[10] = { "/","\\",":","*","?","\"","<",">","|"," " };
		int donotuseLen = sizeof(donotuse) / sizeof(char*);
		for (int i = 0;i < donotuseLen;i++) {
			temp = strstr(fprefix, donotuse[i]);
			if (temp != NULL) {
				cout << "Error file prefix! Contains \'" << donotuse[i] << "\'" << endl;
				return 4;
			}
		}
	}

	//Check wether the out put folder is exist.
	struct _stat fileStat;
	if (!((_stat(out, &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR)))
	{
		cout << "Out put folder not exsit!" << endl;
		return 5;
	}

	//Check wether the out put folder is empty.
	char * dest = NULL;
	dest = (char *)malloc(1024);
	char * postfix = "*.*";
	strcpy(dest, out);
	strcat(dest, postfix);

	CString csout = dest;
	CFileFind cff;
	BOOL finding = cff.FindFile(csout);
	while (finding)
	{
		finding = cff.FindNextFile();
		if (cff.IsDots()) {
			continue;//skip . and ..
		}
		else {
			cout << "Out put folder is not empty!" << endl;
			cff.Close();
			return 6;
		}
	}
	cff.Close();
	outFolder = out;
	filePrefix = fprefix;
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