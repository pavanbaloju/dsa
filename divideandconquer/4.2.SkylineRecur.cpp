// Problem Statement:
// Given a set of buildings, represented by their left and right x coordinates along with their heights,
// find the skyline formed by these buildings. The skyline is the outline formed by all the buildings
// when viewed from a distance.

// Intuition:
// To find the skyline, we divide the problem into smaller subproblems using a divide and conquer approach.
// We recursively find the skyline of the left half and the right half of the buildings and then merge them.
// Merging involves comparing the heights of the skylines at each x coordinate and selecting the maximum height
// for the resulting skyline.

// DSA Strategy:
// We use a divide and conquer strategy to solve this problem. We recursively find the skyline of the left half
// and the right half of the buildings. Then, we merge the skylines by comparing their heights at each x coordinate.

// Approach:
// 1. Define structures to represent buildings and strips in the skyline.
// 2. Implement a function to find the skyline recursively using divide and conquer.
// 3. Implement a merge function to merge two skylines.
// 4. Create a driver function to input the buildings, find the skyline, and print the result.

// Time Complexity:
// The time complexity of finding the skyline using the divide and conquer approach is O(n log n), where n is
// the number of buildings.

// Space Complexity:
// The space complexity is O(n log n) due to the recursive calls and the space required for storing the skylines.

// Code with Comments:

#include <iostream>
using namespace std;

// A structure for building
struct Building {
    // x coordinate of left side
    int left;

    // height
    int height;

    // x coordinate of right side
    int right;
};

// A strip in skyline
class Strip {
    // x coordinate of left side
    int left;

    // height
    int height;

public:
    // Constructor
    Strip(int l = 0, int h = 0) {
        left = l;
        height = h;
    }

    // Declare SkyLine class as a friend
    friend class SkyLine;
};

// Skyline: To represent Output(An array of strips)
class SkyLine {
    // Array of strips
    Strip *arr;

    // Capacity of strip array
    int capacity;

    // Actual number of strips in array
    int n;

public:
    // Destructor
    ~SkyLine() { delete[] arr; }

    // Function to get the count of strips
    int count() { return n; }

    // A function to merge another skyline to this skyline
    SkyLine *Merge(SkyLine *other);

    // Constructor
    SkyLine(int cap) {
        capacity = cap;
        arr = new Strip[cap];
        n = 0;
    }

    // Function to add a strip 'st' to array
    void append(Strip *st) {
        // Check for redundant strip
        if (n > 0 && arr[n - 1].height == st->height)
            return;
        if (n > 0 && arr[n - 1].left == st->left) {
            arr[n - 1].height = max(arr[n - 1].height, st->height);
            return;
        }

        arr[n] = *st;
        n++;
    }

    // A utility function to print all strips of skyline
    void print() {
        for (int i = 0; i < n; i++) {
            cout << " (" << arr[i].left << ", " << arr[i].height << "), ";
        }
    }
};

// This function returns skyline for a given array of buildings arr[l..h].
// This function is similar to mergeSort().
SkyLine *findSkyline(Building arr[], int l, int h) {
    if (l == h) {
        SkyLine *res = new SkyLine(2);
        res->append(new Strip(arr[l].left, arr[l].height));
        res->append(new Strip(arr[l].right, 0));
        return res;
    }

    int mid = (l + h) / 2;

    // Recur for left and right halves and merge the two results
    SkyLine *sl = findSkyline(arr, l, mid);
    SkyLine *sr = findSkyline(arr, mid + 1, h);
    SkyLine *res = sl->Merge(sr);

    // To avoid memory leak
    delete sl;
    delete sr;

    // Return merged skyline
    return res;
}

// Similar to merge() in MergeSort
// This function merges another skyline 'other' to the skyline for which it is called.
// The function returns pointer to the resultant skyline
SkyLine *SkyLine::Merge(SkyLine *other) {
    // Create a resultant skyline with capacity as sum of two skylines
    SkyLine *res = new SkyLine(this->n + other->n);

    // To store current heights of two skylines
    int h1 = 0, h2 = 0;

    // Indexes of strips in two skylines
    int i = 0, j = 0;
    while (i < this->n && j < other->n) {
        // Compare x coordinates of left sides of two skylines and put the smaller one in result
        if (this->arr[i].left < other->arr[j].left) {
            int x1 = this->arr[i].left;
            h1 = this->arr[i].height;

            // Choose height as max of two heights
            int maxh = max(h1, h2);

            res->append(new Strip(x1, maxh));
            i++;
        } else {
            int x2 = other->arr[j].left;
            h2 = other->arr[j].height;
            int maxh = max(h1, h2);
            res->append(new Strip(x2, maxh));
            j++;
        }
    }

    // If there are strips left in this skyline or other skyline
    while (i < this->n) {
        res->append(&arr[i]);
        i++;
    }
    while (j < other->n) {
        res->append(&other->arr[j]);
        j++;
    }
    return res;
}

// Driver Function
int main() {
    Building arr[] = {{1, 11, 5}, {2, 6, 7}, {3, 13, 9}, {12, 7, 16}, {14, 3, 25}, {19, 18, 22}, {23, 13, 29}, {24, 4, 28}};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Find skyline for given buildings and print the skyline
    SkyLine *ptr = findSkyline(arr, 0, n - 1);
    cout << " Skyline for given buildings is \n";
    ptr->print();
    return 0;
}
