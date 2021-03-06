
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <chrono>
#include <cmath>

#define sizeOfArray 25
#define sizeOfBigArray 100000

using namespace std;

void printArray(int * a, int size);
void merge(int arr[], int low, int high, int mid);
void mergesort(int arr[], int low, int high);
void insertionSort(int arr[], int n);
void radixSort(int arr[], int num_digits, int size);
void timeForEachSort(int * arr);
int main()
{	
	
	int * a = new int[sizeOfArray];
	for (unsigned i = 0, j = 10; i < sizeOfArray;)
		a[i++] = j++;
	
	random_shuffle(a, a + sizeOfArray); // Using srand, rand, time functions is very inefficient than this method
	cout << "Before merge sort" << endl;
	printArray(a, sizeOfArray);
	
	mergesort(a, 1, sizeOfArray);
	cout << "After merge sort" << endl;
	printArray(a, sizeOfArray);

	random_shuffle(a, a + sizeOfArray);
	cout << "Before insertion sort" << endl;
	printArray(a, sizeOfArray);

	insertionSort(a, sizeOfArray);
	cout << "After insertion sort" << endl;
	printArray(a, sizeOfArray);

	random_shuffle(a, a + sizeOfArray);
	cout << "Before radix sort" << endl;
	printArray(a, sizeOfArray);

	radixSort(a, 2, sizeOfArray);
	cout << "After radix sort" << endl;
	printArray(a, sizeOfArray);

	int * arr = new int[sizeOfBigArray];
	for (unsigned i = 0; i < sizeOfBigArray; i++)
		arr[i] = 123456 + i;

	timeForEachSort(arr);

	delete[] a;
	delete[] arr;
	return 0;
}
void timeForEachSort(int * arr) {
	
	random_shuffle(arr, arr + sizeOfBigArray);

	auto begin = chrono::high_resolution_clock::now();

	mergesort(arr, 1, sizeOfBigArray);

	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time for merge sort = " << ms << " milliseconds" << endl;

	random_shuffle(arr, arr + sizeOfBigArray);

	begin = chrono::high_resolution_clock::now();

	insertionSort(arr, sizeOfBigArray);

	end = chrono::high_resolution_clock::now();
	dur = end - begin;
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time for insertion sort = " << ms << " milliseconds" << endl;
	
	random_shuffle(arr, arr + sizeOfBigArray);

	begin = chrono::high_resolution_clock::now();

	radixSort(arr, 6, sizeOfBigArray);

	end = chrono::high_resolution_clock::now();
	dur = end - begin;
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time for radix sort = " << ms << " milliseconds" << endl;
}
void printArray(int * a, int size) {
	cout << "[ ";
	for (int i = 0; i < size; i++)
		cout << a[i] << " ";
	cout << "]" << endl;
}
void merge(int arr[], int low, int high, int mid) {

	int * temp1 = new int[mid - (low - 1)];
	int * temp2 = new int[high - mid];

	for(int i = (low - 1), j = 0; i < mid;)
		temp1[j++] = arr[i++];
	for (int i = mid, j = 0; i < high;)
		temp2[j++] = arr[i++];

	for (int i = 0, j = 0, k = low - 1; k < high; k++) {

		bool gone_through_temp1 = (i >= mid - (low - 1));
		bool gone_through_temp2 = (j >= (high - mid));

		if (!gone_through_temp1 && !gone_through_temp2)
			if (temp1[i] <= temp2[j])
				arr[k] = temp1[i++];
			else
				arr[k] = temp2[j++];

		else if (!gone_through_temp1)
			arr[k] = temp1[i++];// These are already sorted so we don't need to look for a minimum
		else if (!gone_through_temp2)
			arr[k] = temp2[j++];// Same as above

	}
	delete[] temp1;
	delete[] temp2;
}
void mergesort(int arr[], int low, int high) {
	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(arr, low, mid);
		mergesort(arr, mid + 1, high);
		merge(arr, low, high, mid);
	}
}
void insertionSort(int arr[], int n) {
	for (int i = 1; i < n; i++) {
		int elem = arr[i];
		int j = i;
		for (; j > 0 && elem < arr[j - 1]; j--)
			arr[j] = arr[j - 1];
		arr[j] = elem;
	}
}
void radixSort(int arr[], int num_digits, int size) {
	int maxNumDigits = num_digits;
	queue<int> *q = new queue<int>[10];

	while (num_digits != 0) {
		int divisor = (int)(pow(10, maxNumDigits - num_digits--));
		for (int i = 0; i < size; i++) {
			int zeroth_place = (arr[i] / divisor) % 10;
			q[zeroth_place].push(arr[i]);
		}
		for (int i = 0, j = 0; i < 10; i++)
			while (!q[i].empty()) {
				arr[j++] = q[i].front();
				q[i].pop();
			}
	}

	delete[] q;
}