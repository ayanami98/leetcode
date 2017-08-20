/******************************************************************************
 * Copyright (c)  2017, GraphSQL Inc.                                      *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 138_Copy_List_with_Random_Pointer.cpp
*
* Created on : 2017-08-20
* Author : tufeng
*
* Last Modified : Sun 20 Aug 2017 12:01:45 AM PST
******************************************************************************/

/******************************************************************************
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null.
 *
 * Return a deep copy of the list. 
 ******************************************************************************/

#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list with a random pointer.
*/
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        // copy round
        RandomListNode* cur = head;
        while (nullptr != cur) {
            RandomListNode* new_node = new RandomListNode(cur->label);
            new_node->random = cur->random;
            new_node->next = cur->next;
            cur->next = new_node;
            cur = new_node->next;
        }
        
        // correct random pointer
        cur = head;
        while (nullptr != cur) {
            if (nullptr != cur->next->random) {
                cur->next->random = cur->next->random->next;
            }
            cur = cur->next->next;
        }
        
        RandomListNode* r_head = head->next;
        RandomListNode* r_tail = head->next;
        head->next = r_tail->next;
        cur = head->next;
        while (nullptr != cur) {
            r_tail->next = cur->next;
            r_tail = r_tail->next;
            cur->next = r_tail->next;
            cur = cur->next;
        }
        return r_head;
    }
};

int main() {
  RandomListNode* head = new RandomListNode(1);
  RandomListNode* node1 = new RandomListNode(2);
 // RandomListNode* node2 = new RandomListNode(3);
 // RandomListNode* node3 = new RandomListNode(4);
 // RandomListNode* node4 = new RandomListNode(5);
 // RandomListNode* node5 = new RandomListNode(6);
 // RandomListNode* node6 = new RandomListNode(7);
  head->next = node1;
 // node1->next = node2;
 // node2->next = node3;
 // node3->next = node4;
 // node4->next = node5;
 // node5->next = node6;
 // head->random = node4;
 // node1->random = nullptr;
 // node2->random = head;
 // node3->random = node4;
 // node4->random = node2;
 // node5->random = node3;
 // node6->random = head;
  auto r = Solution().copyRandomList(head);
  while (nullptr != r) {
    cout << r->label << endl;
    r = r->next;
  }
  return 0;
  
}
