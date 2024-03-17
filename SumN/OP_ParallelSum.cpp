// 代码介绍：optimized 优化的并行求n数和算法(MPI_Scatterv)
#include<iostream>
#include<mpi.h>
using namespace std;

int n; 
int* array_p;
int sum;
int* displs; // 存放分发规则
int* sendcounts; 

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

        // 制定分发规则
        displs = new int[comm_sz];
        sendcounts = new int[comm_sz];
        displs[0] = 0;
        sendcounts[0] = loc_n;
        for(int i = 1; i <= comm_sz - 1; i++) {
            displs[i] = displs[i - 1] + loc_n;
            if(i != comm_sz - 1) sendcounts[i] = loc_n;
            else {
                sendcounts[i] = loc_n + n % comm_sz; // 错误点：n % loc_n
            }
        } // 除最后一项外，其他区间长度相同

        // 分发之前，仍然需要把数组大小给广播出去，否则无法在分发前建立动态数组
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // 分发，采取块划分的方式
        MPI_Scatterv(array_p, sendcounts, displs, MPI_INT, loc_array_p, loc_n, MPI_INT, 0, MPI_COMM_WORLD);
        
        // 本地求和
        for(int i = 0; i <= loc_n - 1; i++) loc_sum += loc_array_p[i];

        // 清空动态内存
        delete []loc_array_p;
        delete []array_p;
        
    }else{
        

        // 采用广播的方式，直接获取n
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if(my_rank == comm_sz - 1) loc_n = n / comm_sz + n % comm_sz;
        else loc_n = n / comm_sz;

        loc_array_p = new int[loc_n];

        // 接收数据
        MPI_Scatterv(array_p, sendcounts, displs, MPI_INT, loc_array_p, loc_n, MPI_INT, 0, MPI_COMM_WORLD);

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

