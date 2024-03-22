// 整合测试 向量*矩阵 [1 * m] * [m * n] = [1 * n]
#include<iostream>
#include<chrono>
#include<cstring>
#include<fstream>
#include<ctime>
using namespace std;

void TestSimple(int m, int n, int *vector_p, int **Martrix_p_p);
void TestCacheOP(int m, int n, int *vector_p, int **Martrix_p_p);

int main(){

    freopen("MMul.in", "r", stdin);
    int m, n; // 行、列
    cin >> m >> n;  

    // 生成矩阵内容
    int **Martrix_p_p = new int*[m]; // 创建 m 行
    for(int i = 0; i <= m - 1; i++){
        Martrix_p_p[i] = new int[n]; // 创建 n 列
        for(int j = 0; j <= n - 1; j++) Martrix_p_p[i][j] = i + j / 2;
    }

    // 生成向量内容
    int *vector_p = new int[m];
    for(int i = 0; i <= m - 1; i++) vector_p[i] = i * 2;

    TestCacheOP(m, n, vector_p, Martrix_p_p);
    TestSimple(m, n, vector_p, Martrix_p_p);


    // 清空缓存
    for(int i = 0; i <= m - 1; i++){
        delete [] Martrix_p_p[i];
    }
    delete [] Martrix_p_p;
    delete [] vector_p;

    return 0; 
}


void TestCacheOP(int m, int n, int *vector_p, int **Martrix_p_p){

    int *res_p = new int[n];
    memset(res_p, 0, n);

    struct timespec start, end;
 
    // 开始时间点
    clock_gettime(CLOCK_MONOTONIC, &start);
 
    // 计算矩阵-向量乘法(行访问)
    for(int j = 0; j < m ; j++){
        for(int i = 0; i < n ; i++){
            res_p[i] += vector_p[j] * Martrix_p_p[j][i];
        }
    }
 
    // 结束时间点
    clock_gettime(CLOCK_MONOTONIC, &end);
 
    // 计算持续时间
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 ;
    
    ofstream out;
    out.open("Result.out", ios::app);
    out << elapsed << "  " << std::endl;
    // out << "Cathe优化: " << elapsed.count() << " microseconds" << std::endl;
    out.close();
    // std::cout << "Cathe优化: " << elapsed.count() << " microseconds" << std::endl;

    // 输出结果
    // cout << "向量-矩阵乘积：" ;
    // for(int i = 0; i <= n - 1; i++) cout << res_p[i] << " ";
    // cout << endl;

    delete [] res_p;
}

void TestSimple(int m, int n, int *vector_p, int **Martrix_p_p){

    int *res_p = new int[n];

    struct timespec start, end;
 
    // 开始时间点
    clock_gettime(CLOCK_MONOTONIC, &start);
 
    // 计算矩阵-向量乘法(列访问)
    
    for(int i = 0; i < n ; i++){
        int temp = 0;
        for(int j = 0; j < m ; j++){
            temp += vector_p[j] * Martrix_p_p[j][i];
        }
        res_p[i] = temp;
    }
    // 结束时间点
    clock_gettime(CLOCK_MONOTONIC, &end);
 
    // 计算持续时间
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 ;

    ofstream out;
    out.open("Result.out", ios::app);
    out  << elapsed << "  " << std::endl;
    // out << "朴素算法: " << elapsed.count() << " microseconds" << std::endl;
    out.close();
 
    // std::cout << "朴素算法: " << elapsed.count() << " microseconds" << std::endl;
    
    // 输出结果
    // cout << "向量-矩阵乘积：" ;
    // for(int i = 0; i <= n - 1; i++) cout << res_p[i] << " ";
    // cout << endl;

    delete [] res_p;

}