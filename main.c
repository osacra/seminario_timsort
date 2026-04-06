#include <stdio.h>


void insertionSort (int *v, int left, int right){

    int i = left +1;
    int j,aux;

    for(i; i <= right ; i++){
        aux = v[i];
        for(j = i; (j > left)&& (aux < v[j-1]); j--){
            v[j] = v[j-1];
        }
        v[j] = aux;
    }
}

void mergeSort (int *v, int start, int mid, int end){

    int n1 = mid - start +1;
    int n2 = end - mid;
    int left [n1];
    int right [n2];
    int i, j;
    int k = start;

    for(i = 0; i<n1; i++){
        left[i] = v [start + i];
     }

    for(j=0; j< n2; j++){
        right[j] = v[mid +1 +j];
    }

    i =0;
    j = 0;

    while(i < n1 && j < n2){

        if(left[i] < right[j]){
            v[k] = left [i];
            i++;
        }else{
            v[k] = right [j];
            j++;
        }
        k++;
    }

    while(i<n1){
        v[k] = left[i];
        i++;
        k++;
    }

    while(j<n2){
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
    return n+r;
}


void findRuns(int *v, int n){

    int i = 0;
    int minRun =calculateMinRun(n);

    while(i < n){

        int start = i;

        while(i < n-1 && v[i] <= v[i+1]){
            i++;
        }

        int end = i;

        int runSize = end - start + 1;

        if(runSize < minRun){

            int newEnd = start + minRun - 1;

            if(newEnd >= n)
                newEnd = n-1;

            insertionSort(v, start, newEnd);

            end = newEnd;
        }

        i = end + 1;
    }
}



int main(){



}
