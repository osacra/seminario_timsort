#include <stdio.h>

#define MAX 1000

void inverteArray(int *v, int start, int end);
void insertionSort (int *v, int left, int right);
void merge (int *v, int start, int mid, int end);
int calculateMinRun(int n);
void findRuns(int *v, int n);

int runStart[MAX];
int runLen[MAX];
int runCount = 0;


void insertionSort (int *v, int left, int right){

    int i = left + 1;
    int j,aux;

    for(i; i <= right ; i++){
        aux = v[i];

        for(j = i; (j > left) && (aux < v[j-1]); j--){
            v[j] = v[j-1];
        }

        v[j] = aux;
    }
}


void merge (int *v, int start, int mid, int end){

    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1];
    int right[n2];

    int i,j;
    int k = start;

    for(i = 0; i < n1; i++)
        left[i] = v[start + i];

    for(j = 0; j < n2; j++)
        right[j] = v[mid + 1 + j];

    i = 0;
    j = 0;

    while(i < n1 && j < n2){

        if(left[i] <= right[j]){
            v[k] = left[i];
            i++;
        }
        else{
            v[k] = right[j];
            j++;
        }

        k++;
    }

    while(i < n1){
        v[k] = left[i];
        i++;
        k++;
    }

    while(j < n2){
        v[k] = right[j];
        j++;
        k++;
    }
}


int calculateMinRun(int n){

    int r = 0;

    while(n >= 64){
        r |= n & 1;
        n >>= 1;
    }

    return n + r;
}


void inverteArray(int *v, int start, int end){

    int aux;

    while(start < end){

        aux = v[start];
        v[start] = v[end];
        v[end] = aux;

        start++;
        end--;
    }
}


void findRuns(int *v, int n){

    int end;
    int i = 0;

    int minRun = calculateMinRun(n);

    while(i < n){

        int start = i;

        if(i < n-1 && v[i] > v[i+1]){

            while(i < n-1 && v[i] > v[i+1])
                i++;

            end = i;

            inverteArray(v,start,end);
        }
        else{

            while(i < n-1 && v[i] <= v[i+1])
                i++;

            end = i;
        }

        int runSize = end - start + 1;

        if(runSize < minRun){

            int newEnd = start + minRun - 1;

            if(newEnd >= n)
                newEnd = n-1;

            insertionSort(v,start,newEnd);

            end = newEnd;
        }

        runStart[runCount] = start;
        runLen[runCount] = end - start + 1;
        runCount++;

        i = end + 1;
    }
}


void timSort(int *v, int n){

    findRuns(v,n);

    while(runCount > 1){

        int newCount = 0;

        for(int i = 0; i < runCount; i += 2){

            if(i == runCount-1){

                runStart[newCount] = runStart[i];
                runLen[newCount] = runLen[i];
                newCount++;
            }
            else{

                int start = runStart[i];
                int mid = start + runLen[i] - 1;
                int end = runStart[i+1] + runLen[i+1] - 1;

                merge(v,start,mid,end);

                runStart[newCount] = start;
                runLen[newCount] = runLen[i] + runLen[i+1];
                newCount++;
            }
        }

        runCount = newCount;
    }
}


int main(){

    int v[] = {9,8,7,6,5,4,3,2,1,10,11,12,0, 8, 76,51, 44,77,1,0,56,5,100};
    int n = sizeof(v)/sizeof(v[0]);

    timSort(v,n);

    for(int i=0;i<n;i++){
        printf("%d ",v[i]);
        }

    return 0;
}
