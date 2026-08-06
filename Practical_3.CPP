#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

//------------------ RECURSIVE MAX HEAPIFY ------------------//
void maxHeapifyRecursive(vector<int> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeapifyRecursive(arr, n, largest);   // recursive call
    }
}

void heapSortRecursive(vector<int> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapifyRecursive(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapifyRecursive(arr, i, 0);
    }
}

//------------------ ITERATIVE MAX HEAPIFY ------------------//
void maxHeapifyIterative(vector<int> &arr, int n, int i)
{
    while (true)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest == i)
            break;               // no more swaps needed -> stop

        swap(arr[i], arr[largest]);
        i = largest;             // move down the tree (loop instead of recursive call)
    }
}

void heapSortIterative(vector<int> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapifyIterative(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapifyIterative(arr, i, 0);
    }
}

//------------------ HELPER ------------------//
void printArray(const vector<int> &arr, int limit = 20)
{
    int n = min((int)arr.size(), limit);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    if ((int)arr.size() > limit)
        cout << "... (" << arr.size() - limit << " more)";
    cout << endl;
}

//------------------ MAIN ------------------//
int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);
    srand(time(0));
    for (int i = 0; i < n; i++)
        original[i] = rand() % 100000;

    vector<int> arrRecursive = original;
    vector<int> arrIterative = original;

    //---------------- RECURSIVE HEAP SORT ----------------//
    auto startRec = high_resolution_clock::now();
    heapSortRecursive(arrRecursive);
    auto endRec = high_resolution_clock::now();

    //---------------- ITERATIVE HEAP SORT ----------------//
    auto startIter = high_resolution_clock::now();
    heapSortIterative(arrIterative);
    auto endIter = high_resolution_clock::now();

    //---------------- VERIFY CORRECTNESS ----------------//
    bool same = (arrRecursive == arrIterative);

    //---------------- DISPLAY TIME ----------------//
    auto nanoRec  = duration_cast<nanoseconds>(endRec - startRec);
    auto microRec = duration_cast<microseconds>(endRec - startRec);
    duration<double> secRec = endRec - startRec;

    auto nanoIter  = duration_cast<nanoseconds>(endIter - startIter);
    auto microIter = duration_cast<microseconds>(endIter - startIter);
    duration<double> secIter = endIter - startIter;

    cout << "\nSorted (Recursive) first 20: ";
    printArray(arrRecursive);
    cout << "Sorted (Iterative) first 20: ";
    printArray(arrIterative);

    cout << "\nBoth results match: " << (same ? "YES" : "NO") << "\n";

    cout << "\n========== RECURSIVE HEAPIFY - HEAP SORT ==========\n";
    cout << "Nanoseconds  : " << nanoRec.count() << " ns\n";
    cout << "Microseconds : " << microRec.count() << " us\n";
    cout << "Seconds      : " << secRec.count() << " s\n";

    cout << "\n========== ITERATIVE HEAPIFY - HEAP SORT ==========\n";
    cout << "Nanoseconds  : " << nanoIter.count() << " ns\n";
    cout << "Microseconds : " << microIter.count() << " us\n";
    cout << "Seconds      : " << secIter.count() << " s\n";

    return 0;
}
