#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

/**
    由两个栈组成的队列
    题目：编写一个类，用两个栈实现队列，支持队列的基本操作(add、poll、peek)。
*/
/**
    解题思路：栈的特点是先入后出，而队列的特点是先入先出，因此用两个栈正好可以把顺序反过来从而
    实现类似队列的操作。具体操作如下：
    1. 一个栈专门用于入队操作，另一个栈专门用于出队操作。压入数据时只往第一个栈中压入，弹出数据
    时只从第二个栈中弹出。将第一个栈中的数据全部压入第二个栈中，再从第二个栈中弹出即可实现类似
    队列的操作。
    2. 但是需要特别注意一点，在将第一个栈中的数据压入第二个栈时，一定要确保第二个栈的数据已经
    全部弹出，否则不可做此操作，否则就会导致之前第二个栈中未弹出的数据被新压入的数据压在底部
    从而不能达到队列先入先出的要求。
*/

template <typename T>
class MyQueue {
public:
    void add (T data) {
        mPushStack.push(data);
    }
    T peek() {
        // 仅返回队列头的元素
        return internalTop();
    }
    T poll() {
        T ret = internalTop();
        // 从队列中删除元素
        mPopStack.pop();
        return ret;
    }
    bool empty() {
        return (mPushStack.empty() && mPopStack.empty());
    }
private:
    stack<T> mPushStack;
    stack<T> mPopStack;
    T internalTop() {
        if (mPopStack.empty()) {
            while (!mPushStack.empty()) {
                mPopStack.push(mPushStack.top());
                mPushStack.pop();
            }
        }
        assert(!mPopStack.empty());
        return mPopStack.top();
    }
};

int main(int nargs, char* argv[]) {
    MyQueue<int> myQueue;
    myQueue.add(1);
    myQueue.add(2);
    myQueue.add(3);
    myQueue.add(4);
    myQueue.add(5);
    myQueue.add(6);

    while (!myQueue.empty()) {
        cout << "Output value " << myQueue.poll() << endl;
    }
    return 0;
}
