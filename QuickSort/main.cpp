//QuickSort - реализация алгоритма быстрой сортировки
//@param a sort array
//@param n index the last of array elements
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template <typename T>
void quickSort(T* a, const long n) {
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
  if (j > 0) quickSort(a, j);
  if (n > i) quickSort(a + i, n - i);
}

int main(){
	cout<<"Enter size of array: ";
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
    quickSort(a, size-1);
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
	return 0;
}