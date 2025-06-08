#include <stdio.h>
#include <stdlib.h>

//minheap struct
typedef struct {
    int *data; //arr
    int size; //number of data in arr
    int capacity; //length of arry
} MinHeap;


MinHeap* createHeap(int capacity) {
    //make table
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    //initialize data[index]. +1 coz index start w 1
    heap->data = (int*)malloc((capacity+1) * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert(MinHeap *heap, int value) {
    if (heap->size >= heap->capacity) return; //full
    
    //add at end
    heap->size++;
    heap->data[heap->size] = value;
    heapifyUp(heap, heap->size);
}


void heapifyUp(MinHeap *heap, int index) {
    //go up if data smaller
    if (index > 1 && heap->data[index] < heap->data[index/2]) {
        swap(&heap->data[index], &heap->data[index/2]);
        heapifyUp(heap, index/2);
    }
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int extractMin(MinHeap *heap) {
    if (heap->size == 0) return -1;
    
    int min = heap->data[1]; //get smallest 
    heap->data[1] = heap->data[heap->size];
    heap->size--; //decrease size
    heapifyDown(heap, 1);
    
    return min;
}

void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int left = index*2;
    int right = index*2 +1;
    
    if (left <= heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    
    if (right <= heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;
    
    //go down if data bigger
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}


void heapSort(int arr[], int n) {
    MinHeap *heap = createHeap(n);

    //insert data into heap
      for (int i = 0; i < n; i++) {
        insert(heap, arr[i]);
    }
    

    //extract elemet in sorted ord
    for (int i = 0; i < n; i++) {
        arr[i] = extractMin(heap); //sort data
    }
    
    free(heap->data);
    free(heap);
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(m * sizeof(int));
    

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    

    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }
    

    heapSort(a, n);
    heapSort(b, m);
    

    int i = 0, j = 0;
    int symmetric_diff_count = 0;
    
    while (i < n && j < m) {
        if (a[i] == b[j]) { //element in both a b
            i++; //move pointer (skip coz same)
            j++;
        } else if (a[i] < b[j]) { //element in a but not in b
            symmetric_diff_count++; //counter ++
            i++; //move pointer
        } else {
            symmetric_diff_count++; //elem in b but not in a, counter ++
            j++; //move pointer
        }
    }
    
    symmetric_diff_count += (n - i) + (m - j); //add the rest
    
    printf("%d\n", symmetric_diff_count);
    
    free(a);
    free(b);
    
    return 0;
}