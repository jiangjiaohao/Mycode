// 代码简介：三种算法的整合程序，方便统计

#include<iostream>
#include<chrono>
#include<fstream>
#include<ctime>
#include<cmath>
using namespace std;

void TestSimple();
void recursion( int x);
void TestRecursion();
void TestOPtimisim();
void InitData();
void TestStep2();

int n; 
const int N = 2e8 + 10;
int a[N];

int main(){

    freopen("Sumn.in", "r", stdin);
    cin >> n;
    n = pow(2, n);
    

    InitData();  // 生成数据序列
    TestSimple(); // 测试朴素算法

    TestRecursion(); // 测试递归优化

    InitData();  // 重置数据序列
    TestOPtimisim(); // 测试非递归优化

    InitData();  // 重置数据序列
    TestStep2(); // 测试两步循环展开

    return 0;
}

void TestSimple(){

    struct timespec start, end;
 
    // 开始时间点
    clock_gettime(CLOCK_MONOTONIC, &start);

    int sum = 0;
    for(int i = 0; i <= n - 1; i++){
        sum += a[i];
    }

 
    // 结束时间点
    clock_gettime(CLOCK_MONOTONIC, &end);
 
    // 计算持续时间
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 ;
 
    ofstream out;
    out.open("Result.out", ios::app);
    out  << elapsed << "  " << std::endl;
    out.close();
 
    // std::cout << "朴素算法: " << elapsed.count() << " microseconds" << std::endl;
    // cout << "求和结果：" << sum << endl;

}

void TestRecursion(){

    struct timespec start, end;
 
    // 开始时间点
    clock_gettime(CLOCK_MONOTONIC, &start);
 
    recursion(n);

    // 结束时间点
    clock_gettime(CLOCK_MONOTONIC, &end);
 
    // 计算持续时间
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 ;
 
    
    ofstream out;
    out.open("Result.out", ios::app);
    out  << elapsed << "  " << std::endl;
    out.close();
    // std::cout << "递归优化: " << elapsed.count() << " microseconds" << std::endl;
    // cout << "求和结果：" << a[0] << endl;
}

// 设置求和个数为2^n所以不需要考虑 n为奇数
void recursion(int x){

    if(x == 0) return;
    else{

        for( int i = 0; i < x / 2; i++){
            a[i] += a[x - i - 1];   
        }
        x = x / 2;
        recursion(x);
    }

}

void TestOPtimisim(){

    struct timespec start, end;
 
    // 开始时间点
    clock_gettime(CLOCK_MONOTONIC, &start);
 

    for( int t = n; t > 1; t /= 2){
        for(int i = 0; i < t / 2; i++){
            a[i] = a[i * 2] + a[i * 2 + 1];
        }
    }

    // 结束时间点
    clock_gettime(CLOCK_MONOTONIC, &end);
 
    // 计算持续时间
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 ;
 
    ofstream out;
    out.open("Result.out", ios::app);
    out  << elapsed << "  " << std::endl;
    out.close();
 
    // std::cout << "非递归优化: " << elapsed.count() << " microseconds" << std::endl;
    // cout << "求和结果：" << a[0] << endl;
}


void TestStep2(){

    struct timespec start, end;

    // 开始时间点
    clock_gettime(CLOCK_MONOTONIC, &start);
 
    int sum1 = 0;
    int sum2 = 0;
    
    for( int i = 0; i < n; i += 2){
        sum1 += a[i];
        sum2 += a[i + 1];
    }
    
    int sum = sum1 + sum2;

    // 结束时间点
    clock_gettime(CLOCK_MONOTONIC, &end);
 
    // 计算持续时间
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 ;
 
    ofstream out;
    out.open("Result.out", ios::app);
    out  << elapsed << "  " << std::endl;
    out.close();
 
    // std::cout << "非递归优化: " << elapsed.count() << " microseconds" << std::endl;
    // cout << "求和结果：" << a[0] << endl;
}

void InitData(){
    for(int i = 0; i <= n - 1; i++) a[i] = i * 20 + 1;
}