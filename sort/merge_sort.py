from math import floor


def merge_sort(arr: list):
    merge_sort_internal(arr, 0, len(arr) - 1)


def merge_sort_internal(arr: list, start: int, end: int):
    n = end - start + 1

    if n == 2:
        # order the 2
        if arr[start] > arr[end]:
            temp = arr[start]
            arr[start] = arr[end]
            arr[end] = temp
        return

    if n == 1:
        return
    left_end = start + int(floor(n / 2) - 1)

    # perform merge sort on left split
    merge_sort_internal(arr, start, left_end)

    # perform merge sort on right split
    merge_sort_internal(arr, left_end + 1, end)

    # merge
    merge(arr, start, left_end, end)


def merge(arr: list, start: int, left_end: int, end: int):
    left_section = [k for k in arr[start : left_end + 1]]
    right_section = [k for k in arr[left_end + 1 : end + 1]]

    left_index = 0
    right_index = 0
    max_left_index = left_end - start
    max_right_index = end - left_end - 1

    for i in range(start, end + 1):
        if (right_index > max_right_index) or (
            left_index <= max_left_index
            and left_section[left_index] <= right_section[right_index]
        ):
            arr[i] = left_section[left_index]
            left_index = left_index + 1
        else:
            arr[i] = right_section[right_index]
            right_index = right_index + 1
