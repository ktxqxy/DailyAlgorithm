#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

/**
    如何仅用递归函数和栈操作逆序一个栈
    题目：一个栈依次压入1、2、3、4、5，那么从栈顶到栈底分别为5、4、3、2、1。将这个栈转置后，
    从栈顶到栈底为1、2、3、4、5，也就是实现栈中元素的逆序，但是只能用递归函数来实现，不能用其
    他数据结构。
*/
/**
    解题思路：题目要求仅用递归函数来实现对栈的转置，并且不能借用别的任何数据结构。
    因此我们需要设计2个递归函数：
    1. 第一个递归函数用来将输入的栈中的栈底元素取出并从栈中删除；
    2. 第二个递归函数用来逆序原栈。
    需要注意的是这两个递归都是递归到底后返回的时候才会压栈，即倒序压栈。第一次通过倒序压栈可以
    将栈底的元素弹出，而第二次通过倒序压栈可以实现栈的逆序。
*/

// 第一个递归函数
static int getAndRemoveLastElement(stack<int>& stk) {
    // Step 1: 先将栈顶元素弹出，并保存下此时的栈顶值
    int last = stk.top();
    stk.pop();
    // Step 2: 如果此时栈为空，则说明刚弹出的栈顶元素即为最后一个元素，递归结束开始返回，且返回
    // 值是这个这个最后一个元素
    if (stk.empty()) return last;
    int ret = getAndRemoveLastElement(stk);
    // Step 3: 在递归结束后返回的过程中压栈(逆序)，这样即可确保弹出栈底元素后对其余元素无影响。
    stk.push(last);
    return ret;
}

// 第二个递归函数
static void reverse(stack<int>& stk) {
    if (stk.empty()) return;
    // Step 1: 先获取此时栈底元素值，随着递归的迭代，是从栈顶到栈底
    int val = getAndRemoveLastElement(stk);
    // Step 2: 递归操作
    reverse(stk);
    // Step 3: 在递归结束后，返回时将前面获取的栈底元素压栈。而根据前面的操作，是依次从栈底到
    // 栈顶取出元素，因此此时我们通过倒序压栈的方法，即可保证在新构造的栈中相对原栈是转置的。
    stk.push(val);
}

int main(int nargs, char* argv[]) {
    stack<int> mStack;
    mStack.push(1);
    mStack.push(2);
    mStack.push(3);

    reverse(mStack);

    cout << "The reversed stack is ";
    while (!mStack.empty()) {
        cout << mStack.top() << " ";
        mStack.pop();
    }
    cout << endl;
    return 0;
}
