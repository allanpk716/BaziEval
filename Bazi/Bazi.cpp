// Bazi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include<iostream>
using namespace std;

void Usage()
{
	cout << "Usage:\tBazi.exe -q <生辰八字中之前六字> -t hh" << endl;
	cout <<"\tBazi.exe -e <生辰八字>" << endl;
	return;
}

bool CheckBazi(_TCHAR *bazi);
_TCHAR *ComputeTimeGan(_TCHAR *bazi, int hour);
_TCHAR *EvalBazi(_TCHAR *bazi);

int _tmain(int argc, _TCHAR* argv[])
{
	_TCHAR *subCmd, *paraStr;
	if (argc != 5 && argc !=3) {
		Usage();
		return 0;
	}

	subCmd = argv[1];
	paraStr = argv[2];
	if (argc ==5) {
		// Parsing the part of"-q <生辰八字中之前六字>"
		if (!(wcslen(subCmd)==1&& subCmd[0] == 'q' || wcslen(subCmd)==2 && subCmd[0]=='-'&& subCmd[1]=='q')) {
			Usage();
			return 0;
		}

		if (wcslen(paraStr)!=6 ||!CheckBazi(paraStr)) {
			cout <<"-q后面须跟上生辰日的干支，可以查询万年历，比如在线版本 http://www.nongli.net/" << endl;
			Usage();
			return 0;
		}

		// Parsing the part of"-t hh:mm"
		subCmd = argv[3];
		paraStr = argv[4];

		if (!(wcslen(subCmd)==1&& subCmd[0] == 't' || wcslen(subCmd)==2 && subCmd[0]=='-'&& subCmd[1]=='t')) {
			Usage();
			return 0;
		}

		int hour = -1;
		swscanf(paraStr,L"%d", &hour);
		if (hour <0 || hour>23) {
			cout <<"Error: 时辰参数不正确，应为0~23之间的一个整点数。" << endl;
			Usage();
			return 0;
		}

		_TCHAR * result =ComputeTimeGan(argv[2], hour);
		if (result == 0) {
			cout << "查询不成功！"<< endl;
		} else {
			char tmpBuf[128];
			WideCharToMultiByte( CP_ACP, 0, result, -1,tmpBuf, 127, NULL, NULL );

			cout << "查询八字的结果是："<< tmpBuf << endl;
			cout << "接下来您可以用-e命令测算此八字的五行平衡信息。" << endl;
		}
		return 0;
	}

	if (argc ==3) {
		// Parsingthe part of "-q <生辰八字中之前六字>"
		if (!(wcslen(subCmd)==1&& subCmd[0] == 'e' || wcslen(subCmd)==2 && subCmd[0]=='-'&& subCmd[1]=='e')) {
			Usage();
			return 0;
		}

		if (wcslen(paraStr)!=8 ||!CheckBazi(paraStr)) {
			cout <<"-e后面须跟上生辰八字" << endl;
			Usage();
			return 0;
		}

		_TCHAR *result =EvalBazi(paraStr);

		if (result == 0) {
			cout << "测算不成功，另请高明！"<< endl;
		} else {
			char tmpBuf[1024];
			WideCharToMultiByte( CP_ACP, 0, result, -1,tmpBuf, 1024, NULL, NULL );

			cout <<"\n此八字的五行平衡分析结果如下：\n\n" << tmpBuf << endl;
		}
		return 0;
	}

	Usage();

	return 0;
}

