// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    
    int key, j;
    for(int i=1;i < data.size();i++){
        key = data[i];
        j = i-1;
        while(j >= 0 && data[j] > key){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
    //done
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    int middle;
    if (low < high){
        if (flag == 0){
            middle = Partition(data, low, high);
        }
        else{
            middle = RandomizedPartition(data, low, high);
        }
        QuickSortSubVector(data, low, middle, flag);
        QuickSortSubVector(data, middle+1, high, flag);
    }
    
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    
    int n = high-low+1;
    int x = data[rand()%n+low];
    int i= low, j = high;
    while(true){
        while (data[j] > x && j > low){
            j--;
        }
        while (data[i] < x && i < high){
            i++;
        }
        if (i < j){
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
        else{
            return j;
        }       
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x = data[low];
    int i = low, j = high;
    while(true){
        while (data[j] > x && j > low){
            j--;
            //std::cout<<"j = "<<j<<endl;

        }
        while (data[i] < x && i < high){
            i++;
            //std::cout<<"i = "<<i<<endl;

        }
        if (i < j){
            //std::cout<<"i = "<<i<<" , j = "<<j<<endl;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
        else{
            //std::cout<<"return j = "<<j<<endl;
            return j;
        }     
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
        int middle = floor((low+high)/2);
        MergeSortSubVector(data, low, middle);
        MergeSortSubVector(data, middle+1, high);
        Merge(data, low, middle, middle+1, high);
    }
    //done
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    vector<int> L_array(data.begin()+low, data.begin()+middle1+1);
    vector<int> R_array(data.begin()+middle2, data.begin()+high+1);
    // std::cout<<L_array.size()<<endl;
    // std::cout<<R_array.size()<<endl;
    // for (int i=0; i<L_array.size(); i++) {
        // std::cout<<L_array[i]<<' ';
    // }
    // std::cout<<endl;
    // for (int i=0; i<R_array.size(); i++) {
        // std::cout<<R_array[i]<<' ';
    // }
    int n1 = middle1 - low + 1;
    int n2 = high - middle2 + 1;
    int i = 0, j = 0;
    int k = low;
    while(i < n1 && j < n2){
        if(L_array[i] <= R_array[j]){
            data[k] = L_array[i];
            i++;
        }
        else{
            data[k] = R_array[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        data[k] = L_array[i];
        i++;
        k++;
    }
    while(j < n2){
        data[k] = R_array[j];
        j++;
        k++;
    }
    //done
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int L = 2*(root+1)-1;
    int R = 2*(root+1);
    int largest = root;
    if(L+1 <= heapSize && data[L] > data[largest]){
        largest = L;
    }    
    if(R+1 <= heapSize && data[R] > data[largest]){
        largest = R;
    }
    if(largest != root){
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data, largest);
    }
    // done
    
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    int i = floor(heapSize/2)-1;
    while (i >= 0){
        MaxHeapify(data, i);
        i--;
    }
    //done
}
