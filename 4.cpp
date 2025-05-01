#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
using namespace std;
int k;
int hao[1000][1000];
int huai[1000][1000];
int main()
{
	// 随机数生成器
    std::random_device rd; // 随机数设备
    std::mt19937 gen(rd()); // 以随机设备作为种子的Mersenne Twister生成器

    // 分配一个在 [4, 1000] 范围内的均匀分布的随机数
    std::uniform_int_distribution<> distrib(4, 30); // 从4开始，因为要大于2

    // 生成随机偶数
    int randomEvenNumber = distrib(gen);

    // 确保是偶数
    if (randomEvenNumber % 2 != 0) {
        randomEvenNumber++;
    }
    //输入蓝图和故障图,使用数组
    k=randomEvenNumber;
    cout<<k<<endl;
    int n = k * k + k*k/4;
    cout<<n<<endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            hao[i][j]=0;
            huai[i][j]=0;
        }
    }
    for (int i = 0; i < n; i++) {
        if(i<k*k/4){
            for(int j=0;j<k;j++){
            	hao[i][j*k/2+k+i*2/k]=1;
            	hao[j*k/2+k+i*2/k][i]=1;
			}
		}
		else if(i>=n-k*k/2){
			int index3=int((i-k*k/2)/(k/2))-(k/2);
			for(int kvv=0;kvv<k/2;kvv++){
				hao[i][index3*k/2+kvv+k*k/4]=1;
				hao[index3*k/2+kvv+k*k/4][i]=1;
			}		
		}
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<hao[i][j]<<" ";
            huai[i][j]=hao[i][j];
        }
        cout<<endl;
    }
    for (int i = 0; i < 4; i++) {
    	int a,b;
        cin>>a>>b;
        if(huai[a][b]==0){
        	huai[a][b]=1;
		}
		else{
			huai[a][b]=0;
		}
		if(huai[b][a]==0){
        	huai[b][a]=1;
		}
		else{
			huai[b][a]=0;
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
    int aa=0,bb=0,cc=0; 
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
            	aa=1;
                std::cout << "No output for "  << " seconds, breaking all loops." << std::endl;
                return 0; // 退出内层循环
            	}
            } while (next_permutation(huaiban, huaiban + k2));
            if(aa==1){
            	bb=1;
            	break;
			}
        } while (next_permutation(huaiquan2, huaiquan2 + k6));
        if(bb==1){
        	break;
		}
    } while (next_permutation(huaiquan1, huaiquan1 + k4));
    return 0;
}
