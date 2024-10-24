#include <iostream>
#include <vector>

// Function to perform bubble sort
void bubbleSort(std::vector<int> &arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        // Swap the elements
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

// Function to print the array
void printArray(const std::vector<int> &arr) {
  for (int i : arr) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {
  int n;
  std::cout << "Enter the number of elements: ";
  std::cin >> n;

  std::vector<int> arr(n);
  std::cout << "Enter " << n << " integers:" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  std::cout << "Unsorted array: ";
  printArray(arr);

  bubbleSort(arr);

  std::cout << "Sorted array: ";
  printArray(arr);

  return 0;
}
