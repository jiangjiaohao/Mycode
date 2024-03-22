// 代码介绍：矩阵和向量的乘积（串行）


#include<iostream>
using namespace std;



int main(){
    int m, n; // 行、列
    cin >> m >> n;

    // 输入矩阵
    int **Martrix_p_p = new int*[m]; // 创建 m 行
    for(int i = 0; i <= m - 1; i++){
        Martrix_p_p[i] = new int[n]; // 创建 n 列
        for(int j = 0; j <= n - 1; j++) cin >> Martrix_p_p[i][j];
    }

    // 输入向量 
    int *vector_p = new int[n];
    for(int i = 0; i <= n - 1; i++) cin >> vector_p[i];

    // 计算矩阵-向量乘法
    int *res_p = new int[m];
    for(int i = 0; i <= m - 1; i++){
        int tmp = 0;
        for(int j = 0; j <= n - 1; j++){
            tmp += Martrix_p_p[i][j]*vector_p[j];
        }
        res_p[i] = tmp;
    }

    for(int i = 0; i <= m - 1; i++) cout << res_p[i] << " ";

    // 清空缓存
    for(int i = 0; i <= m - 1; i++){
        delete [] Martrix_p_p[i];
    }
    delete [] Martrix_p_p;
    delete [] res_p;

    return 0; 
}