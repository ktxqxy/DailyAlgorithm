#include <iostream>
#include <string>
#include <time.h>
#include <stack>
#include <assert.h>
using namespace std;

/**
    用栈来解决汉诺塔问题
    题目：大梵天创造世界的时候做了三根金刚石柱子，在一根柱子上从下往上按照大小顺序摞着
    64片黄金圆盘。大梵天命令婆罗门把圆盘从下面开始按大小顺序重新摆放在另一根柱子上。并且规定，
    任何时候，在小圆盘上都不能放大圆盘，且在三根柱子之间一次只能移动一个圆盘。问应该如何操作？
    思路：这三根柱子跟栈的特性非常相似，因此我们可以用等效的3个栈来解决此问题。
*/

// 将一个栈的栈顶元素弹出并压入另一个栈中
static void singleMove(stack<int>& from, stack<int>& to) {
    assert(!from.empty());
    to.push(from.top());
    from.pop();
}

const int height = 15;
/** 此函数用来处理普通汉诺塔问题。
    n: 汉诺塔的层数
    from: 第一根汉诺塔柱子
    buffer: 中间汉诺塔柱子
    to: 第三根汉诺塔柱子
    算法设计思路：
    1. 先将n - 1层圆盘从1柱移动到2柱(此步递归)
    2. 然后将1柱剩下的第n层圆盘移动到3柱(1次操作)
    3. 最后再将2柱的n - 1层圆盘移动到3柱(递归操作)
    循环上述步骤即可。
    注意点：
    1. 在处理期间，用作buffer的柱子会不停的变化，其原则是三根柱子中除去源柱子和目标柱子外的
    另一根柱子作为buffer使用。
    2. 这期间其实有个小原则，递归的本质是每次都是以完整的一次汉诺塔操作作为一次大操作，而且
    处理顺序是依次把最左侧柱子上的圆盘按照从大到小的顺序移动到最右侧，其带来的隐藏作用是由于
    圆盘在每根柱子上永远都是按照从小到大的顺序排列，因此在操作圆盘时，那些栈顶比被操作的圆盘
    大的柱子可以等同于该根柱子上没有圆盘，即可将多层数的汉诺塔问题化为底层数的汉诺塔问题，从
    而使得递归变为可能。
*/
void move(int n, stack<int>& from, stack<int>& buffer, stack<int>& to) {
    if (n <= 0) return;
    if (n == 1) {
        singleMove(from, to);
    } else {
        move(n - 1, from, to, buffer);
        move(1, from, buffer, to);
        move(n - 1, buffer, from, to);
    }
}

/**
    修改版的汉诺塔问题：现在限制不能从最左侧的塔直接移动到最右侧，也不能从最右侧直接移动到最
    左侧，而是必须经过中间。求当塔有N层的时候，打印最优移动过程和最优移动总步数。

    解题思路： 由于规则规定不能交换第一根柱子和第三根柱子的圆盘，因此相当于如果要从第一根柱子
    到第三根柱子，必须先挪到中间的柱子(第二根)上，再挪到第三根柱子上。因此在本设计中，buffer
    不能出现在move2()的接收柱子(to)上，而只能通过singleMove()来交换元素。
    其算法设计可简单归纳为: 对于n层汉诺塔而言，
    1. 先将前n - 1层圆盘从1柱移动到3柱(此步递归)
    2. 然后将1柱剩下的第n个圆盘挪到2柱
    3. 再将3柱的n - 1层圆盘从3柱挪回1柱(此步递归)
    4. 然后将2柱的那个第n层圆盘挪到3柱
    5. 最后再将1柱的n - 1层圆盘挪到3柱(此步递归)
    循环上述步骤即可完成该需求。
*/
static void move2(int n, stack<int>& from, stack<int>& buffer, stack<int>& to) {
    if (n <= 0) return;
    if (n == 1) {
        singleMove(from, buffer);
        singleMove(buffer, to);
    } else {
        move2(n - 1, from, buffer, to);
        singleMove(from, buffer);
        move2(n - 1, to, buffer, from);
        singleMove(buffer, to);
        move2(n - 1, from, buffer, to);
    }
}

string getTime() {
    time_t timep;
    time (&timep); //获取time_t类型的当前时间
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//对日期和时间进行格式化
    return tmp;
}

int main(int nargs, char* argv[])
{
    stack<int> from;
    stack<int> buffer;
    stack<int> to;
    for (int i = height; i > 0; i--) {
        from.push(i);
    }
    //cout << "The input number stack is: ";
    //while (!from.empty()) {
    //    cout << from.top() << " ";
    //    from.pop();
    //}
    //cout << endl;
    cout << getTime() << endl;
    move2(height, from, buffer, to);
    cout << getTime() << endl;
    cout << "The output number stack is: ";
    while (!to.empty()) {
        cout << to.top() << " ";
        to.pop();
    }
    cout << endl;
    return 0;
}
