#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

/**
    设计一个有getMin功能的栈
    题目：实现一个特殊的栈，在实现栈的基本功能的基础上，再实现返回栈中最小元素的操作。
    要求：
        1. pop、push、getMin操作的时间复杂度都是O(1)
        2. 设计的栈类型可以使用现成的栈结构
*/
/**
    解题思路：对于此问题，重点要从栈结构的特点入手，先入后出，利用该特点可以帮助我们非常方便的
    解决此问题。在设计上，我们可以使用两个栈，其中一个栈实现基本的栈的功能，另一个栈用来保存栈
    的最小值。具体操作如下：
    数据压入规则：当有一个新的数到来时，
    1. 先将其压入第一个正常的栈中
    2. 然后对该数和第二个栈的栈顶元素做比较，有以下三种情况：
        a. 如果该栈为空，则直接将该数压入
        b. 如果该数小于等于栈顶元素，则直接将该数压入
        c. 如果该数大于栈顶元素，则不做任何操作。这一步是整个算法的核心，首先这个栈从栈底到栈
        顶是递减序列，即栈顶元素是整个栈的最小值，而又因为栈结构的特点是先入后出，因此当后压入
        的数比当前栈顶元素大时，其实根本没必要将其保存，因为在做弹出操作时，它要比栈底部的元素
        更早弹出，也就意味着这个数的弹出对整个栈的最小值没有任何影响，因为当前保存的最小值处于
        栈中更底部的位置。而如果我们不保存这个元素，对于我们后续的弹出操作很方便。因为最小值栈
        的顺序和另一个正常栈的顺序完全一致，在做弹出操作时，只需要每次将其弹出的数和该栈的栈顶
        元素做比较即可，如果相等，将该栈的栈顶元素也弹出即可。
    数据弹出规则：
    1. 先将正常栈中的栈顶元素弹出
    2. 然后对弹出的数和另一个最小值栈的栈顶元素做比较，有两种情况：
        a. 如果两个数相等，则将最小值栈的栈顶元素也弹出
        b. 如果不相等，则只有一种可能，弹出的数比最小值栈的栈顶元素大，此时不做任何操作
*/

template <typename T>
class MyStack {
public:
    void push(T data) {
        if (mStackMin.empty()) {
            mStackMin.push(data);
        } else if (data <= mStackMin.top()) {
            mStackMin.push(data);
        }
        mStackData.push(data);
    }
    T pop() {
        assert(!mStackData.empty());
        assert(!mStackMin.empty());
        T value = mStackData.top();
        mStackData.pop();
        if (value == mStackMin.top()) {
            mStackMin.pop();
        }
        return value;
    }
    T getMin() {
        assert(!mStackMin.empty());
        return mStackMin.top();
    }
    bool empty() {
        return mStackData.empty();
    }
private:
    stack<T> mStackData;
    stack<T> mStackMin;
};

int main(int nargs, char* argv[]) {
    MyStack<int> mStack;
    mStack.push(3);
    mStack.push(4);
    mStack.push(5);
    mStack.push(1);
    mStack.push(2);
    mStack.push(1);

    while (!mStack.empty()) {
        cout << "Current min value is " << mStack.getMin() << endl;
        cout << "Pop value " <<  mStack.pop() << endl;
    }
    return 0;
}
