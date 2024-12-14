#include <stdio.h>
#include <stdlib.h>

// This is a super-basic quicksort implementation following the Lomuto partition scheme
// https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme

int* Partition(int* low_ptr, int* high_ptr){
  int pivot = *high_ptr;
  int* ptr_pivot = low_ptr;
  int* ptr_iter = low_ptr;
  int tmp = 0;
  while(ptr_iter != high_ptr){
    if(*ptr_iter <= pivot){
      tmp = *ptr_pivot;
      *ptr_pivot = *ptr_iter;
      *ptr_iter = tmp;
      ptr_pivot++;
    }
    ptr_iter++;
  }
  *high_ptr = *ptr_pivot;
  *ptr_pivot = pivot;
  return ptr_pivot;
}

void Quicksort(int* low_ptr, int* high_ptr){
  if(low_ptr >= high_ptr){
    return;
  }
  int* partition_ptr = Partition(low_ptr, high_ptr);
  if(low_ptr != partition_ptr){
    Quicksort(low_ptr, partition_ptr - 1);
  }
  Quicksort(partition_ptr + 1, high_ptr);
}


int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Error! qsort expects exactly one argument:\n");
    printf("  1. A filename that contains a list of numbers to sort\n");
    return 1;
  }
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("Encountered an error in loading file: %s", argv[1]);
    return 2;
  } 
  
  int num_lines = 0;
  fscanf(fp, "%d\n", &num_lines);
  int* data = (int*) malloc(num_lines * sizeof(int));

  for(int i = 0; i < num_lines; i++){
    fscanf(fp, "%d\n", data + i);   
  }
  
  Quicksort(data, data + num_lines - 1);
  
  for(int i = 0; i < num_lines; i++){
    printf("%d\n", data[i]);
  }


  fclose(fp);
  free(data);
}
