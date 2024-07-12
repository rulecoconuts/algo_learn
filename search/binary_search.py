from math import floor


def binary_search(arr: list, element) -> int:
    return binary_search_internal(arr, element, 0, len(arr) - 1)


def binary_search_internal(arr: list, element, start: int, end: int) -> int:
    n = end - start + 1

    if n == 1:
        return -1 if arr[start] != element else start
    left_end = start + int(floor(n / 2) - 1)

    if arr[left_end] == element:
        return left_end
    elif element < arr[left_end]:
        return binary_search_internal(arr, element, start, left_end)
    else:
        return binary_search_internal(arr, element, left_end + 1, end)
