#include<bits/stdc++.h>
using namespace std;

void Set(int n, int n1, char* compilerMul, char* compilerSum, int iterations);

int main(){

    char compilerMul[] = "arm-linux-gnueabi-g++ -O3 -fopenmp -static -o sumn Sumn.cpp";
    char compilerSum[] = "arm-linux-gnueabi-g++ -O3 -fopenmp -static -o mmul MMul.cpp";
    int iterations = 100;

    for(int n = 200, n1 = 6; n <= 2200, n1 <= 26; n += 200, n1 += 2){
        Set(n, n1, compilerMul, compilerSum, iterations);     
    }
   
}

void Qemu(){
    system("qemu-arm mmul");
    system("qemu-arm sumn");
}

void NormalRun(){
    system("./mmul");
    system("./sumn");
}

void Set(int n, int n1, char* compilerMul, char* compilerSum, int iterations){

   // 定义参数设置文件
    ofstream InSum("Sumn.in");
    ofstream InMMul("MMul.in");
    system("rm Result.out");
    

    InMMul << n << " " << n; // 空格别漏

    InMMul.close();

    InSum << n1;
    InSum.close();
   
    // 编译运行代码，以iterations为迭次数
    system(compilerMul);
    system(compilerSum);

    for(int i = 1; i <= iterations; ++i){
        Qemu();
    }

    // 读取结果，求平均值
    struct MMulCost{
        double SimpleCost = 0;
        double CacheCost = 0;
    }costM;
    
    struct SumnCost{
        double SimpleCost = 0;
        double RecursionCost = 0;
        double OPCost = 0;
        double Step2 = 0;
    }costS;

    int cnt = 0;
    
    ifstream Result("Result.out");
    for(int i = 1; i <= iterations; ++i){
        double MMulSimple, MMulCache, SumnSimple, SumnRecursion, SumnOP, SumnStep2;
        Result >> MMulCache >> MMulSimple >> SumnSimple >> SumnRecursion >> SumnOP >> SumnStep2;
        
        if((costM.SimpleCost +  MMulSimple) > 0) costM.SimpleCost += MMulSimple;
        else break;
        if((costM.CacheCost + MMulCache) > 0) costM.CacheCost += MMulCache;
        else break;
        if((costS.SimpleCost + SumnSimple) > 0) costS.SimpleCost += SumnSimple;
        else break;
        if((costS.RecursionCost + SumnRecursion) > 0) costS.RecursionCost += SumnRecursion;
        else break;
        if((costS.OPCost + SumnOP) > 0) costS.OPCost += SumnOP;
        else break;
        if((costS.Step2 + SumnStep2) > 0) costS.Step2 += SumnStep2;
        else break;

        cnt++;

    }
    Result.close();

    // 控制台信息
    printf("=========================================================\n");

    printf("方阵参数 %d*%d     迭代次数为 %d \n", n, n, cnt);
    printf("朴素算法平均用时为 %lf ms\n", costM.SimpleCost * 1000 / cnt);
    printf("Cathe优化平均用时为 %lf ms\n", costM.CacheCost * 1000 / cnt);

    printf("=========================================================\n");

    printf("求和参数 2^%d     迭代次数为 %d \n", n1, cnt);
    printf("朴素算法平均用时为 %lf ms\n", costS.SimpleCost * 1000 / cnt);
    printf("递归优化平均用时为 %lf ms\n", costS.RecursionCost * 1000 / cnt);
    printf("非递归优化平均用时为 %lf ms\n", costS.OPCost * 1000 / cnt);
    printf("双步循环展开平均用时为 %lf ms\n", costS.Step2 * 1000 / cnt);

        // 导入文件信息
    ofstream Summary("Summary.csv", std::ios::out|std::ios::app);
    
    Summary 
        << costM.SimpleCost * 1000 / cnt << ","
        << costM.CacheCost * 1000 / cnt << ","
        << costS.SimpleCost * 1000 / cnt << ","
        << costS.RecursionCost * 1000 / cnt << ","
        << costS.OPCost * 1000 / cnt << ","
        << costS.Step2 * 1000 / cnt << ","
        << compilerMul << ","
        << compilerSum << ","
        << n << ","
        << n1 << ","
        << iterations 
    << endl;

    Summary.close();


}