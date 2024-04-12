#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cpucycles.h"
#include "speed_print.h"

//#include <iostream>
//#include <cmath>
#include <math.h>




static int cmp_uint64(const void *a, const void *b) {
  if(*(uint64_t *)a < *(uint64_t *)b) return -1;
  if(*(uint64_t *)a > *(uint64_t *)b) return 1;
  return 0;
}

static uint64_t median(uint64_t *l, size_t llen) {
  qsort(l,llen,sizeof(uint64_t),cmp_uint64);

  if(llen%2) return l[llen/2];
  else return (l[llen/2-1]+l[llen/2])/2;
}

static uint64_t average(uint64_t *t, size_t tlen) {
  size_t i;
  uint64_t acc=0;
 //New t shld be Defined as t[i] = t[2*i+1] - t[2*i] 
 t[i] = t[2*i+1] - t[2*i];
 
  for(i=0;i<tlen;i++)
    acc += t[i];

  return acc/tlen;
}

static uint64_t variance(uint64_t *t, size_t tlen) {
  size_t i;
  uint64_t acc = 0;
  uint64_t ave;
 //New t shld be Defined as t[i] = t[2*i+1] - t[2*i] 
 t[i] = t[2*i+1] - t[2*i];
  
  for(i=0;i<tlen;i++){
    acc += t[i];
    }
  ave = acc/tlen; //mean calculation 
  
  uint64_t diff[tlen];
  for (size_t i = 0; i < tlen; ++i) {
    diff[i] = t[i] - ave;
    }//difference between mean and EACH Element of the array
  
  uint64_t square_diff[tlen];
  for (size_t i = 0; i < tlen; ++i) {
    square_diff[i] = diff[i] * diff[i];
    }//Squaring the Difference
  
  uint64_t variance = 0.0;
  for (size_t i = 0; i < tlen; ++i) {
    variance += square_diff[i];
    }
    variance /= tlen;//calculate the Variance

  return variance;
}

static uint64_t deviation(uint64_t *t, size_t tlen){
  size_t i;
  uint64_t acc = 0;
  uint64_t ave;
 //New t shld be Defined as t[i] = t[2*i+1] - t[2*i] 
 t[i] = t[2*i+1] - t[2*i];
  
  for(i=0;i<tlen;i++){
    acc += t[i];
    }
  ave = acc/tlen; //mean calculation 
  
  uint64_t diff[tlen];
  for (size_t i = 0; i < tlen; ++i) {
    diff[i] = t[i] - ave;
    }//difference between mean and EACH Element of the array
  
  uint64_t square_diff[tlen];
  for (size_t i = 0; i < tlen; ++i) {
    square_diff[i] = diff[i] * diff[i];
    }//Squaring the Difference
  
  uint64_t variance = 0.0;
  for (size_t i = 0; i < tlen; ++i) {
    variance += square_diff[i];
    }
    variance /= tlen;//calculate the Variance
  
  uint64_t std_deviation = sqrt(variance);

  return std_deviation;
}



void print_results(const char *s, uint64_t *t, size_t tlen)
{
  size_t i;
  static uint64_t overhead = -1;

  if(tlen < 2) 
  {
    fprintf(stderr, "ERROR: Need a least two cycle counts!\n");
    return;
  }

  if(overhead  == (uint64_t)-1)
    overhead = cpucycles_overhead();

  tlen--;
  for(i=0;i<tlen;++i)
  {
    t[i] = t[2*i+1] - t[2*i] - overhead;
  }
  printf("I have finished iteration...\n");
  
  printf("%s\n", s);
//  printf("median: %llu cycles/ticks\n", (unsigned long long)median(t, tlen));
//printf("average: %llu cycles/ticks\n", (unsigned long long)average(t, tlen));
// printf("Standard Deviation: %llu cycle/tickets\n", (unsigned long long)deviation(t, tlen));
  printf("Variance: %llu cycle/tickets\n", (unsigned long long)variance(t, tlen));
// printf("length:%llu\n", tlen);
  printf("\n");

}
