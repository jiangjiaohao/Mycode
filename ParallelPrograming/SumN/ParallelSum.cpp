// 代码介绍：用并行的算法优化求n个数和的代码 
// 代码缺陷：n如果不能被comm_sz整除，那么会出现余数不计算的问题(MPI_Scatter)
// Error: mpiexec -n 4 parallelsum [4 通道]
// Please Input The Number: 5 []
// Plaese Input an Array: 1 2 3 4 5 
// sum is 10

#include<iostream>
#include<mpi.h>
using namespace std;

int n; 
int* array_p;
int sum;

int main(){

    int comm_sz; // 定义通讯子大小
    int my_rank; // 定义当前进程的进程序号
    int* loc_array_p; // 存放本地求和数组
    int loc_sum = 0; // 本地求和结果
    int loc_n = 0; // 本地数组大小

    MPI_Init(NULL, NULL); // 初始化MPI
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); // 获取通讯子大小
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // 获取进程序号

    if(my_rank == 0){
        // 输入只允许单个IO
        cout << "Please Input The Number: ";
        cin >> n;
        cout << "Plaese Input an Array: "; 

        array_p = new int[n];
        loc_n = n/comm_sz;
        loc_array_p = new int[loc_n]; // 注意能不能整除的问题！！！（暂定）
        
        for(int i = 0; i <= n - 1; i++) cin >> array_p[i];

        // 广播，将子模块大小传入其他进程
        MPI_Bcast(&loc_n, 1, MPI_INT, 0, MPI_COMM_WORLD);
         
        // 分发，采取块划分的方式
        MPI_Scatter(array_p, loc_n, MPI_INT, loc_array_p, loc_n, MPI_INT, 0, MPI_COMM_WORLD);
        
        // 本地求和
        for(int i = 0; i <= loc_n - 1; i++) loc_sum += loc_array_p[i];

        // 清空动态内存
        delete []loc_array_p;
        delete []array_p;
        
    }else{

        // 本地变量初始化
        // loc_n = n/comm_sz; // error1:对于其他进程，n = 0 所以没有求和结果

        // 所以采用广播的方式，直接获取loc_n
        MPI_Bcast(&loc_n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        loc_array_p = new int[loc_n]; 
        
        // 接收数据
        MPI_Scatter(array_p, loc_n, MPI_INT, loc_array_p, loc_n, MPI_INT, 0, MPI_COMM_WORLD);

        // 本地求和
        for(int i = 0; i <= loc_n - 1; i++) loc_sum += loc_array_p[i];

        // 清空动态内存
        delete []loc_array_p;

    }

    // 树形收集结果，采用集合通讯的方式
    MPI_Reduce(&loc_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
    
    // 输出结果
    if(my_rank == 0) cout << "sum is " << sum << endl;


    MPI_Finalize();


    return 0;
}

