#include <stdio.h>
#include <stdlib.h>

// Min heap implementation
typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

// Create a new min heap
MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Insert element into heap
void insert(MinHeap *heap, int value) {
    if (heap->size >= heap->capacity) return;
    
    heap->data[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size);
}

// Heapify up (maintain min heap property)
void heapifyUp(MinHeap *heap, int index) {
    int parent = (index - 1) / 2;
    
    if (index > 0 && heap->data[index] < heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        heapifyUp(heap, parent);
    }
}

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Extract minimum element from heap
int extractMin(MinHeap *heap) {
    if (heap->size <= 0) return -1;
    
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size];
    heap->size--;
    heapifyDown(heap, 0);
    
    return min;
}

// Heapify down (maintain min heap property)
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;
    
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

// Heap sort function
void heapSort(int arr[], int n) {
    MinHeap *heap = createHeap(n);
    buildHeap(heap, arr, n);
    
    for (int i = 0; i < n; i++) {
        arr[i] = extractMin(heap);
    }
    
    free(heap->data);
    free(heap);
}

// Build heap from array
void buildHeap(MinHeap *heap, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        heap->data[i] = arr[i];
    }
    heap->size = n;
    
    // Start from last non-leaf node and heapify down
    for (int i = (n - 2) / 2; i >= 0; i--) {
        heapifyDown(heap, i);
    }
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(m * sizeof(int));
    
    // Read set A
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // Read set B
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }
    
    // Sort both arrays using heap sort
    heapSort(a, n);
    heapSort(b, m);
    
    // Use two pointers to find symmetric difference
    int i = 0, j = 0;
    int symmetric_diff_count = 0;
    
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            // Skip common elements
            i++;
            j++;
        } else if (a[i] < b[j]) {
            // Element in A but not in B
            symmetric_diff_count++;
            i++;
        } else {
            // Element in B but not in A
            symmetric_diff_count++;
            j++;
        }
    }
    
    // Add remaining elements
    symmetric_diff_count += (n - i) + (m - j);
    
    printf("%d\n", symmetric_diff_count);
    
    free(a);
    free(b);
    
    return 0;
}