// 代码简介：简单的串行算法，求给定的n个数的和

#include<iostream>
#include<chrono>
using namespace std;

int main(){

    cout << "请输入数据规模：" ;
    int n; cin >> n;
    int *a = new int[n];

    // 生成数据序列
    for(int i = 0; i <= n - 1; i++) a[i] = i;

    // 开始时间点
    auto start = std::chrono::high_resolution_clock::now();

    int sum = 0;
    for(int i = 0; i <= n - 1; i++){
        sum += a[i];
    }

    // 结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    
    // 计算时间差，微秒
    std::chrono::duration<double, std::micro> elapsed = end - start;
 
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;
    cout << "求和结果：" << sum << endl;

    delete [] a;

    return 0;
}


