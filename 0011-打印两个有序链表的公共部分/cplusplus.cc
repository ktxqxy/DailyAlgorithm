#include <iostream>
#include <assert.h>
using namespace std;

/**
    打印两个有序链表的公共部分
    题目：给定两个有序链表的头指针head1和head2，打印两个链表的公共部分。
*/
/**
    解题思路：这个问题比较简单，由于是有序链表，所以我们只需要比较两个链表的头结点就好了。假定
    有序链表都是从头结点向后递增的，那么：
    1. 如果head1的值小于head2，则head1往下移动。
    2. 如果head2的值小于head1，则head2往下移动。
    3. 如果head1的值等于head2的值，则打印这个值，然后head1和head2都往下移动。
    4. 直到head1或head2有任何一个移动到NULL为止。
*/

struct Node {
    int value;
    Node* next;
};

static void printCommonPart(Node* head1, Node* head2) {
    cout << "The common part is : ";
    while (head1 && head2) {
        if (head1->value < head2->value) {
            head1 = head1->next;
        } else if (head2->value < head1->value) {
            head2 = head2->next;
        } else {
            cout << head1->value << " ";
            head1 = head1->next;
            head2 = head2->next;
        }
    }
    cout << endl;
}

int main(int nargs, char** argv) {

    return 0;
}
