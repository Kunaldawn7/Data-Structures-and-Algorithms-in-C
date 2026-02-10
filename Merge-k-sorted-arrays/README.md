## LeetCode Problem 23: [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

<b>Problem Statement:</b>

You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

*Merge all the linked-lists into one sorted linked-list and return it.*

**Example:**


```
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6
```

 

The implementation is performed using the `min-heap` data-structure. I have provided 2 versions of it:

1. The input being passed as `2D-arrays`  (my own version).
2. The **Leetcode** version: The evaluation performed through the
   `struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)` function entry-point.
