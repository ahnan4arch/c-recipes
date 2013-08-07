// Given k sorted arrays of size n each, merge them and print
// the sorted output.
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
struct HeapNode {
    T data;
    size_t array_index;
    size_t current_pos;
    size_t next_pos;
    bool HeapNodeCompare(HeapNode<T>& other) const {
        return data < other.data;
    }
};

std::vector<int> MergeKSortedArray(const std::vector<std::vector<int> > arr)
{
    if (arr.empty()) return std::vector<int>();

    std::vector<int> sorted_array;
    size_t num_of_arrays = arr.size();
    std::vector<HeapNode<int> > aux_heap(num_of_arrays);

    for (int i = 0; i < num_of_arrays; i++) {
        HeapNode<int> node = {arr[i][0], i, 0, 1};
        aux_heap.push_back(node);
    }

    std::make_heap(aux_heap.begin(), aux_heap.end());

    while(true) {
        if (aux_heap.empty()) break;
        HeapNode<int> node = aux_heap[0];
        if (node.current_pos < arr[node.array_index].size() - 1) {
            sorted_array.push_back(node.data);

            // the last element in this array.
            if(node.next_pos == arr[node.array_index].size()) {
                std::pop_heap(aux_heap.begin(), aux_heap.end());
                aux_heap.erase(aux_heap.begin() + aux_heap.size() - 1);
                aux_heap.shrink_to_fit();
            } else {
                aux_heap[0].data = arr[node.array_index][node.next_pos];
                aux_heap[0].array_index = node.array_index;
                aux_heap[0].current_pos = node.next_pos;
                aux_heap[0].next_pos++;
            }
            std::make_heap(aux_heap.begin(), aux_heap.end());
        }
    }

    return sorted_array;
}

/*
 * ===  FUNCTION  =========================================================
 *         Name:  main
 *  Description:  program entry routine.
 * ========================================================================
 */
int main(int argc, const char *argv[])
{
    std::vector<std::vector<int> > arr = {{1, 2, 3}, {3, 4, 5, 6, 8}, {2, 4, 6, 8}};
    std::vector<int> sorted = MergeKSortedArray(arr);
    for_each(sorted.begin(), sorted.end(),
            [] (int i) {std::cout << i << "\t";});
    std::cout << std::endl;
    return EXIT_SUCCESS;
}  /* ----------  end of function main  ---------- */
