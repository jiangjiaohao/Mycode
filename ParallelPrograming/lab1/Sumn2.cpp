// 代码简介：多链路式优化求和（递归），求给定的n个数的和

#include<iostream>
#include<chrono>
using namespace std;

// 此方法的缺点在于递归消耗比较大
void recursion(int n, int* q){
    if(n == 0 || n == 1) return;
    else{
        // odd 特殊处理
        if(n % 2) q[0] += q[n / 2];

        for(int i = 0; i < n / 2; i++){
            q[i] += q[n - i - 1];   
        }
        n = n / 2;
        recursion(n, q);
    }

}


int main(){

    cout << "请输入数据规模：" ;
    int n; cin >> n;
    int *a = new int[n];

    // 生成数据序列
    for(int i = 0; i <= n - 1; i++) a[i] = i;

    // 开始时间点
    auto start = std::chrono::high_resolution_clock::now();

    recursion(n, a);

    // 结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    
    // 计算时间差，微秒
    std::chrono::duration<double, std::micro> elapsed = end - start;
 
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;
    cout << "求和结果：" << a[0] << endl;

    delete [] a;

    return 0;
}
