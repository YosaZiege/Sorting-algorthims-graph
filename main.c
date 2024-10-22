#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(long int arr[],long int left,long int mid,long int right){
    long int i, j, k;
    long int n1 = mid - left + 1;
    long int n2 = right - mid;
    long int* L = (long int *) malloc(n1 * sizeof(long int));
    long int* R = (long int *) malloc(n2 * sizeof(long int));

    for (i = 0; i<n1; i++){
        L[i] = arr[left + i];
    }
    for (j = 0;j<n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i<n1 && j<n2){
        if (L[i]<=R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergesort(long int arr[], long int left, long int right){
    if (left < right){
        long int mid = left + (right - left)/2;
        mergesort(arr, left, mid);
        mergesort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }

}

void TriBulles(long int list[],int low, long int n)
{
    long int key;
    int swapped; // Indicateur pour vérifier s'il y a eu des échanges

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0; // Réinitialiser l'indicateur pour chaque itération

        for (int j = 0; j < n - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                // Échange
                key = list[j];
                list[j] = list[j + 1];
                list[j + 1] = key;

                swapped = 1; // Un échange a eu lieu
            }
        }

        // Si aucun échange n'a eu lieu, le tableau est déjà trié
        if (swapped == 0)
        {
            break;
        }
    }
}

void TriSelection(long int list[],int low, long int n)
{
    long int position, key;

    for (long int i = 0; i < n - 1; i++)
    {
        position = i;

        // Rechercher le minimum dans la sous-liste non triée
        for (long int j = i + 1; j < n; j++)
        {
            if (list[j] < list[position])
            {
                position = j;
            }
        }

        // Échanger l'élément trouvé avec le premier élément non trié
        if (position != i)
        {
            key = list[position];
            list[position] = list[i];
            list[i] = key;
        }
    }
}

void TriInsertion(long int list[],long int low ,long int n){
    for (long int i=0;i<n;i++){
        long int j = i-1;
        long int key = list[i];
        while (list[j] > key && j >=0){
            list[j+1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}
long int partition(long int list[], long int low, long int high){
    long int pivot = list[high];
    long int smallerIndex = low - 1;

    for (long int CurrentIndex = low;CurrentIndex< high; CurrentIndex++){
        if(list[CurrentIndex] <= pivot){
            smallerIndex++;
            long int key = list[smallerIndex];
            list[smallerIndex] = list[CurrentIndex];
            list[CurrentIndex] = key;
        }
    }

    long int temp = list[smallerIndex+1];
    list[smallerIndex+1] = list[high];
    list[high] = temp;
    return smallerIndex + 1;
}

void Quicksort(long int list[],long int low,long int high){
    if (low < high) {
        long int PivotIndex = partition(list, low, high);
        Quicksort(list, low, PivotIndex - 1);
        Quicksort(list, PivotIndex + 1, high);
    }
}

void printArray(long int arr[], long int size){
    for (long int i = 0; i<size; i++){
        printf(" %ld, ", arr[i]);
    }
    printf("\n");
}

void generateRandomArray(long int a[], long int size){

    for(long int i = 0; i < size;i++){
        a[i] = rand() * 10000;
    }

}

float get_time(void sort(long int arr[],long int low , long int high),long int n){
    float cpu_time;
    long int* arr = (long int *) malloc(n*sizeof(long int));

    generateRandomArray(arr , n);
    clock_t start , end;
    start = clock();
    sort(arr, 0, n - 1);
    end = clock();

    cpu_time = ((float ) (end - start)) / CLOCKS_PER_SEC;
    free(arr);
    return cpu_time;
}
int main(){
    FILE *pipeGnuplot = popen("gnuplot -p", "w");
   
    // Try to open the file in the same directory as your program
    FILE *fp = fopen("timing_data2.txt", "w");
    if (fp == NULL) {
        // If opening fails, print the error
        perror("Error opening file");
        return 1;
    }

    srand(time(NULL));


    printf("Starting timing measurements...\n");
    printf("Starting timing measurements...\n");
    fprintf(pipeGnuplot, "set title 'Sorts Complexity'\n");
    fprintf(pipeGnuplot, "set xlabel 'n'\n");
    fprintf(pipeGnuplot, "set ylabel 'Temp de machine'\n");
    /*fprintf(pipeGnuplot, "set logscale x\n");*/

    for (long int n = 0; n <= 1000; n += 200) {

        float cpu_time_2 = get_time(mergesort, n);
        float cpu_time_3 = get_time(Quicksort,  n);
        float cpu_time_4 = get_time(TriBulles,  n);
        float cpu_time_5 = get_time(TriSelection,  n);
        float cpu_time_6 = get_time(TriInsertion,  n);
        fprintf(fp, "%ld %lf %lf %lf %lf %lf\n", n, cpu_time_2, cpu_time_3, cpu_time_4, cpu_time_5, cpu_time_6);



        printf("Processed array of size %ld\n", n);


    }
    fprintf(pipeGnuplot, "plot 'timing_data2.txt' using 1:2 smooth bezier with lines title 'Merge', \\\n");
    fprintf(pipeGnuplot, "     'timing_data2.txt' using 1:3 smooth bezier with lines title 'Quick', \\\n");
    fprintf(pipeGnuplot, "     'timing_data2.txt' using 1:4 smooth bezier with lines title 'Bubble', \\\n");
    fprintf(pipeGnuplot, "     'timing_data2.txt' using 1:5 smooth bezier with lines title 'Selection', \\\n");
    fprintf(pipeGnuplot, "     'timing_data2.txt' using 1:6 smooth bezier with lines title 'Insertion'\n");

    fclose(fp);
    pclose(pipeGnuplot);

    return 0;
}