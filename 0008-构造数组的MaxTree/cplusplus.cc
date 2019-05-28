#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <assert.h>
using namespace std;

/**
    构造数组的MaxTree
    题目：定义一个二叉树节点结构体，据此一个数组的MaxTree定义如下：
    1. 数组必须没有重复元素。
    2. MaxTree是一颗二叉树，数组的每一个值对应一个二叉树节点。
    3. 包括MaxTree树在内且在其中每一颗子树上，值最大的节点都是树的根。
    问题：给定一个没有重复元素的数组arr，写出生成这个数组的MaxTree的函数，要求如果数组长度为N，
    则时间复杂度为O(N)、额外空间复杂度为O(N)。
*/
/**
    解题思路：
    1. 可以以如下原则来建立这棵树：
        a. 每一个数的父节点是是它左边第一个比它大的数和右边第一个比它大的数中较小的那个。
        b. 如果一个数左边没有比它大的数，右边也没有，那么这个数就是整个数组的最大值，也是MaxTree
        的根节点。
    2. 一种最先想到的算法是：根据上述原则2，我们只要使用递归算法，每层用O(N)的时间来找到最大值，
    再以此为界将数组分成两部分，依次递归完成构造。但是这种算法总的复杂度为O(N^2)，无法满足需求。
    3. 因此，需要找到一种有效率的方法来完成，方法如下：
*/
struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int val = -1) : data(val), left(NULL), right(NULL) {}
};

static void addMap(Node *node, stack<Node *>& stk, map<Node *, Node *>& mp) {
    // 栈底为空，说明无比它大的值
    if (stk.empty()) {
        mp[node] = NULL;
    } else {
        mp[node] = stk.top();
    }
}

static void addMaxTree(Node *parent, Node *child) {
    assert(parent);
    assert(child);
    if (parent->left == NULL) {
        parent->left = child;
    } else if (parent->right == NULL) {
        parent->right = child;
    } else {
        cout << "ERROR: The node has been assigned more than two children!" << endl;
    }
}

static Node* getMaxTree(vector<int>& arr) {
    // Step1: 先将输入数组值构造成一个二叉树节点数组，待后续将其构造成MaxTree树
    vector<Node *> nArr;
    for (int i = 0; i < arr.size(); i++) {
        Node *p = new Node(arr[i]);
        nArr.push_back(p);
    }
    // Step2: 新建辅助变量，一个栈结构用来快速寻找左右两边第一个比它大的数，两个map结构分别用来保
    // 存每个数找到的左边第一个比它大的数和右边第一个比它大的数
    // Note: 需要注意栈结构采用递减序列，即栈底的数最大，栈顶的数最小。这样栈底的数永远都是代表当
    // 前数的左边/右边第一个比它大的数，若栈底为空则说明其左边/右边无比它大的数。
    stack<Node *> nStack;
    map<Node *, Node *> lBigMap, rBigMap;
    // Step3: 先遍历一遍数组来填充每个数找到的左边第一个比它大的数的map
    for (int i = 0; i < nArr.size(); i++) {
        // 比较当前栈顶保存的数和当前遍历指向的数组的数的大小，两种情况：
        // 1. 如果栈顶保存的数大，则说明该栈顶的数即为当前数的左边第一个比它大的数，因此先将其保
        // 存到lBigMap中，再将当前数组的数压入栈中(因为保不齐该数是后边的数的左边第一个比它大的数
        // )；
        // 2. 如果栈顶保存的数小，则需要继续和栈保存的其他值比较(栈为递减序列)，直到找到比它大的
        // 数(如果找到栈底都没有，则说明该数左边没有比它更大的数)，应该先将栈顶的数弹出，再把它
        // 压入到栈中。
        while (!nStack.empty() && nStack.top()->data < nArr[i]->data) {
            nStack.pop();
        }
        // 填充当前节点的左边第一个比它大的map结构
        addMap(nArr[i], nStack, lBigMap);
        // 将当前数压入栈中
        nStack.push(nArr[i]);
    }
    while (!nStack.empty()) {
        nStack.pop();
    }
    // Step4: 然后再遍历一遍数组来填充每个数找到的右边第一个比它大的数的map
    for (int i = nArr.size() - 1; i >= 0; i--) {
        while (!nStack.empty() && nStack.top()->data < nArr[i]->data) {
            nStack.pop();
        }
        addMap(nArr[i], nStack, rBigMap);
        nStack.push(nArr[i]);
    }
    // Step5: 最后根据左/右最近的大值map表来构造MaxTree树
    Node *head = NULL;
    for (int i = 0; i < nArr.size(); i++) {
        Node *cur = nArr[i];
        Node *lbigger = lBigMap[cur];
        Node *rbigger = rBigMap[cur];
        if (lbigger == NULL && rbigger == NULL) {
            head = cur;
        } else if (lbigger == NULL) {
            addMaxTree(rbigger, cur);
        } else if (rbigger == NULL) {
            addMaxTree(lbigger, cur);
        } else {
            addMaxTree(lbigger->data < rbigger->data ? lbigger : rbigger, cur);
        }
    }
    return head;
}

static void printTree(Node *tree) {
    if (!tree) return;
    cout << tree->data << " ";
    printTree(tree->left);
    printTree(tree->right);
}

int main(int nargs, char* argv[]) {
    vector<int> arr = {3, 4, 5, 1, 2};
    Node *tree = getMaxTree(arr);
    cout << "The MaxTree is ";
    printTree(tree);
    cout << endl;
    return 0;
}
