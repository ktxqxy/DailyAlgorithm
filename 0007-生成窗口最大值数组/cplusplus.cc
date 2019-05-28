#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>
using namespace std;

/**
    生成窗口最大值数组
    题目：有一个整型数组arr和一个大小为w的窗口从数组的最左边滑到最右边，窗口每次向右滑一个位置。
    如果数组长度为n，则一共产生(n - w + 1)个窗口的最大值，请实现一个函数：
    a. 输入：整型数组arr，窗口大小w
    b. 输出：一个长度为(n - w + 1)的数组res，res[i]表示每一种窗口状态下的最大值
    时间复杂度要求为O(N)
*/
/**
    解题思路：维护一个双端队列，该队列在队头到队尾的方向上维持递减序列，即队头永远是当前窗口下
    的最大值。同时由于窗口在滑动时，其左右边界的数会更新，因此用队头来维护窗口的左边界，队尾来
    维护窗口的右边界。需要注意队列保存的是源数组的下标值，而不是其元素。
*/

static void getWindowMaxArr(vector<int>& arr, int win_size, vector<int>& arr_max) {
    deque<int> deq;
    for (int i = 0; i < arr.size(); i++) {
        // step 1: 处理队头，如果队头相对滑动窗口已经过期，那么将其弹出删除
        if (!deq.empty() && deq.front() == i-win_size)
            deq.pop_front();
        // step 2: 处理队尾
        //         a. 如果队列为空，那么直接将此时的下标值加入队尾；
        //         b. 如果队列不为空，那么比较此时下标值指向的数组值和队尾保存的下标值指向的
        //            数组值，如果此时的下标值指向的数组值比队尾保存的小，那么将其直接加入队尾；
        //            反之，先将队尾的下标值弹出删除，重复此步骤直到将此下标值压入队尾。
        if (deq.empty()) {
            deq.push_back(i);
        } else {
            while (!deq.empty() && arr[i] >= arr[deq.back()]) {
                deq.pop_back();
            }
            deq.push_back(i);
        }
        // step 3: 从队头取出下标值返回即为滑动窗口在当前位置的最大值
        if (i < win_size - 1) continue;
        assert(!deq.empty());
        arr_max.push_back(arr[deq.front()]);
    }
}

int main(int nargs, char* argv[]) {
    vector<int> arr = {4, 3, 5, 4, 3, 3, 6, 7};
    vector<int> arr_max;
    int win_size = 3;
    getWindowMaxArr(arr, win_size, arr_max);
    cout << "The output is ";
    for (int i = 0; i < arr_max.size(); i++) {
        cout << arr_max[i] << " ";
    }
    cout << endl;
    return 0;
}
