## LeetCode Problem 23: [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

<b>Problem Statement:</b>

You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

*Merge all the linked-lists into one sorted linked-list and return it.*

 

The implementation is performed using the `min-heap` data-structure. I have provided 2 versions of it:

1. The input being passed as `2D-arrays`  (my own version).
2. The **Leetcode** version: The evaluation performed through the `struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)` function entry-point.