#include<stdio.h>
#include<stdlib.h>

# define MAX_HEAP_SIZE 10000

// LL- structure.
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct{
    int pri;
    struct ListNode *next_ptr;
} PQ;


void swap_PQ(PQ *p1, PQ *p2){
    PQ tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


int list2tree(struct ListNode** lists, int listsSize, PQ *heap){
    int count = 0;

    // Takes: O(k) : k = |listsSize|
    
    for(int i=0; i<listsSize; i++){
        
        if (lists[i])
        {   
            heap[count].pri = lists[i]->val;
            heap[count].next_ptr = lists[i]->next;

            count++;

        }
    }
    
    return count;
}

void min_heapify(PQ *heap, int i, int heap_size){
    int left, right, smallest=i;

    left = 2*i+1;
    right = 2*i+2;

    if (left<heap_size && heap[left].pri < heap[i].pri)
        smallest = left;
    if (right<heap_size && heap[right].pri < heap[smallest].pri)
        smallest = right;
    
    if (smallest!=i){
        swap_PQ(heap+i, heap+smallest);
        min_heapify(heap, smallest, heap_size);
    }
}


void heap_insert(PQ *heap, int heap_size){
    int parent_idx, cur_idx = heap_size-1;

    while(cur_idx > 0){
        parent_idx = (cur_idx-1)/2;

        if(heap[cur_idx].pri < heap[parent_idx].pri)
            swap_PQ(heap+parent_idx, heap+cur_idx);

        cur_idx = parent_idx;
    }

}

void build_min_heap(PQ *pq, int heap_size){
    int cur_idx = heap_size-1;

    if (cur_idx < 0)
        return;

    for (int i=(cur_idx-1)/2; i>=0; i--)
        min_heapify(pq, i, heap_size);
}


struct ListNode* insert_data_at_end(struct ListNode* head, int data){
    struct ListNode *new, *cur=head;
    
    new = (struct ListNode*)malloc(sizeof(struct ListNode));
    new->val = data;
    new->next = NULL;

    if (!head)
        return new;

    while(cur->next)
        cur = cur->next;
    
    cur->next = new;

    return head;
}



struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    PQ heap[MAX_HEAP_SIZE], min, new_data;
    int heap_size;
    struct ListNode* sorted = NULL;

    heap_size = list2tree(lists, listsSize, heap); // O(k)
    build_min_heap(heap, heap_size); // O(k)

    while (heap_size > 0){
        min = heap[0];
        sorted = insert_data_at_end(sorted, min.pri); // O(n); Note: avg. case of n insertions in heap: O(1)
                                                      // Best Case: O(1): maintain head and tail
        
        // O(log k) [Extract min] 
        heap[0] = heap[heap_size-1];
        heap_size--;
        min_heapify(heap, 0, heap_size); 

        if (min.next_ptr){
            
            new_data.pri = min.next_ptr->val;
            new_data.next_ptr = min.next_ptr->next;
            
            // Insert: O(log k)
            heap[heap_size] = new_data;
            heap_size++;
            heap_insert(heap, heap_size);

        }

    } 
    
    return sorted;

}

