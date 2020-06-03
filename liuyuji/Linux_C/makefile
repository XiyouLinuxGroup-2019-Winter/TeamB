QuickSort.o:QuickSort.c threadpool_QuickSort.h
	gcc -c QuickSort.c -o QuickSort.o
threadpool.o:threadpool.c threadpool_QuickSort.h
	gcc -c threadpool.c -o threadpool.o
threadpool_QuickSort:QuickSort.o threadpool.o
	gcc QuickSort.o threadpool.o -o threadpool_QuickSort
1:QuickSort.O threadpool.o
	gcc -g QuickSort.o threadpool.o -o 1
