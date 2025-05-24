#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
int k;
int hao[1000][1000];
int huai[1000][1000];
int main()
{
    //输入蓝图和故障图,使用数组
    cin >> k;
    int n = k * k + k*k/4;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> hao[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> huai[i][j];
        }
    }
    //计算一下每个点有多少个邻居

    //分类，利用fattree的特点进行分类,分成三类,默认k>2
    int haoban[100];
    int huaiban[100];
    int haoquan1[100];
    int haoquan2[100];
    int huaiquan1[100];
    int huaiquan2[100];
    int k1 = 0, k2 = 0, k3 = 0, k4 = 0, k5 = 0, k6 = 0;
    int haozan[100], huaizan[100], kz1 = 0, kz2 = 0;
    for (int i = 0; i < n; i++) {
        int count1 = 0, count2 = 0;
        for (int j = 0; j < n; j++) {
            if (hao[i][j] == 1) {
                count1++;
            }
            if (huai[i][j] == 1) {
                count2++;
            }
        }
        if (count1 == k / 2) {
            haoban[k1] = i;
            k1++;
        }
        else {
            haozan[kz1] = i;
            kz1++;
        }
        if (count2 == k / 2) {
            huaiban[k2] = i;
            k2++;
        }
        else {
            huaizan[kz2] = i;
            kz2++;
        }
    }
    for (int i = 0; i < kz1; i++) {
        int index1 = 0, index2 = 0;
        for (int j = 0; j < k1; j++) {
            if (hao[haozan[i]][haoban[j]] == 1) {
                index1 = 1;
                break;
            }
        }
        if (index1 == 0) {
            haoquan1[k3] = haozan[i];
            k3++;
        }
        else {
            haoquan2[k5] = haozan[i];
            k5++;
        }
        for (int j = 0; j < k2; j++) {
            if (huai[huaizan[i]][huaiban[j]] == 1) {
                index2 = 1;
                break;
            }
        }
        if (index2 == 0) {
            huaiquan1[k4] = huaizan[i];
            k4++;
        }
        else {
            huaiquan2[k6] = huaizan[i];
            k6++;
        }
    }
    //分析错误的地方
    //可以先分析每个类都数量相同的情况。
    auto lastOutputTime= std::chrono::steady_clock::now();
    int zuixiao = 999;
    do {
        int duiyin[100];
        for (int i = 0; i < k4; i++) {
            duiyin[haoquan1[i]] = huaiquan1[i];
        }
       
        do {
            for (int i = 0; i < k6; i++) {
                duiyin[haoquan2[i]] = huaiquan2[i];
            }
            do {

                for (int i = 0; i < k2; i++) {
                    duiyin[haoban[i]] = huaiban[i];
                }
                int gu[100][100];
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        gu[i][j] = huai[duiyin[i]][duiyin[j]];
                    }
                }
                int guzhang[100][2];
                int count = 0;
                int k = 0;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (gu[i][j] != hao[i][j]) {
                            count++;
                            if(count>zuixiao){
                            	break;
							}
                            guzhang[k][0] = i;
                            guzhang[k][1] = j;
                            k++;
                        }
                    }
                }
                if (count < zuixiao) {
                	lastOutputTime = std::chrono::steady_clock::now();
                    zuixiao = count;
                    for (int i = 0; i < n; i++) {
                        cout << duiyin[i] << " ";
                    }
                    cout << endl;
                    for (int i = 0; i < k; i++) {
                        cout << duiyin[guzhang[i][0]] << " " << duiyin[guzhang[i][1]] << endl;
                    }
                }
                auto currentTime = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastOutputTime).count() >1) {
                std::cout << "No output for "  << " seconds, breaking all loops." << std::endl;
                return 0; // 退出内层循环
            	}
            } while (next_permutation(huaiban, huaiban + k2));
        } while (next_permutation(huaiquan2, huaiquan2 + k6));
    } while (next_permutation(huaiquan1, huaiquan1 + k4));
    return 0;
}
