#include <iostream>
using namespace std;

// bubble sort 
// compares adjacent element and swaps, in each pass the larger elmt gets bubbled up to top
// best : n [optimization], avg : n2, worst : n2
// stable
void bubblesort(int arr[],int n){
    // bool swapped;
    for(int i = 0; i < n - 1; ++i) {
        // swapped = false;
        for(int j = 0; j < n - i - 1; ++j) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                // swapped = true;
            }
        }
        // No swaps means the array is already sorted
        // if(!swapped)
            // break;
    }
}

// insertion sort
// builds the final sorted array one element at a time, [divides array into left part : sorted and right : unsorted]
// by comparing the current element to its left and inserting it in the correct position
// playing cards in your hand.
// best : n [when already sorted], avg : n2, worst : n2
// stable
void insertionsort(int arr[],int n){
    for(int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// selection sort
// repeatedly finds the minimum element from the unsorted part of the array 
// and swaps it with the first unsorted element.
// best : n2 , avg : n2, worst : n2
// unstable
void selectionsort(int arr[],int n){
    for(int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for(int j = i + 1; j < n; ++j) {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// merge sort
// divides the array into halves,
// recursively sorts them, and then merges the sorted halves back together.
// best,avg,worst :nlogn
// stable
// not in place [sc:n]

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}
void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// quicksort
// selects a pivot element and partitions the array such that:
// all elements less than the pivot go to the left
// all elements greater than the pivot go to the right
// it then recursively sorts the subarrays.
// best,avg : nlogn, worst : n2[sorted ip with first/last pivot]
// inplace 
// unstable
// sc : logn due to recursion

int partition(int arr[], int low, int high) {
    int pivot = arr[low];  // First element as pivot
    int i = low + 1;
    int j = high;
    while (true) {
        // Move i right while arr[i] < pivot
        while (i <= high && arr[i] <= pivot) i++;
        // Move j left while arr[j] > pivot
        while (j >= low && arr[j] > pivot) j--;
        // If pointers cross, break
        if (i >= j)
            break;
        swap(arr[i], arr[j]);
    }
    // Place pivot in correct position
    swap(arr[low], arr[j]);
    return j;  // Return pivot index
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1);         
        quickSort(arr, pi + 1, high);       
    }
}

//Heap Sort
//create a heap and keep on deleting nodes to get a sorted order
//TC : nlogn all cases [since heapify is called n times which is logn function]
//SC : const
//unstable, inplace
void heapify(int arr[], int n, int i) {
    int largest = i;          
    int left = 2 * i + 1;     
    int right = 2 * i + 2; 
    
    if (left < n && arr[left] > arr[largest])
    largest = left;
    
    if (right < n && arr[right] > arr[largest])
    largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);
    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
//Count Sort
// non comparison based sort
// tc :o(n+k), sc :o(k+1), k : max elmt
// not in place, not stable
void countingSort(int arr[], int n) {
    //max value
    int maxVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    // count array
    int* count = new int[maxVal + 1]();
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }
    // main process
    int index = 0;
    for (int i = 0; i <= maxVal; ++i) {
        while (count[i]-- > 0) {
            arr[index++] = i;
        }
    }
    delete[] count;
}
//REMAINING : Radix,Shell,Bucket...

int main(){
    int arr[]={2,41,2,12,41,2,35,62,742,31};
    int n = sizeof(arr)/sizeof(int);
    // bubblesort(arr,n);
    // insertionsort(arr,n);
    // selectionsort(arr,n);

    // mergeSort(arr,0,n-1);
    // quickSort(arr,0,n-1);
    // heapSort(arr,n);


    for(int i=0;i<n;i++){
        cout << arr[i] << " ";
    }
    return 0;

}
