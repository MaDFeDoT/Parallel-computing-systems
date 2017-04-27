//QuickSort - реализация алгоритма быстрой сортировки
//@param a sort array
//@param n index the last of array elements
#include <iostream>
#include <fstream>
#include <ctime>
#include "mpi.h"
using namespace std;

template <typename T>
void quickSort(T* a, const long n, int level) {
  int ProcNum, ProcRank, RecvRank;
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  long i = 0, j = n;
  T pivot = a[n / 2]; // pivot element
  do {
    while (a[i] < pivot) i++;
    while (a[j] > pivot) j--;
    if (i <= j) {
      std::swap(a[i], a[j]);
      i++; j--;
    }
  } while (i <= j);
  if ( ProcRank == 1 && level==0){
	if (j > 0) quickSort(a, j, level+1);
  }
  else if(ProcRank == 1 && level>0){
	  if (j > 0) quickSort(a, j, level+1);
	  if (n > i) quickSort(a + i, n - i, level+1);
  }
  if ( ProcRank == 2 && level==0){
	if (n > i) quickSort(a + i, n - i, level+1);
  }
  else if(ProcRank == 2 && level>0){
	  if (j > 0) quickSort(a, j, level+1);
	  if (n > i) quickSort(a + i, n - i, level+1);
  }
}

int main(int argc, char* argv[]){
	MPI_Status Status;
    MPI_Init(&argc, &argv);
	int ProcNum, ProcRank, RecvRank;
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	if ( 1 ){
	cout<<"Enter size of array: ";
	char buf;
	cin>>buf;
	int size;
	cin>>size;
	int * a=new int[size];
	int first_value=0;
	int last_value=10000;
	int format_out=10;
	int elements_in_row=10;
	//Text file for results
	ofstream fout("results.txt");
	fout<<"********************\tArray:"<<endl<<endl;
	for(int i=0; i<size; i++)
	{	
		a[i]=first_value+rand()%last_value;
		fout.width(format_out);
		fout.setf(ios::left);
		if(i%elements_in_row==0 && i!=0) fout<<endl;
		fout<<a[i]<<"\t\t";
	}

	//Start quick sorting array
	cout<<endl<<"Start sorting array (Quick sort)"<<endl;
	unsigned int start_time =  clock(); // start time
    quickSort(a, size-1, 0);
    unsigned int end_time = clock(); // finish time
    unsigned int search_time = end_time - start_time; // execution time
	cout<<"Finish sorting array. Execution time = "<<search_time<<" milliseconds"<<endl;
	fout<<endl<<endl<<endl<<"Start sorting array (Quick sort)"<<endl;
	fout<<"Finish sorting array. Execution time = "<<search_time<<" milliseconds"<<endl<<endl;

	//Print results (sort array)
	fout<<endl<<endl<<"********************\tSort array:"<<endl;
	for(int i=0; i<size; i++)
	{	 
		fout.width(format_out);
		fout.setf(ios::left);
		if(i%elements_in_row==0 && i!=0) fout<<endl<<endl;
		fout<<a[i]<<"\t\t";
	}
	fout.close();
	delete [] a;
	MPI_Finalize();
	return 0;
	}
}

/*
#include <stdio.h>
  #include "mpi.h"
  int main(int argc, char* argv[]){
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if ( ProcRank == 0 ){
      // Действия, выполняемые только процессом с рангом 0
      printf ("\n Hello from process %3d", ProcRank);
      for ( int i=1; i<ProcNum; i++ ) {
        MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE, 
          MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        printf("\n Hello from process %3d", RecvRank);
      }
    } 
    else // Сообщение, отправляемое всеми процессами, 
         // кроме процесса с рангом 0
      MPI_Send(&ProcRank,1,MPI_INT,0,0,MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
  }*/