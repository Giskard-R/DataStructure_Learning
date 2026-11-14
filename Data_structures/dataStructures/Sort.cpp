#include <vector>

void insertSort(std::vector<int>& arr)
{
	int n = arr.size();
	for (int i = 1; i < n; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

void binaryInsertSort(std::vector<int>& arr)
{
	int n = arr.size();

	for (int i = 1; i < n; i++)
	{
		int temp = arr[i];
		int left = 0;
		int right = i - 1;

		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (arr[mid] > temp)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}

		for (int j = i - 1; j >= left; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[left] = temp;
	}
}

void shellSort(std::vector<int>& arr)
{
	int n = arr.size();

	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap;i < n; i++)
		{
			int temp = arr[i];
			int j;
			for (j = i;j >= gap && arr[j - gap] > temp;j -= gap)
			{
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

void bubbleSort(std::vector<int>& arr)
{
	int n = arr.size();

	for (int i = 0; i < n - 1; i++)
	{
		bool flag = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int t = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = t;
				flag = true;
			}
		}
		if (!flag)
			break;
	}
}

int partition(std::vector<int>& arr, int left, int right)
{
	int pivot = arr[left];
	while (left < right)
	{
		while (left < right && arr[right] >= pivot)
			right--;
		arr[left] = arr[right];

		while (left < right && arr[left] <= pivot)
			left++;
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	return left;
}

void quickSort(std::vector<int>& arr, int l, int r)
{
	if (l >= r)
		return;
	int pos = partition(arr, l, r);
	quickSort(arr, l, pos - 1);
	quickSort(arr, pos + 1, r);
}

void quickSort(std::vector<int>& arr)
{
	quickSort(arr, 0, arr.size() - 1);
}

void selectSort(std::vector<int>& arr)
{
	int n = arr.size();
	for (int i = 0; i < n - 1; i++)
	{
		int minIdx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[minIdx])
				minIdx = j;
		}
		if (minIdx != i)
			std::swap(arr[i], arr[minIdx]);
	}
}

void heapAdjust(std::vector<int>& arr, int i, int len)
{
	int temp = arr[i];

	for (int k = 2 * i + 1; k < len; k = 2 * k + 1)
	{
		if (k + 1 < len && arr[k + 1] > arr[k])
			k++;
		if (arr[k] > temp)
		{
			arr[i] = arr[k];
			i = k;
		}
		else
			break;
	}
	arr[i] = temp;
}

void heapSort(std::vector<int>& arr)
{
	int n = arr.size();
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapAdjust(arr, i, n);
	}
	for (int i = n - 1;i > 0;i--)
	{
		std::swap(arr[0], arr[i]);
		heapAdjust(arr, 0, i);
	}
}

void merge(std::vector<int>& arr, std::vector<int>& tmp, int l, int mid,int r)
{
	int i = l;
	int j = mid + 1;
	int k = l;

	while (i <= mid && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			tmp[k++] = arr[i++];
		}
		else
		{
			tmp[k++] = arr[j++];
		}
	}
	while (i <= mid)
		tmp[k++] = arr[i++];
	while (j <= r)
		tmp[k++] = arr[j++];
	for (int p = l;p <= r;p++)
	{
		arr[p] = tmp[p];
	}
}

void mergeSort(std::vector<int>& arr, std::vector<int>& tmp, int l, int r)
{
	if (l >= r)
		return;
	int mid = l + (r - l) / 2;
	mergeSort(arr, tmp, l, mid);
	mergeSort(arr, tmp, mid + 1, r);
	merge(arr, tmp, l, mid, r);
}

void mergeSort(std::vector<int>& arr)
{
	std::vector<int> tmp(arr.size());
	mergeSort(arr, tmp, 0, arr.size() - 1);
}

void countSort(std::vector<int>& arr, int digit)
{
	int n = arr.size();
	std::vector<int> output(n);
	int cnt[10] = { 0 };

	for (int x : arr)
	{
		int num = (x / digit) % 10;
		cnt[num]++;
	}
	for (int i = 1; i < 10; i++)
		cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--)
	{
		int num = (arr[i] / digit) % 10;
		output[cnt[num] - 1] = arr[i];
		cnt[num]--;
	}
	for (int i = 0; i < n; i++)
		arr[i] = output[i];
}

void redixSort(std::vector<int>& arr)
{
	if (arr.empty())
		return;
	int maxVal = *std::max_element(arr.begin(), arr.end());
	for (int digit = 1;maxVal / digit > 0;digit *= 10)
		countSort(arr, digit);
}


