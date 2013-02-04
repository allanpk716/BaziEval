#include "stdafx.h"
 
#include <windows.h>
 
const _TCHAR *TianGan = L"甲乙丙丁戊己庚辛壬癸";
const _TCHAR *DiZhi = L"子丑寅卯辰巳午未申酉戌亥";
 
bool CheckBazi(_TCHAR *bazi)
{
         int baziLen;
         int i,j;
 
         baziLen= wcslen(bazi);
         if(baziLen != 6 && baziLen != 8 ) return false;
 
         for(i = 0; i < baziLen;) {
                   _TCHAR ch = bazi[i];
                   for(j = 0; j < 10; j++)
                            if(ch == TianGan[j]) break;
                   if(j >= 10) return false;
                   i++;
 
                   ch= bazi[i];
                   for(j = 0; j < 12; j++)
                            if(ch == DiZhi[j]) break;
                   if(j >= 12) return false;
                   i++;
         }
        
         return true;
}
 
/*
根据出生日子的天干，通过下表来查算时辰干支：
时辰干支查算表
时间时辰                             五行纪日干支
                       甲己     乙庚     丙辛     丁壬     戊癸
 
23－01 子/水           甲子     丙子     戊子     庚子     壬子
01－03 丑/土           乙丑     丁丑     己丑     辛丑     癸丑
03－05 寅/木           丙寅     戊寅     庚寅     壬寅     甲寅
05－07 卯/木           丁卯     己卯     辛卯     癸卯     乙卯
07－09 辰/土           戊辰     庚辰     壬辰     甲辰     丙辰
09－11 巳/火           己巳     辛巳     癸巳     己巳     丁巳
11－13 午/火           庚午     壬午     甲午     丙午     戊午
13－15 未/土           辛未     癸未     乙未     丁未     己未
15－17 申/金           壬申     甲申     丙申     戊申     庚申
17－19 酉/金           癸酉     乙酉     丁酉     己酉     辛酉
19－21 戊/土           甲戌     丙戌     戊戌     庚戌     壬戌
21－23 亥/水           乙亥     丁亥     己亥     辛亥     癸亥
 
*/
const _TCHAR * cTimeGanZhi_Table[12][5] =
{
         {L"甲子",L"丙子", L"戊子", L"庚子", L"壬子"},
         {L"乙丑",L"丁丑", L"己丑", L"辛丑", L"癸丑"},
         {L"丙寅",L"戊寅", L"庚寅", L"壬寅", L"甲寅"},
         {L"丁卯",L"己卯", L"辛卯", L"癸卯", L"乙卯"},
         {L"戊辰",L"庚辰", L"壬辰", L"甲辰", L"丙辰"},
         {L"己巳",L"辛巳", L"癸巳", L"己巳", L"丁巳"},
         {L"庚午", L"壬午",L"甲午", L"丙午", L"戊午"},
         {L"辛未",L"癸未", L"乙未", L"丁未", L"己未"},
         {L"壬申",L"甲申", L"丙申", L"戊申", L"庚申"},
         {L"癸酉",L"乙酉", L"丁酉", L"己酉", L"辛酉"},
         {L"甲戌",L"丙戌", L"戊戌", L"庚戌", L"壬戌"},
         {L"乙亥",L"丁亥", L"己亥", L"辛亥", L"癸亥"}
};
 
static _TCHAR sBuf[128];        // 用作八字结果缓冲区
 
// 根据出生年月日的干支计算时辰干支
// 输入参数：bazi，年月日的干支，即八字中的前六个字
// 输入参数：hour，出生时间的小时数，-1~22
// 输出结果：八字字符串，Unicode编码
_TCHAR * ComputeTimeGan(_TCHAR *bazi, int hour)
{
         _TCHAR dayGan = bazi[4];
 
         int indexX, indexY;
        
         int i;
         for(i = 0; i < 10; i++)
                   if(dayGan == TianGan[i]) break;
         if(i >= 10) return 0;
         indexX= i;
         if(indexX >=5) indexX -= 5;
         indexY= (hour +1)/2;
 
         wcscpy(sBuf,bazi);
         wcscat(sBuf,cTimeGanZhi_Table[indexY][indexX]);
 
         return sBuf;
}
 
/*
十二月份天干强度表
生月\四柱天干        甲              乙              丙              丁              戊              己              庚              辛              壬              癸
子月                            1.2             1.2             1.0             1.0             1.0             1.0             1.0             1.0             1.2             1.2
丑月                            1.06 1.06 1.0             1.0             1.1             1.1             1.14 1.14 1.1             1.1
寅月                            1.14 1.14 1.2             1.2             1.06 1.06 1.0             1.0             1.0             1.0
卯月                            1.2             1.2             1.2             1.2             1.0             1.0             1.0             1.0             1.0             1.0
辰月                            1.1             1.1             1.06 1.06 1.1             1.1             1.1             1.1             1.04 1.04
巳月                            1.0             1.0             1.14 1.14 1.14 1.14 1.06 1.06 1.06 1.06
午月                            1.0             1.0             1.2             1.2             1.2             1.2             1.0             1.0             1.0             1.0
未月                            1.04 1.04 1.1             1.1             1.16 1.16 1.1             1.1             1.0             1.0
申月                            1.06 1.06 1.0             1.0             1.0             1.0             1.14 1.14 1.2             1.2
酉月                            1.0             1.0             1.0             1.0             1.0             1.0             1.2             1.2             1.2             1.2
戌月                            1.0             1.0             1.04 1.04 1.14 1.14 1.16 1.16 1.06 1.06
亥月                            1.2             1.2             1.0             1.0             1.0             1.0             1.0             1.0             1.14 1.14
*/
 
double TianGan_Strength [12][10] =
{
         {1.2, 1.2,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.2,  1.2},
         {1.06,        1.06,         1.0,  1.0,  1.1,  1.1,  1.14,         1.14,         1.1,  1.1},
         {1.14,        1.14,         1.2,  1.2,  1.06,         1.06,         1.0,  1.0,  1.0,  1.0},
         {1.2, 1.2,  1.2,  1.2,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0},
         {1.1, 1.1,  1.06,         1.06,         1.1,  1.1,  1.1,  1.1,  1.04,         1.04},
         {1.0, 1.0,  1.14,         1.14,         1.14,         1.14,         1.06,         1.06,         1.06,         1.06},
         {1.0, 1.0,  1.2,  1.2,  1.2,  1.2,  1.0,  1.0,  1.0,  1.0},
         {1.04,        1.04,         1.1,  1.1,  1.16,         1.16,         1.1,  1.1,  1.0,  1.0},
         {1.06,        1.06,         1.0,  1.0,  1.0,  1.0,  1.14,         1.14,         1.2,  1.2},
         {1.0, 1.0,  1.0,  1.0,  1.0,  1.0,  1.2,  1.2,  1.2,  1.2},
         {1.0, 1.0,  1.04,         1.04,         1.14,         1.14,         1.16,         1.16,         1.06,         1.06},
         {1.2, 1.2,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.14,         1.14}
};
 
/*
十二月份地支强度表
 
                        生月       子月         丑月         寅月         卯月         辰月         巳月         午月         未月         申月         酉月         戌月         亥月        
地支         支藏
子              癸                       1.2             1.1             1.0             1.0             1.04 1.06 1.0             1.0             1.2             1.2             1.06 1.14
丑              癸                       0.36 0.33 0.3             0.3             0.312        0.318        0.3             0.3             0.36 0.36 0.318        0.342
丑              辛                       0.2             0.228        0.2             0.2             0.23 0.212        0.2             0.22 0.228        0.248        0.232        0.2           
丑              己                       0.5             0.55 0.53 0.5             0.55 0.57 0.6             0.58 0.5             0.5             0.57 0.5            
寅              丙                       0.3             0.3             0.36 0.36 0.318        0.342        0.36 0.33 0.3             0.3             0.342        0.318       
寅              甲                       0.84 0.742        0.798        0.84 0.77 0.7             0.7             0.728        0.742        0.7             0.7             0.84
卯              乙                       1.2             1.06 1.14 1.2             1.1             1.0             1.0             1.04 1.06 1.0             1.0             1.2            
辰              乙                       0.36 0.318        0.342        0.36 0.33 0.3             0.3             0.312        0.318        0.3             0.3             0.36
辰              癸                       0.24 0.22 0.2             0.2             0.208        0.2             0.2             0.2             0.24 0.24 0.212        0.228       
辰              戊                       0.5             0.55 0.53 0.5             0.55 0.6             0.6             0.58 0.5             0.5             0.57 0.5            
巳              庚                       0.3             0.342        0.3             0.3             0.33 0.3             0.3             0.33 0.342        0.36 0.348        0.3            
巳              丙                       0.7             0.7             0.84 0.84 0.742        0.84 0.84 0.798        0.7             0.7             0.728        0.742       
午              丁                       1.0             1.0             1.2             1.2             1.06 1.14 1.2             1.1             1.0             1.0             1.04 1.06
未              丁                       0.3             0.3             0.36 0.36 0.318        0.342        0.36 0.33 0.3             0.3             0.312        0.318       
未              乙                       0.24 0.212        0.228        0.24 0.22 0.2             0.2             0.208        0.212        0.2             0.2             0.24
未              己                       0.5             0.55 0.53 0.5             0.55 0.57 0.6             0.58 0.5             0.5             0.57 0.5            
申              壬                       0.36 0.33 0.3             0.3             0.312        0.318        0.3             0.3             0.36 0.36 0.318        0.342       
申              庚                       0.7             0.798        0.7             0.7             0.77 0.742        0.7             0.77 0.798        0.84 0.812        0.7            
酉              辛                       1.0             1.14 1.0             1.0             1.1             1.06 1.0             1.1             1.14 1.2             1.16 1.0            
戌              辛                       0.3             0.342        0.3             0.3             0.33 0.318        0.3             0.33 0.342        0.36 0.348        0.3            
戌              丁                       0.2             0.2             0.24 0.24 0.212        0.228        0.24 0.22 0.2             0.2             0.208        0.212       
戌              戊                       0.5             0.55 0.53 0.5             0.55 0.57 0.6             0.58 0.5             0.5             0.57 0.5            
亥              甲                       0.36 0.318        0.342        0.36 0.33 0.3             0.3             0.312        0.318        0.3             0.3             0.36
亥              壬                        0.84 0.77 0.7             0.7             0.728        0.742        0.7             0.7             0.84 0.84 0.724        0.798       
*/
struct ZISTRENGTH {
         _TCHAR diZhi;
         _TCHAR zhiCang;
         double strength[12];
};
 
ZISTRENGTH DiZhi_Strength [] =
{
         {L'子', L'癸', {1.2,1.1, 1.0, 1.0,        1.04, 1.06, 1.0,1.0, 1.2, 1.2, 1.06, 1.14}},     
         {L'丑', L'癸', {0.36,0.33, 0.3, 0.3, 0.312, 0.318, 0.3, 0.3, 0.36, 0.36, 0.318, 0.342}},
         {L'丑', L'辛', {0.2,0.228, 0.2, 0.2, 0.23, 0.212, 0.2,         0.22,0.228, 0.248, 0.232, 0.2}},              
         {L'丑', L'己', {0.5,0.55, 0.53, 0.5, 0.55, 0.57, 0.6, 0.58, 0.5, 0.5, 0.57, 0.5}},                 
         {L'寅', L'丙', {0.3,0.3, 0.36, 0.36, 0.318, 0.342, 0.36, 0.33, 0.3, 0.3, 0.342, 0.318}},   
         {L'寅', L'甲', {0.84,0.742, 0.798, 0.84, 0.77, 0.7, 0.7, 0.728, 0.742, 0.7, 0.7, 0.84}},   
         {L'卯', L'乙', {1.2,1.06, 1.14, 1.2, 1.1, 1.0, 1.0, 1.04, 1.06, 1.0, 1.0, 1.2}},             
         {L'辰', L'乙', {0.36,0.318, 0.342, 0.36, 0.33, 0.3, 0.3, 0.312, 0.318, 0.3, 0.3, 0.36}},   
         {L'辰', L'癸', {0.24,0.22,  0.2, 0.2, 0.208, 0.2, 0.2, 0.2,0.24, 0.24, 0.212, 0.228}},       
         {L'辰', L'戊', {0.5,0.55, 0.53, 0.5, 0.55, 0.6, 0.6, 0.58, 0.5, 0.5, 0.57, 0.5}},          
         {L'巳', L'庚', {0.3,0.342, 0.3, 0.3, 0.33, 0.3, 0.3, 0.33, 0.342, 0.36, 0.348, 0.3}},          
         {L'巳', L'丙', {0.7,0.7, 0.84, 0.84, 0.742, 0.84, 0.84, 0.798, 0.7, 0.7, 0.728, 0.742}},   
         {L'午', L'丁', {1.0,1.0, 1.2, 1.2, 1.06, 1.14, 1.2, 1.1, 1.0, 1.0, 1.04, 1.06}},   
         {L'未', L'丁', {0.3,0.3, 0.36, 0.36, 0.318, 0.342, 0.36, 0.33, 0.3, 0.3, 0.312, 0.318}},   
         {L'未', L'乙', {0.24,0.212, 0.228, 0.24, 0.22, 0.2, 0.2, 0.208, 0.212, 0.2, 0.2, 0.24}},   
         {L'未', L'己', {0.5,0.55, 0.53, 0.5, 0.55, 0.57, 0.6, 0.58, 0.5, 0.5, 0.57, 0.5}},                 
         {L'申', L'壬', {0.36,0.33, 0.3, 0.3, 0.312, 0.318, 0.3, 0.3, 0.36, 0.36, 0.318, 0.342}},   
         {L'申', L'庚', {0.7,0.798, 0.7, 0.7, 0.77, 0.742, 0.7, 0.77, 0.798, 0.84, 0.812, 0.7}},               
         {L'酉', L'辛', {1.0,1.14, 1.0, 1.0, 1.1, 1.06, 1.0, 1.1, 1.14, 1.2, 1.16, 1.0}},             
         {L'戌', L'辛', {0.3,0.342, 0.3, 0.3, 0.33, 0.318, 0.3, 0.33, 0.342, 0.36, 0.348, 0.3}},               
         {L'戌', L'丁', {0.2,0.2, 0.24, 0.24, 0.212, 0.228, 0.24, 0.22, 0.2, 0.2, 0.208, 0.212}},   
         {L'戌', L'戊', {0.5,0.55, 0.53, 0.5, 0.55, 0.57, 0.6, 0.58, 0.5, 0.5, 0.57, 0.5}},                 
         {L'亥', L'甲', {0.36,0.318, 0.342, 0.36, 0.33, 0.3, 0.3, 0.312, 0.318, 0.3, 0.3, 0.36}},   
         {L'亥', L'壬', {0.84,0.77, 0.7, 0.7, 0.728, 0.742, 0.7, 0.7, 0.84, 0.84, 0.724, 0.798}}     
};
 
/*
         金 --- 0
         木 --- 1
         水 --- 2
         火 --- 3
         土 --- 4
*/
 
_TCHAR WuXingTable[5] = {L'金', L'木', L'水', L'火', L'土' };
 
/*
         天干地支的五行属性表
         天干： 甲-木、乙-木、丙-火、丁－火、戊－土、己－土、庚－金、辛－金、壬－水、癸－水
         地支：子-水、丑-土、寅-木、卯－木、辰－土、巳－火、午－火、未－土、申－金、酉－金、戌－土、亥－水
*/
 
int TianGan_WuXingProp[10] = {1, 1, 3, 3, 4,4, 0, 0, 2, 2};
int DiZhi_WuXingProp[12] = {2, 4, 1, 1, 4,3, 3, 4, 0, 0, 4, 2};
int GenerationSourceTable[5] = {4, 2, 0, 1,3};
 
int ComputeGanIndex(_TCHAR gan)
{
         int i;
         for(i=0; i < 10; i++)
                   if(TianGan[i] == gan) break;
         if(i >= 10) return -1;
         return i;
}
 
int ComputeZhiIndex(_TCHAR zhi)
{
         int i;
         for(i=0; i < 12; i++)
                   if(DiZhi[i] == zhi) break;
         if(i >= 12) return -1;
         return i;
}
 
static _TCHAR sResultBuf[1024];   // 用作八字测算结果返回的字符缓冲区
 
// 根据八字计算五行平衡
// 输入参数：bazi，年月日时的干支，即俗称的八字
// 输出结果：分析结果字符串，Unicode编码
_TCHAR * EvalBazi(_TCHAR *bazi)
{
         double strengthResult[5];
         int monthIndex = ComputeZhiIndex(bazi[3]);
         if(monthIndex == -1) goto ERROR_CASE;
 
         wcscpy(sResultBuf,bazi);
         wcscat(sResultBuf,L"\n\n");
         for(int wuXing = 0; wuXing < 5; wuXing++) {
                   double value1 = 0.0, value2 = 0.0;
                   int i;
                   //扫描4个天干
                   for(i  = 0; i <8; i+=2) {
                            TCHAR gan = bazi[i];
                            int index = ComputeGanIndex(gan);
                            if(index == -1) goto ERROR_CASE;
 
                            if(TianGan_WuXingProp[index] == wuXing)
                                     value1+= TianGan_Strength[monthIndex][index];
                   }
 
                   //扫描支藏
                   for(i  = 1; i <8; i+=2) {
                            TCHAR zhi = bazi[i];
                            for(int j = 0; j < sizeof (DiZhi_Strength)/sizeof (DiZhi_Strength[0]); j++) {
                                     if(DiZhi_Strength[j].diZhi == zhi) {
                                               int zhiCangIndex = ComputeGanIndex(DiZhi_Strength[j].zhiCang);
                                               if(zhiCangIndex == -1) goto ERROR_CASE;
                                               if(TianGan_WuXingProp[zhiCangIndex] == wuXing) {
                                                        value2+= DiZhi_Strength[j].strength[monthIndex];
                                                        break;
                                               }
                                     }
                            }
                   }
 
                   strengthResult[wuXing]= value1 + value2;
 
                   //输出一行计算结果
                   {
                            _TCHAR preStr[128];
                            char tmpBuf[128];
                            _TCHAR tmpWBuf[256];
                            sprintf(tmpBuf,":%.3f + %.3f = %.3f\n", (float)value1, (float)value2,(float)(value1+value2));
                            MultiByteToWideChar(CP_ACP, 0, tmpBuf, strlen(tmpBuf)+1,
                                     tmpWBuf,sizeof(tmpWBuf)/sizeof(_TCHAR) );
                            wcscpy(preStr,L"金:\t");
                            preStr[0]= WuXingTable[wuXing];
                            wcscat(sResultBuf,preStr);
                            wcscat(sResultBuf,tmpWBuf);
                   }
         }
        
         //根据日干求命里属性
         int fateProp, srcProp;
 
         {
                   _TCHAR tmpWBuf[256];
                   fateProp= TianGan_WuXingProp[ComputeGanIndex(bazi[4])];
                   if(fateProp == -1) goto ERROR_CASE;
                   wcscpy(tmpWBuf,L"\n命属金\n\n");
                   tmpWBuf[3]= WuXingTable[fateProp];
                   wcscat(sResultBuf,tmpWBuf);
 
         }
 
         //求同类和异类的强度值
         srcProp= GenerationSourceTable[fateProp];
         {
                   _TCHAR preStr[128];
                   char tmpBuf[128];
                   _TCHAR tmpWBuf[256];
 
                   double tongLei = strengthResult[fateProp] + strengthResult[srcProp];
                   double yiLei = 0.0;
                   for(int i = 0; i < 5; i ++) yiLei += strengthResult[i];
                   yiLei-= tongLei;
                  
                   sprintf(tmpBuf,"%.3f+ %.3f = %.3f\n", (float)strengthResult[fateProp],(float)strengthResult[srcProp],
                            (float)tongLei);
                   MultiByteToWideChar(CP_ACP, 0, tmpBuf, strlen(tmpBuf)+1,
                            tmpWBuf,sizeof(tmpWBuf)/sizeof(_TCHAR) );
                   wcscpy(preStr,L"同类：金+金，");
                   preStr[3]= WuXingTable[fateProp];
                   preStr[5]= WuXingTable[srcProp];
                   wcscat(sResultBuf,preStr);
                   wcscat(sResultBuf,tmpWBuf);
 
                   sprintf(tmpBuf,"%.3f\n", (float)yiLei);
                   MultiByteToWideChar(CP_ACP, 0, tmpBuf, strlen(tmpBuf)+1,
                            tmpWBuf,sizeof(tmpWBuf)/sizeof(_TCHAR) );
                   wcscat(sResultBuf,L"异类：总和为 ");
                   wcscat(sResultBuf,tmpWBuf);
         }
 
         return sResultBuf;
 
ERROR_CASE:
        
         return 0;
}