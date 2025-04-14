//# include <stdio.h>
//# include <mpi.h>
//int main(int argc, char** argv)
//{
//	int rank, size;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	printf(" fuck off from process %d of %d\n", rank, size);
//	MPI_Finalize();
//	return 0;
//}

#include <stdio.h>
#include <mpi.h>
#include <bits/stdc++.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

void comp_and_swap(int a[], int i, int j, int dir) {
	if (dir == (a[i] > a[j]))
		swap(a[i], a[j]);
}

void bitonic_merge(int a[], int low, int cnt, int dir) {
	if (cnt > 1) {
		int k = cnt / 2;
		for (int i = low; i < low + k; i++) {
			comp_and_swap(a, i, i + k, dir);
		}
		bitonic_merge(a, low, k, dir);
		bitonic_merge(a, low + k, k, dir);
	}
}

void bitonic_sort(int a[], int low, int cnt, int dir) {
	if (cnt > 1) {
		int k = cnt / 2;
		bitonic_sort(a, low, k, 1);
		bitonic_sort(a, low + k, k, 0);
		bitonic_merge(a, low, cnt, dir);
	}
}

void sort(int a[], int N, int up) {
	bitonic_sort(a, 0, N, up);
}

int main(int argc, char** argv) {

	//int a[] = { 2, 5, 21, 54, 7, 9, 6, 4, 45, 6, 7, 74, 4, 3, 34 ,5 };
	//int number_of_elements = sizeof(a) / sizeof(a[0]);
	int* array;
	int array_size;
	int up = 1;
	int num_processes, process_rank;
	int j = 4096;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	array_size = j / num_processes;

	array = (int*)malloc(array_size * sizeof(int));

	srand(time(0));
	for (int i = 0; i < array_size; i++)
		array[i] = rand() % j;

	MPI_Barrier(MPI_COMM_WORLD);
	double timer_start = MPI_Wtime();

	sort(array, array_size, up);

	MPI_Barrier(MPI_COMM_WORLD);
	double timer_stop = MPI_Wtime();
	printf("sorted array: \n");

	for (int i = 0; i < 64; i++) {
		printf("%d ", array[i]);
	}
	printf("\nnow fuck off process %d of %d\n", process_rank, num_processes);
	printf("time: %f", timer_stop - timer_start);

	free(array);
	MPI_Finalize();
	return 0;
}