from sort.merge_sort import merge_sort
from search.binary_search import binary_search

arr = [3, 4, 1, 7, 33, 6, 22, 22, 1, 7, 0]
print(arr)
merge_sort(arr)
print(arr)

print(binary_search(arr, 22))
