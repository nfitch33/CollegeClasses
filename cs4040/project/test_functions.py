from sort_algorithms import insertion_sort, quicksort, counting_sort

def TestMe_InsertionSort(arr):
    print("=== Insertion Sort Test ===")
    print("Original array:")
    print(arr)
    arr_copy = arr.copy()
    insertion_sort(arr_copy)
    print("Sorted array (Insertion Sort):")
    print(arr_copy)
    assert arr_copy == sorted(arr), "Insertion Sort failed!"
    print("Insertion Sort passed.\n")

def TestMe_Quicksort(arr):
    print("=== Quicksort Test ===")
    print("Original array:")
    print(arr)
    arr_copy = arr.copy()
    quicksort(arr_copy)
    print("Sorted array (Quicksort):")
    print(arr_copy)
    assert arr_copy == sorted(arr), "Quicksort failed!"
    print("Quicksort passed.\n")

def TestMe_CountingSort(arr, k):
    print("=== Counting Sort Test ===")
    print("Original array:")
    print(arr)
    arr_copy = arr.copy()
    counting_sort(arr_copy, k)
    print("Sorted array (Counting Sort):")
    print(arr_copy)
    assert arr_copy == sorted(arr), "Counting Sort failed!"
    print("Counting Sort passed.\n")


if __name__ == "__main__":
    test_array = [9, 5, 2, 7, 1, 3]
    
    TestMe_InsertionSort(test_array)
    TestMe_Quicksort(test_array)
    k = max(test_array)
    TestMe_CountingSort(test_array, k)
