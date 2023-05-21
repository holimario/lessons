#include<iostream>
#include<vector>
#include<cmath>
#include<functional>
#include"myqueriable.h"

using namespace std;

int fn(int x){return x*x;}
function<int(int)> op = fn;

int main(){
    vector<int> vec = {2, 3, 4, 5};
    auto li = from(vec)
        .apply(op);
    for(int i = 0; i < li.size(); i++){
        cout << li[i] << endl;
    }
}