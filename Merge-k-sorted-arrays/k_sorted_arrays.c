#include<stdio.h>
#include<math.h>

# define HEAP_SIZE 20

typedef struct{
    int head;
    int arr_start_idx;
    int row_idx;
} heapinfo;


heapinfo MIN_HEAP[HEAP_SIZE];

void disp_array(int *arr, int size){

    for (int i=0;i<size;i++)
        printf("%d ",arr[i]);


    printf("\n");
}


void show_heap(heapinfo *h, int h_size, int tree_ht){
    
    int i=0, idx=0, num_elmnts_level;
    
    while (i<=tree_ht){

        if (idx >= h_size)
            break;
        
        num_elmnts_level = pow(2,i);

        printf("Level: %d\tElemts: ",i);

        for (int j=1; j<=num_elmnts_level; j++)
        {
            if (idx >= h_size)
                break;

            printf("%d ", h[idx].head);
            idx++;
        }

        printf("\n");
        i++;
        
    }


}

void swap_val(heapinfo *p1, heapinfo *p2){
    
    heapinfo tmp = *p1;
    
    // to copy all members: struct x = y; where `y` is already initialized.
    *p1 = *p2;
    *p2 = tmp;

}

void min_heapify(heapinfo *Arr, int i, int heap_size){
    int left, right, smallest; // Indices to consider for heapify.

    left = 2*i + 1;
    right = 2*i + 2;
    smallest = i;

    if (left < heap_size && Arr[left].head < Arr[i].head)
        smallest = left;

    if (right < heap_size && Arr[right].head < Arr[smallest].head)
        smallest = right;

    if (smallest!=i){
        swap_val(Arr+i, Arr+smallest);
        min_heapify(Arr, smallest, heap_size);
    }

}

void build_tree_from_arrays(int (*arr)[4], int num_arrays, int arr_length, heapinfo *hi){
    
    for (int i=0; i<num_arrays; i++)
    {
        hi[i].head = **arr;
        hi[i].arr_start_idx = 1;
        hi[i].row_idx = i;

        arr++;
    }    

}

void build_min_heap(heapinfo *Arr, int heap_size){

    for (int i=(heap_size-1)/2; i>=0; i--)
        min_heapify(Arr, i, heap_size);

}

void heapify_insert(heapinfo *heap, int heap_size){
    
    int parent_idx, current_idx = heap_size-1;

    while (current_idx > 0)
    {
        // parent idx;
        parent_idx = (current_idx - 1)/2;

        if (heap[current_idx].head < heap[parent_idx].head)
            swap_val(heap+parent_idx, heap+current_idx);

        current_idx = parent_idx;
    }
}


int sort_k_arrays(heapinfo *heap, int (*p)[4], int heap_size, int array_size, int *result){
    
    heapinfo minm_data, new_data;
    int idx=0, *array_loc;
    
    // Iterate for total_n elements
    while (heap_size > 0)
    {

        minm_data = heap[0];

        result[idx] = minm_data.head;
        idx++;
        
        // 1. Extract MIN: O(log k); k = heap-size
        heap[0] = heap[heap_size-1];
        heap_size--;
        min_heapify(heap, 0, heap_size);


        // 2. New data to insert.
        if (minm_data.arr_start_idx < array_size)
        {
            array_loc = p[minm_data.row_idx] + minm_data.arr_start_idx;
            new_data.head = *array_loc;
            new_data.row_idx = minm_data.row_idx;
            new_data.arr_start_idx = minm_data.arr_start_idx + 1;

            // 3. Insert key: O(log k); k = heap-size
            heap[heap_size] = new_data;
            heap_size++;

            printf("after Insert... Heap-size: %d\n", heap_size);
            heapify_insert(heap, heap_size);
            
        }
    }

    printf("\nSorted Array...\n");
    disp_array(result, idx);
       

    // min_heapify(heap, )
}


int main(){

    int NUM_ARRS = 3, ARR_LENGTH = 4, TOTAL_N;

    int arr[][4] = {{1, 3, 5, 7}, 
                    {2, 4, 6, 8}, 
                    {0, 9, 10, 11}};

    build_tree_from_arrays(arr, NUM_ARRS, ARR_LENGTH, MIN_HEAP);
    // show_heap(MIN_HEAP, NUM_ARRS, 1);

    // Step 0: O(k); k = heap-size
    build_min_heap(MIN_HEAP, NUM_ARRS);

    printf("\n");
    // show_heap(MIN_HEAP, NUM_ARRS, 1);
    // disp_array(MIN_HEAP, NUM_ARRS);
    
    TOTAL_N = (int)(sizeof(arr)/sizeof(**arr));
    
    int res[TOTAL_N];

    sort_k_arrays(MIN_HEAP, arr, NUM_ARRS, ARR_LENGTH, res);

    return 0;
}