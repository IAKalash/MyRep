#include <stdio.h>
#include <malloc.h>

void MergeSort(int *arr, int len)
{
    if (len == 1)
        return;
    
    MergeSort(arr, len / 2);
    MergeSort(&arr[len / 2], len - len / 2);

    int left = 0;
    int right = 0;
    int *tmp = (int *)malloc(4 * len);

    for (int i = 0; i < len; i++)
    {
        if (arr[left] < arr[len / 2 + right])
            tmp[i] = arr[left++];
        else
            tmp[i] = arr[len / 2 + right++];

        if (left == len / 2)
        { 
            while (right < len - len / 2)
                tmp[++i] = arr[len / 2 + right++];
            break;
        }
        else if (right == len - len / 2)
        { 
            while (left < len / 2)
                tmp[++i] = arr[left++];
            break;
        }
    }

    for (int i = 0; i < len; i++)
        arr[i] = tmp[i];
    free(tmp);
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, m;

    fread(&n, 4, 1, in);

    int *arr = (int *)malloc(4 * n);

    for (int i = 0; i < n; ++i)
    {
        fread(&arr[i], 4, 1, in);
    }

    MergeSort(arr, n);

    for (int i = 0; i < n; ++i)
    {
        fwrite(&arr[i], 4, 1, out);
    }

    free(arr);

    fclose(in);
    fclose(out);
}