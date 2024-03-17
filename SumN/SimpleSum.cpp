// 代码简介：简单的串行算法，求给定的n个数的和

#include<iostream>
using namespace std;

int main(){
    int n; cin >> n;

    int sum = 0;
    while(n--){
        int tmp; cin >> tmp;
        sum += tmp;
    }

    cout << "Sum is " << sum << endl;

    return 0;
}




