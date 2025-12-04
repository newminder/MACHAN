#include "TCalcFuncSets.h"
#include "indicators.cpp"

// 函数声明
void EMA_Enhanced(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc);
void Custom_RSI(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc);
void BB_Width(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc);

// 函数表（可按需扩展）
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
    {1001, (pPluginFUNC)&EMA_Enhanced},   // 函数编号1001
    {1002, (pPluginFUNC)&Custom_RSI},     // 函数编号1002
    {1003, (pPluginFUNC)&BB_Width},       // 函数编号1003
    {0, NULL}, // 结束标记
};

// 导出函数（通达信调用此函数获取函数表）
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
    if (*pFun == NULL) {
        *pFun = g_CalcFuncSets;
        return TRUE;
    }
    return FALSE;
}