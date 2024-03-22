## README


### 项目说明
在`ParallelPrograming`文件夹下，有子文件夹`lab1`,其中存放的`Controller.cpp`文件是测试程序的**控制文件**

```c++
    //  Contorller.cpp   主函数main()

    // 设置编译选项及迭代次数
    char compilerMul[] = "arm-linux-gnueabi-g++ -O3 -fopenmp -static -o sumn Sumn.cpp";
    char compilerSum[] = "arm-linux-gnueabi-g++ -O3 -fopenmp -static -o mmul MMul.cpp";
    int iterations = 100;
	
    // 以固定的迭代次数、不同规模，运行待测量算法
    for(int n = 200, n1 = 6; n <= 2200, n1 <= 26; n += 200, n1 += 2){
        Set(n, n1, compilerMul, compilerSum, iterations);     
    }
```
### 使用方法

Step1 `g++ -Wall -g -o cont Controller.cpp`

Step2 `./cont`



### 运行结果

```shell
=========================================================
方阵参数 200*200     迭代次数为 100 
朴素算法平均用时为 0.108844 ms
Cathe优化平均用时为 0.139082 ms
=========================================================
求和参数 2^6     迭代次数为 100 
朴素算法平均用时为 0.036696 ms
递归优化平均用时为 0.027620 ms
非递归优化平均用时为 0.025715 ms
双步循环展开平均用时为 0.000443 ms
```

### 结果存储

存储在同文件夹的`Summary.csv`文件中, 大致内容如下
分别存储不同`算法运行时间（ms）`，以及所用到的`编译选择`，还有算法执行的`运算规模`

| MulSimple |  MulCache |  SumnSimple |  SumnRetursion |  SumnOP    |  SumnStep2 |  CompilerMul         |  CompilerSum         |  Muln |  Sumn |  iterations |
|-----------|-----------|-------------|----------------|------------|------------|----------------------|----------------------|-------|-------|-------------|
| 0.0637474 | 0.0783114 | 0.00014054  | 0.00026209     | 0.00019464 | 7.383E-05  | g++ -o sumn Sumn.cpp | g++ -o mmul MMul.cpp | 200   | 6     | 100         |
| 0.277339  | 0.316899  | 0.00044668  | 0.00059683     | 0.0005112  | 0.00020726 | g++ -o sumn Sumn.cpp | g++ -o mmul MMul.cpp | 400   | 8     | 100         |
| 0.661052  | 0.740509  | 0.00106761  | 0.00182696     | 0.00163201 | 0.00072635 | g++ -o sumn Sumn.cpp | g++ -o mmul MMul.cpp | 600   | 10    | 100         |
| 1.2723    | 1.21216   | 0.00385697  | 0.00655208     | 0.00561345 | 0.00286627 | g++ -o sumn Sumn.cpp | g++ -o mmul MMul.cpp | 800   | 12    | 100         |
| 2.1042    | 1.86335   | 0.0159011   | 0.0244534      | 0.0226077  | 0.0110445  | g++ -o sumn Sumn.cpp | g++ -o mmul MMul.cpp | 1000  | 14    | 100         |





