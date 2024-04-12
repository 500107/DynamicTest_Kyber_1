#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "kem.h"
#include "kex.h"
#include "params.h"
#include "indcpa.h"
#include "polyvec.h"
#include "poly.h"
#include "cpucycles.h"
#include "speed_print.h"

#define NTESTS 1199999//Actual Test Time should be 'NTEST + 1'
//Since for Setting the initial value of Mean, the First execution must be OUTSIDE of the For loop;
//So just like if we are going to Test the Var of 5000 times of Execution, NTEST must be 4999 because  
//the 1st test is not included in the NTEST for loop. 

int main()
{
    uint64_t t_start1, t_end1, t_start2, t_end2;
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
    uint8_t key[CRYPTO_BYTES];
    double mean;//Current Mean Value
    double mean_1;
    double mean_pre;//previous Mean value
    double mean_pre1;
    double M2 = 0.0; // M2 = n * Variance
    double M1 = 0.0; // M1 = n * Variance in 
    double variance;
    double variance_1;
    uint64_t count = 1; 
    uint64_t count_1 = 1;
    unsigned int ntests = NTESTS;

// # This is the test for the First Key groups 
      crypto_kem_keypair(pk, sk);
      printf("\n");
      printf("This is the Test for ntests %u.\n", ntests);
      printf("\n");
      crypto_kem_enc(ct, key, pk);
      t_start1 = cpucycles();
      crypto_kem_dec(key, ct, sk);
      t_end1 = cpucycles();

      // initialization of Mean
      mean_pre = (double)t_end1 - (double)t_start1;

      for (unsigned int i = 0; i < ntests; i++)
      {
          crypto_kem_enc(ct, key, pk);
          t_start1 = cpucycles();
          crypto_kem_dec(key, ct, sk);
          t_end1 = cpucycles();
          uint64_t time1 = t_end1 - t_start1;
          // Calculation of Running / INcremental Variance
          count++;
          mean = mean_pre + ((double)time1 - mean_pre) / count; // Incremental fomula for 'RunningMean'
          M2 = M2 + ((double)time1 - mean_pre) * ((double)time1 - mean);
          mean_pre = mean;
      }

      // calculation 
      printf("\n");
      variance = M2 / count;
      printf("Mean: %lf cycles/ticks\n", mean);
      printf("Variance: %lf cycles/ticks\n", variance);
      printf("\n");
// # This is the test for the First Key groups 

// # This is the test for the Second Key groups      
    crypto_kem_keypair(pk, sk);
      printf("\n");
      printf("This is the Test for ntests %u.\n", ntests);
      printf("\n");
      crypto_kem_enc(ct, key, pk);
      t_start2 = cpucycles();
      crypto_kem_dec(key, ct, sk);
      t_end2 = cpucycles();

      // initialization of Mean
      mean_pre1 = (double)t_end2 - (double)t_start2;

      for (unsigned int j = 0; j < ntests; j++)
      {
          crypto_kem_enc(ct, key, pk);
          t_start2 = cpucycles();
          crypto_kem_dec(key, ct, sk);
          t_end2 = cpucycles();
          uint64_t time2 = t_end2 - t_start2;
          // Calculation of Running / INcremental Variance
          count_1++;

          mean_1 = mean_pre1 + ((double)time2 - mean_pre1) / count_1; // Incremental fomula for 'RunningMean'
          M1 = M1 + ((double)time2 - mean_pre1) * ((double)time2 - mean_1);
          mean_pre1 = mean_1;
      }

      // calculation 
      printf("\n");
      variance_1 = M1 / count_1;
      double tvla = fabs(mean - mean_1) / sqrt((variance / (ntests + 1)) + (variance_1 / (ntests + 1)));

      printf("Mean: %lf cycles/ticks\n", mean_1);
      printf("Variance: %lf cycles/ticks\n", variance_1);
      printf("TVLA for two times of decryption is %f\n", tvla);
      printf("\n");
      printf("test...\n");
    return 0;
// # This is the test for the Second Key groups 
}
