#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

/**
    用一个栈实现另一个栈的排序
    题目：一个栈中元素的类型为整型，现在想将该栈从顶到底按从大到小的顺序排序，只许申请一个栈。
    除此之外，可以申请新的变量，但是不能申请额外的数据结构。如何完成排序？
*/
/**
    解题思路：利用栈的特点 - 先入后出，题目允许申请一个栈来操作，而两个栈就可以实现这样一个操
    作，把第一个栈的元素依次弹出并压入第二个栈，然后再从第二个栈依次弹出并压入第一个栈，此时
    第一个栈中元素的顺序和最一开始完全一样。因此，我们这里可以采取类似“冒泡”的策略，从第一个栈
    中依次弹出元素，然后和第二个栈的栈顶元素做比较（由于题目没有要求，这里我们假定让元素从栈底
    到栈底从大到小排列）：
    1. 在最开始先申请一个临时变量来储存从第一个栈弹出的待插入数据；
    2. 当待插入数据小于等于栈顶数据时，可直接将其压入栈；
    3. 当待插入数据大于栈顶数据时，我们将第二个栈的栈顶元素弹出并压到第一个栈中暂存，再将待插入
    数据和新的栈顶元素比较，不断按照前述策略比较下去，直到找到一个比它大的数或者到栈底，这时我们
    把待插入压入栈中，再把刚压入第一个栈的元素都弹出压回第二个栈(这个操作不需要专门处理，只需要
    按照之前的处理策略依次比较入栈即可，这个操作空间最省。如果允许多申请一个临时变量，也可以再
    用这个临时变量储存从第二个栈弹出到第一个栈的深度，这样再往回压入时可以直接用此深度直接完成
    入栈而不需要额外比较开销)，此时便完成了一个元素的排序。
*/

static void sortWithStack(stack<int>& src, stack<int>& dst) {
    int temp;
    while (!src.empty()) {
        temp = src.top();
        src.pop();
        while (!dst.empty() && dst.top() < temp) {
            src.push(dst.top());
            dst.pop();
        }
        dst.push(temp);
    }
}

int main(int nargs, char* argv[]) {
    stack<int> mStack, mSortedStack;
    mStack.push(7);
    mStack.push(3);
    mStack.push(5);
    mStack.push(6);
    mStack.push(9);
    mStack.push(2);
    sortWithStack(mStack, mSortedStack);

    cout << "The sorted stack is ";
    while (!mSortedStack.empty()) {
        cout << mSortedStack.top() << " ";
        mSortedStack.pop();
    }
    cout << endl;
    return 0;
}
