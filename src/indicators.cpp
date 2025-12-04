#include <cmath>
#include <algorithm>

// 示例1: 增强型移动平均
void EMA_Enhanced(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc)
{
    if (DataLen <= 0 || !pfINa || !pfOUT) return;
    
    // 参数解析：pfINb[0] = 周期（默认为12）
    int period = 12;
    if (pfINb && DataLen > 0) {
        period = static_cast<int>(pfINb[0]);
        if (period < 2) period = 2;
        if (period > DataLen) period = DataLen;
    }
    
    float alpha = 2.0f / (period + 1.0f);
    pfOUT[0] = pfINa[0];
    
    for (int i = 1; i < DataLen; i++) {
        pfOUT[i] = alpha * pfINa[i] + (1 - alpha) * pfOUT[i-1];
    }
}

// 示例2: 自定义RSI
void Custom_RSI(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc)
{
    if (DataLen <= 1 || !pfINa || !pfOUT) return;
    
    int period = 14;
    if (pfINb && DataLen > 0) {
        period = static_cast<int>(pfINb[0]);
        if (period < 2) period = 2;
    }
    
    // 计算价格变化
    for (int i = 0; i < DataLen; i++) {
        pfOUT[i] = 50.0f; // 默认值
        
        if (i >= period) {
            float gain = 0.0f;
            float loss = 0.0f;
            
            for (int j = 0; j < period; j++) {
                float change = pfINa[i-j] - pfINa[i-j-1];
                if (change > 0) {
                    gain += change;
                } else {
                    loss -= change;
                }
            }
            
            if (loss > 0.00001f) {
                float rs = gain / loss;
                pfOUT[i] = 100.0f - 100.0f / (1.0f + rs);
            } else if (gain > 0.00001f) {
                pfOUT[i] = 100.0f;
            } else {
                pfOUT[i] = 50.0f;
            }
        }
    }
}

// 示例3: 布林带宽度指标
void BB_Width(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc)
{
    if (DataLen <= 0 || !pfINa || !pfOUT) return;
    
    int period = 20;
    float stdDev = 2.0f;
    
    if (pfINb && DataLen > 0) period = static_cast<int>(pfINb[0]);
    if (pfINc && DataLen > 0) stdDev = pfINc[0];
    
    if (period < 2) period = 2;
    
    for (int i = 0; i < DataLen; i++) {
        if (i >= period - 1) {
            // 计算均值
            float sum = 0.0f;
            for (int j = 0; j < period; j++) {
                sum += pfINa[i - j];
            }
            float mean = sum / period;
            
            // 计算标准差
            float variance = 0.0f;
            for (int j = 0; j < period; j++) {
                float diff = pfINa[i - j] - mean;
                variance += diff * diff;
            }
            float stdev = sqrtf(variance / period);
            
            // 布林带宽度 = (上轨 - 下轨) / 中轨
            float upper = mean + stdDev * stdev;
            float lower = mean - stdDev * stdev;
            pfOUT[i] = (upper - lower) / mean * 100.0f;
        } else {
            pfOUT[i] = 0.0f;
        }
    }
}