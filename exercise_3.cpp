#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;


void insertion_sort(int val[], int ARR_SZ) {
    if (ARR_SZ == 0 || ARR_SZ == 1) {
        return;
    }

    unsigned int k = 0;
    int temp = 0;
    for (unsigned i = 1; i < ARR_SZ; i++) {
        k = i;
        while (k > 0 && (val[k] < val[k - 1])) {
            temp = val[k];
            val[k] = val[k - 1];
            val[k - 1] = temp;
            k--;
        }
    }
}

int partition(int val[], int i, int k) {
    int temp = 0;
    bool fin = false;
    int low = i;
    int maxLow = k;
    int midpoint = i + (k - i) / 2;
    int pivot = val[midpoint];

    while (!fin) {
        while (val[low] < pivot) {
            ++low;
        }
        while (pivot < val[maxLow]) {
            --maxLow;
        }

        if (low >= maxLow) {
            fin = true;
        }
        else {
            temp = val[low];
            val[low] = val[maxLow];
            val[maxLow] = temp;
            ++low;
            --maxLow;
        }
    }

    return maxLow;
}

void quick_sort(int val[], int i, int k) {
    int j = 0;
    if (i >= k) {
        return;
    }

    j = partition(val, i, k);
    quick_sort(val, i, j);
    quick_sort(val, j + 1, k);

}


void merge(int val[], int i, int j, int k) {
    int newSize = k - i + 1;
    int mPos = 0;
    int *merged = new int[newSize];
    int lPos = i;
    int  rPos = j + 1;

    while (lPos <= j && rPos <= k) {
        if (val[lPos] <= val[rPos]) {
            merged[mPos] = val[lPos];
            lPos++;
        }
    else {
        merged[mPos] = val[rPos];
        rPos++;

        }
     mPos++;

    }

    while (lPos <= j) {
        merged[mPos] = val[lPos];
        lPos++;
        mPos++;
    }

    while (rPos <= k) {
        merged[mPos] = val[rPos];
        ++rPos;
        ++mPos;
    }

    for (mPos = 0; mPos < newSize; mPos++) {
        val[i + mPos] = merged[mPos];
    }

}

void merge_sort(int val[], int i, int k) {
    int j = 0;
    if (i < k) {
        j = (i + k) / 2;
        merge_sort(val, i, j);
        merge_sort(val, j + 1, k);
        merge(val, i, j, k);
    }
}

void MaxHeapPercolateDown(int index, int vals[], int size) {
    int cIndex = 2 * index + 1;
    int value = vals[index];
    int maxVal, maxIndex, temp = 0;
    while (cIndex < size) {
        maxVal = value;
        maxIndex = -1;

        for (int i = 0; (i < 2) && (i + cIndex < size); i++) {
            if (vals[i + cIndex] > maxVal) {
                maxVal = vals[i + cIndex];
                maxIndex = i + cIndex;
            }
        }

        if (maxVal == value) {
            return;
        }
        else {
            temp = vals[index];
            vals[index] = vals[maxIndex];
            vals[maxIndex] = temp;
            index = maxIndex;
            cIndex = 2 * index + 1;
        }
    }

}

void heapsort(int val[], int ARR_SZ) {
    int size = ARR_SZ;
    for (int i = size / 2 - 1; i >= 0; i--) {
        MaxHeapPercolateDown(i, val, size);
    }

    for (int i = size - 1; i > 0; i--) {
        int temp = val[0];
        val[0] = val[i];
        val[i] = temp;
         MaxHeapPercolateDown(0, val, i);
    }

}


void calculateAverageTime(int val[], int size, double averages[]) {
    long long totalTime = 0;
    for (unsigned i = 0; i < 30; i++) {
        for (unsigned j = 0; j < size; j++) {
            val[i] = (rand() % (size + 1));
        }

        auto start = std::chrono::high_resolution_clock::now();
        heapsort(val, size);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        totalTime += elapsed.count();

    }
    averages[0] = (totalTime / 30.0);

    totalTime = 0;
    for (unsigned i = 0; i < 30; i++) {
        for (unsigned j = 0; j < size; j++) {
            val[i] = (rand() % (size + 1));
        }

        auto start = std::chrono::high_resolution_clock::now();
        quick_sort(val, 0, (size - 1));
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        totalTime += elapsed.count();
    }
    averages[1] = (totalTime / 30.0);

    totalTime = 0;
    for (unsigned i = 0; i < 30; i++) {
        for (unsigned j = 0; j < size; j++) {
            val[i] = (rand() % (size + 1));
        }

        auto start = std::chrono::high_resolution_clock::now();
        insertion_sort(val, size);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        totalTime += elapsed.count();
    }
    averages[2] = (totalTime / 30.0);

    totalTime = 0;
    for (unsigned i = 0; i < 30; i++) {
        for (unsigned j = 0; j < size; j++) {
            val[i] = (rand() % (size + 1));
        }
        auto start = std::chrono::high_resolution_clock::now();
        merge_sort(val, 0, (size - 1));
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        totalTime += elapsed.count();
    }

    averages[3] = (totalTime / 30.0);


}



int main() {
    srand(time(0));
    int ten[10];
    ofstream outFS;
    double *average;
    int oneHundred[100];
    int oneThousand[1000];
    int tenThousand[10000];
    int oneHundredThousand[100000];
    int oneMillion[1000000];
    double averages[4];

    outFS.open("output.txt");
    if (!outFS.is_open()) {
        cout << "error" << endl;
        return 1;
    }

    outFS << "SIZE | " << "HEAPSORT   | " << "QUICKSORT | " << "INSERTION SORT |  " << "MERGE SORT | " << endl;

    calculateAverageTime(ten, 10, averages);
    outFS << "10     |" << averages[0] << "| " << averages[1] << "| " << averages[2] << "| " << averages[3] << endl;

    calculateAverageTime(oneHundred, 100, averages);
    outFS << "100    |" << averages[0] << "| " << averages[1] << "| " << averages[2] << "| " << averages[3] << endl;

    calculateAverageTime(oneThousand, 1000, averages);
    outFS << "1000   |" << averages[0] << "| " << averages[1] << "| " << averages[2] << "| " << averages[3] << endl;
    calculateAverageTime(tenThousand, 10000, averages);
    outFS << "10000  |" << averages[0] << "| " << averages[1] << "| " << averages[2] << "| " << averages[3] << endl;
    calculateAverageTime(oneHundredThousand, 100000, averages);
    outFS << "100000 |" << averages[0] << "| " << averages[1] << "| " << averages[2] << "| " << averages[3] << endl;
    calculateAverageTime(oneMillion, 1000000, averages);
    outFS << "1000000|" << averages[0] << "| " << averages[1] << "| " << averages[2] << "| " << averages[3] << endl;

    cout << "file has been closed." << endl;
    outFS.close();

    return 0;

}