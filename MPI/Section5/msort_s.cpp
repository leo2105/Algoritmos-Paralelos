#include <iostream>
using namespace std;

void merge(int a[], int startIndex, int endIndex)
{
int size = (endIndex - startIndex) + 1;
int *b = new int [size]();
int i = startIndex;
int mid = (startIndex + endIndex)/2;
int k = 0;
int j = mid + 1;

while (k < size)
{   
    if((i<=mid) && (a[i] < a[j]))
        {
        b[k++] = a[i++];
    }
    else
    {
        b[k++] = a[j++];
     }
}

for(k=0; k < size; k++)
{
    a[startIndex+k] = b[k];
}
delete []b;
}



void merge_sort(int iArray[], int startIndex, int endIndex)
{
	int midIndex;

//Check for base case
if (startIndex >= endIndex)
{
   return;
  }   

//First, divide in half
midIndex = (startIndex + endIndex)/2;

//First recursive call 
merge_sort(iArray, startIndex, midIndex);

//Second recursive call 
merge_sort(iArray, midIndex+1, endIndex);
	
 //The merge function
 merge(iArray, startIndex, endIndex);

  }

//The main function
int main(int argc, char *argv[])
{
int iArray[10] = {26,57,60,82,7,24,12,67,64,156};

merge_sort(iArray, 0, 9);

//Print the sorted array
for(int i=0; i < 10; i++)
{
    cout << iArray[i] << endl;
    }

    return 0;    
    }
