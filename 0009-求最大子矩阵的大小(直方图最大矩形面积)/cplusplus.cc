#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <assert.h>
using namespace std;

/**
    求最大子矩阵的大小
    题目：给定一个整型矩阵map，其中的值只有0和1，求其中全是1的所有矩形区域中最大的矩形区域中1的
    数量。
    例如：
        1 1 1 0
    其中，最大的矩形区域有3个1，所以返回3。
    再如：
        1 0 1 1
        1 1 1 1
        1 1 1 0
    其中，最大的矩形区域有6个1，所以返回6。
    需要注意时间复杂度要求为O(NxM)。
*/
/**
    解题思路：
    1. 矩阵的行数为N，以每行为单位，统计以当前行作为底部的情况下，往上数有多少连续的1，我们暂时称
    为高度数组height[]，其数组长度为矩阵的列数M。对于行数的每次累加，都计算一下当前行下的高度数组
    height[]内的最大矩形是什么。然后再比较每行为底的情况下最大矩形即为整个矩阵的最大子矩阵。
    2. 对于每行为底情况下的高度数组height[]的求解公式：
    height[j] = map[i][j] == 0 ? 0 : height[j] + 1
    3. 对于每行为底情况下的高度数组height[]中最大矩形的求解，可以等同于求解将height[]数组画到二维
    坐标系中的直方图中可扩展出的最大矩形的面积。对于直方图中的扩展，对于直方图中的每根柱形，都可
    以以它的高度所能向左和向右扩展到且不超出柱形区域的大矩形。
    4. 从算法的角度看，对于第i列所属的最大矩形的求解，可以等同于向左和向右寻找第一个小于本高度的
    列数j和k(类似于上一个求解数组MaxTree的问题，可以用栈来实现，不过栈底到栈顶为递增序列)，然后对
    于夹在这两个列数中间的区域即为以第i列的高度为准的最大矩形区域，其宽度为(k - j - 1)
*/

static int mMaxRectSize = 0;
static void popAndAddMap(int rmargin, vector<int>& arr, stack<int>& stk, map<int, int>& mp) {
    assert(!stk.empty());
    // 将当前栈顶的数(索引值)弹出，本次即为求解该索引对应的柱形可扩展的最大矩形的宽度
    int index = stk.top();
    stk.pop();
    // 因为栈不包含相等的数且严格按照递增(栈底->栈顶)，对于相邻的和刚取出的索引值对应的柱形高度
    // 相同的情况，根据之前的压栈原则，取到的索引永远都是最左侧的，因此只要将该索引值再左移一位
    // 对应的索引值即是左边界，即：lmargin = index - 1，再根据上述(r - l - 1)公式可得到如下：
    int width = rmargin - index;
    // 以索引值为key值，将其对应的最大矩形宽度作为value值保存到map中。
    mp[index] = width;
    // 求取最大面积
    int rectSize = width * arr[index];
    mMaxRectSize = rectSize > mMaxRectSize ? rectSize : mMaxRectSize;
}

static int getMaxRectSize(vector<int>& height) {
    stack<int> nStack;
    // 用来存储height数组每个高度所能扩展的最大宽度的MAP
    map<int, int> widthMapForHeights;
    int areaSize;
    for (int i = 0; i < height.size(); i++) {
        // 如果当前位置所在的高度数组height值小于栈顶保存的值，说明已经找到栈顶元素对应的右边界，
        // 因此我们计算并将此元素对应的矩形宽度保存下来
        while (!nStack.empty() && height[nStack.top()] > height[i]) {
            popAndAddMap(i, height, nStack, widthMapForHeights);
        }
        // 如果栈顶元素和当前元素相等，说明在直方图中两个柱形高度一样，因此可以预见两个相邻且同高
        // 度的柱形，其可扩展的最大矩形是同一个。
        // 换句话说，这个栈并不包含相等的元素，而是严格按照从栈底到栈顶依次递增序列！
        if (!nStack.empty() && height[nStack.top()] == height[i]) continue;
        // 比栈顶元素大，将当前位置i压入栈中
        nStack.push(i);
    }
    // 经过上述处理，如果栈中还留有元素，说明其右边界为数组的边界，因此直接将数组的右边界设为
    // 栈中其余元素对应最大矩形的右边界，对栈中其余元素均以此处理原则迭代处理。
    while (!nStack.empty()) {
        popAndAddMap(height.size(), height, nStack, widthMapForHeights);
    }
    return mMaxRectSize;
}

int main(int nargs, char* argv[]) {
    vector<int> arr = {3, 2, 3, 0, 3, 6};
    getMaxRectSize(arr);
    cout << "The max rect area size is " << mMaxRectSize << endl;;
    return 0;
}
