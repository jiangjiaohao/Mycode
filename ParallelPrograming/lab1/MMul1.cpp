// 逐列访问矩阵元素 向量*矩阵 [1 * m] * [m * n] = [1 * n]
#include<iostream>
#include<chrono>
using namespace std;

int main(){
    cout << "请输入矩阵的行列信息：" ;
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



   // 开始时间点
    auto start = std::chrono::high_resolution_clock::now();

    // 计算矩阵-向量乘法(列访问)
    int *res_p = new int[n];
    for(int i = 0; i < n ; i++){
        int temp = 0;
        for(int j = 0; j < m ; j++){
            temp += vector_p[j] * Martrix_p_p[j][i];
        }
        res_p[i] = temp;
    }
    
    // 结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    
    // 计算时间差，微秒
    std::chrono::duration<double, std::micro> elapsed = end - start;
    
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;

    // 输出结果
    cout << "向量-矩阵乘积：" ;
    for(int i = 0; i <= n - 1; i++) cout << res_p[i] << " ";
    cout << endl;

    // 清空缓存
    for(int i = 0; i <= m - 1; i++){
        delete [] Martrix_p_p[i];
    }
    delete [] Martrix_p_p;
    delete [] res_p;
    delete [] vector_p;

    return 0; 
}