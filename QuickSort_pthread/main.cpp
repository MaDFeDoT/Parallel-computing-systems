#include <pthread.h>

//QuickSort - реализация алгоритма быстрой сортировки
//@param a sort array
//@param n index the last of array elements
#include <iostream>
#include <fstream>
#include <ctime>
#include <pthread.h>

#define ERROR_CREATE_THREAD -11
using namespace std;

struct pthrData
{
    long size;
    int *a;
    unsigned int rec_level;
};

void* quickSort(void* thread_data) {
  unsigned int recursion_level=2;
  pthrData *data=(pthrData*) thread_data;
  int *a=data->a;
  long n=data->size;
  long i = 0, j = n;
  int pivot = a[n / 2]; // pivot element
  do {
    while (a[i] < pivot) i++;
    while (a[j] > pivot) j--;
    if (i <= j) {
      std::swap(a[i], a[j]);
      i++; j--;
    }
  } while (i <= j);
  if (data->rec_level<recursion_level) {
    pthread_t thread1;
    bool flag1=true;
    pthread_t thread2;
    bool flag2=true;
    if (j > 0)
    {
        pthrData new_data;
        new_data.a=a;
        new_data.size=j;
        new_data.rec_level=++data->rec_level;
        flag1=pthread_create(&thread1, NULL, quickSort, &new_data);
        if (flag1) {
            printf("main error: can't create thread\n");
            exit(ERROR_CREATE_THREAD);
        }
    }
    if (n > i)
    {
        pthrData new_data;
        new_data.a=a+i;
        new_data.size=n-i;
        new_data.rec_level=++data->rec_level;
        flag2=pthread_create(&thread2, NULL, quickSort, &new_data);
        if (flag2) {
            printf("main error: can't create thread\n");
            exit(ERROR_CREATE_THREAD);
        }
    }
    if(!flag1) pthread_join(thread1, NULL);
    if(!flag2) pthread_join(thread2, NULL);
  }
  else
  {
      if(j > 0)
      {
          pthrData new_data;
          new_data.a=a;
          new_data.size=j;
          quickSort(&new_data);
      }
      if (n > i)
      {
          pthrData new_data;
          new_data.a=a+i;
          new_data.size=n-i;
          quickSort(&new_data);
      }
  }
  pthread_exit(0);
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
    ofstream fout;
    fout.open("results.txt");
    fout<<"********************\tArray:"<<endl<<endl;
    for(int i=0; i<size; i++)
    {
        a[i]=first_value+rand()%last_value;
        fout.width(format_out);
        fout.setf(ios::left);
        if(i%elements_in_row==0 && i!=0) fout<<endl;
        fout<<a[i]<<"\t\t";
    }
    pthrData data;
    data.a=a;
    data.size=size;
    data.rec_level=0;
    //Start quick sorting array
    cout<<endl<<"Start sorting array (Quick sort)"<<endl;
    unsigned int start_time =  clock(); // start time

    //create id thread
    pthread_t thread;
    pthread_create(&thread, NULL, quickSort, &data);
    //wait finish pthread
    pthread_join(thread, NULL);

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