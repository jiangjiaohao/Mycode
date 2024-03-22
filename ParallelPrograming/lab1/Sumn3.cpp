// 代码简介：多链路式优化求和（非递归），求给定的n个数的和


#include <iostream>
#include <chrono>
using namespace std;


int main(){

    cout << "请输入数据规模：" ;
    int n; cin >> n;
    int *a = new int[n];

    // 生成数据序列
    for(int i = 0; i <= n - 1; i++) a[i] = i;

    // 开始时间点
    auto start = std::chrono::high_resolution_clock::now();

    for(int t = n; t >= 2; t /= 2){
        if (t % 2) a[0] += a[t / 2];
        for(int i = 0; i < t / 2; i++){
            a[i] += a[t - i - 1];
        }
    }

    // 结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    
    // 计算时间差，微秒
    std::chrono::duration<double, std::micro> elapsed = end - start;
 
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;
    cout << "求和结果：" << a[0] << endl;

    delete [] a;

    return 0;
}
