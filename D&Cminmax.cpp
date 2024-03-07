#include <iostream>
#include <vector>

using namespace std;

void findMinAndMax(vector<int> const &arr, int low, int high, int &min, int &max)
{
    if (low == high)
    {
        if (max < arr[low])
        {
            max = arr[low];
        }
        if (min > arr[high])
        {
            min = arr[high];
        }
        return;
    }
    else if (high - low == 1)
    {
        if (arr[low] < arr[high])
        {
            if (min > arr[low])
            {
                min = arr[low];
            }
            if (max < arr[high])
            {
                max = arr[high];
            }
        }
        else
        {
            if (min > arr[high])
            {
                min = arr[high];
            }

            if (max < arr[low])
            {
                max = arr[low];
            }
        }
        return;
    }

    int mid = (low + high) / 2;

    findMinAndMax(arr, low, mid, min, max);

    findMinAndMax(arr, mid + 1, high, min, max);
}

int main()
{

    vector<int> arr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        arr.push_back(temp);
    }
    int min = arr.front();
    int max = arr.front();
    findMinAndMax(arr, 0, n - 1, min, max);
    cout << min << endl
         << max << endl;
    return 0;
}