#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef high_resolution_clock Time;
typedef time_point<Time> TimePoint;
typedef microseconds us;

void PrintArray(int* array, int n) {
	for (int i = 0; i < n && i < 25; i++)
		cout << setw(5) << array[i] << " ";

	if (n > 25)
		cout << "... " << array[n - 1];

	cout << endl;
}

void GenerateArray(int* array, int n, int a, int b) {
	for (int i = 0; i < n; i++)
		array[i] = a + rand() % (b - a + 1);
}

int Search(int* array, int n, int value) {
	for (int i = 0; i < n; i++)
		if (array[i] == value)
			return i;

	return -1;
}

void QuickSort(int *array, int first, int last) {
	if (last <= first)
		return;

	int left = first;
	int right = last;
	int middle = array[(last + first) / 2];

	while (left <= right) {
		while (array[left] < middle)
			left++;

		while (array[right] > middle)
			right--;

		if (left <= right) {
			int tmp = array[left];
			array[left] = array[right];
			array[right] = tmp;
			left++;
			right--;
		}
	}

	QuickSort(array, first, right);
	QuickSort(array, left, last);
}

int BSearch(int* array, int left, int right, int value) {
	if (value < array[left] || value > array[right] || right <= left)
		return -1;

	int first = 0;
	int last = right + 1;

	while (first < last) {
		int mid = first + (last - first) / 2;

		if (value <= array[mid]) {
			last = mid;
		}
		else {
			first = mid + 1;
		}
	}

	return array[last] == value ? last : -1;
}

int BSearchRecursive(int* array, int left, int right, int value) {
	if (value < array[left] || value > array[right] || right <= left)
		return -1;

	int mid = left + (right - left) / 2;

	if (value == array[mid])
		return mid;

	if (value < array[mid]) {
		return BSearchRecursive(array, left, mid - 1, value);
	}
	else { // иначе
		return BSearchRecursive(array, mid + 1, right, value);
	}
}

int main() {
	int n;
	cout << "Enter n: ";
	cin >> n;

	int *array1 = new int[n];
	int *array2 = new int[n];

	GenerateArray(array1, n, -1000, 1000);
	GenerateArray(array2, n, -1000, 1000);

	cout << "Created array1: ";
	PrintArray(array1, n);
	cout << "Created array2: ";
	PrintArray(array2, n);

	QuickSort(array2, 0, n - 1);

	cout << " Sorted array2: ";
	PrintArray(array2, n);

	int value;
	cout << "Enter value for find: ";
	cin >> value;

	int index1 = Search(array1, n, value);
	int index2 = BSearchRecursive(array2, 0, n - 1, value);

	cout << "Index at first array: " << index1 << endl;
	cout << "Index at second array: " << index2 << endl;

	TimePoint t0 = Time::now();
	for (int i = 0; i < n; i++)
		Search(array1, n, array1[i]);
	TimePoint t1 = Time::now();
	for (int i = 0; i < n; i++)
		BSearchRecursive(array2, 0, n - 1, array2[i]);
	TimePoint t2 = Time::now();

	us dt1 = duration_cast<us>(t1 - t0);
	us dt2 = duration_cast<us>(t2 - t1);

	cout << "Average 'Search' time: " << dt1.count() * 1.0 / n << " us" << endl;
	cout << "Average 'BSearch' time: " << dt2.count() * 1.0 / n << " us" << endl;

	delete[] array1;
	delete[] array2;
}
