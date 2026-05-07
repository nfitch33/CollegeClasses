import random

def insertion_sort(arr):
    #In-place Insertion Sort
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        # Shift elements until correct position is found
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def quicksort(arr):
    #Randomized Quicksort: recursive, random pivot
    def _quicksort(low, high):
        if low < high:
            pivot_index = random.randint(low, high)
            arr[pivot_index], arr[high] = arr[high], arr[pivot_index]
            p = partition(low, high)
            _quicksort(low, p - 1)
            _quicksort(p + 1, high)

    def partition(low, high):
        pivot = arr[high]
        i = low
        for j in range(low, high):
            if arr[j] <= pivot:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1
        arr[i], arr[high] = arr[high], arr[i]
        return i


    _quicksort(0, len(arr) - 1)

def counting_sort(arr, k):
    """
    Stable Counting Sort implementation.
    Assumes arr contains integers in [0, k].
    Returns a new sorted array.
    """
    n = len(arr)
    count = [0] * (k + 1)
    output = [0] * n

    # Count occurrences
    for num in arr:
        count[num] += 1

    # Cumulative count (prefix sum)
    for i in range(1, k + 1):
        count[i] += count[i - 1]

    # Build output array (iterate backwards for stability)
    for i in range(n - 1, -1, -1):
        num = arr[i]
        count[num] -= 1
        output[count[num]] = num

    return output

