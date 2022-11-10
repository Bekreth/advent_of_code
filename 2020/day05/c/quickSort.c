#include "quickSort.h"

void quickSort(int *input, int first, int last){
   int i, j, pivot, temp;
   if(first < last){
      pivot = first;
      i = first;
      j = last;

      while(i < j){
         while(input[i] <= input[pivot] && i < last) i++;
         while(input[j] > input[pivot]) j--;
         if(i < j){
            temp = input[i];
            input[i] = input[j];
            input[j] = temp;
         }
      }

      temp = input[pivot];
      input[pivot] = input[j];
      input[j] = temp;
      quickSort(input, first, j-1);
      quickSort(input, j + 1, last);
   }
}