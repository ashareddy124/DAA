#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// Bubble Sort
void bubbleSort(vector<int> &a)
{
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        }
    }
}

// Selection Sort
void selectionSort(vector<int> &a)
{
    int n = a.size();

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIndex])
                minIndex = j;
        }

        swap(a[i], a[minIndex]);
    }
}

// Insertion Sort
void insertionSort(vector<int> &a)
{
    int n = a.size();

    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Merge Function
void merge(vector<int> &a, int left, int mid, int right)
{
    vector<int> temp;
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    while (i <= mid)
        temp.push_back(a[i++]);

    while (j <= right)
        temp.push_back(a[j++]);

    for (int k = 0; k < temp.size(); k++)
        a[left + k] = temp[k];
}

// Merge Sort
void mergeSort(vector<int> &a, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

// Partition Function
int partition(vector<int> &a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

// Quick Sort
void quickSort(vector<int> &a, int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n = 100;
    vector<int> arr(n), temp;

    srand(time(0));

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    cout << "Number of Elements: " << n << endl << endl;

    auto start = high_resolution_clock::now();
    temp = arr;
    bubbleSort(temp);
    auto end = high_resolution_clock::now();
    cout << "Bubble Sort    : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    temp = arr;
    selectionSort(temp);
    end = high_resolution_clock::now();
    cout << "Selection Sort : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    temp = arr;
    insertionSort(temp);
    end = high_resolution_clock::now();
    cout << "Insertion Sort : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    temp = arr;
    mergeSort(temp, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "Merge Sort     : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    temp = arr;
    quickSort(temp, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "Quick Sort     : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    return 0;
}
