题号右侧数字分别为构造函数、复制构造函数、移动构造函数、赋值运算、移动赋值运算被调用的次数
(1)：2、1、3、0、1
Test F(Test a){
    Test b = std::move(a);
    return b;
}
int main(){
    Test a;//调用默认构造函数
    a = 1;//这里调用了构造函数并进行了移动赋值运算，
    Test A = F(a);//先调用拷贝构造函数，调用一次移动构造函数构造b，再调用移动构造函数return，再调用移动构造函数构造A
    return 0;
}

(2)：1、1、2、0、0
Test F(const Test& a){
    Test b = std::move(a);
    return b;
}
int main(){
    Test A = F(1);//先调用构造函数，进入F内部先调用拷贝构造函数构造b，再调用移动构造函数return，最后再调用移动构造函数构造A
    return 0;
}

(3)：1、0、3、0、0
Test F(Test &&a){
    Test b = std::move(a);
    return b;
}
int main(){
    Test A = F(1);//先调用构造函数，进入F内部先调用移动构造函数构造b，再调用移动构造函数return，最后再调用移动构造函数构造A
    return 0;
}

(4)：存在错误！
Test&& F(Test &a){
    Test b = a;
    return std::move(b);//返回了局部变量的引用
}
int main(){
    Test A = F(Test(1));//非常量引用必须为左值，而该处为右值
    return 0;
}

(5)：存在风险！
const Test& F(const Test& a){
    Test b = a;
    return Test(1);//此处返回了临时变量的引用
}
int main() {
    Test a;
    const Test &A = F(std::move(a));
    return 0;
}
