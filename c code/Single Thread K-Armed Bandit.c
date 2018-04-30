#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Random.h"
#include <windows.h>
#include <math.h>

// https://stackoverflow.com/questions/1787996/c-library-function-to-do-sort
// https://stackoverflow.com/questions/6218399/how-to-generate-a-random-number-between-0-and-1

const int ITERATIONS_PER_RUN = 100;
const int RUNS = 1;

double epsilon = 10, mu = 0, sigma = 0.5;
int k = 10;
double *Q; // estimate values
int *N; // actions
double *reward_history;


int epsilonEquivalent(double x, double y, double e) {
    return fabs(x - y) <= e;
}

int cmp(const void *x, const void *y) {
  double xx = *(double*)x, yy = *(double*)y;
  if (xx < yy) return -1;
  if (xx > yy) return  1;
  return 0;
}

double maxQ() {
    int i;
    double max = Q[0];
    for(i = 1; i < k; i++) {
        if (max < Q[i]) {
            max = Q[i];
        }
    }
    return max;
}
double bandit(int action) {
    double *environment_reward;
    environment_reward = (double *)malloc(sizeof(double)*k);
    environment_reward = gauss(mu, sigma, k);
    qsort(environment_reward, k, sizeof(double), cmp);
    return environment_reward[action];
}
int main (int argc, char **argv) {
    int i, j, m;
    int action;
    double max_estimate;
    int *max_actions;
    int psbl_act_cnt;
    double reward;
    FILE * fp;

    srand(time(0));

    reward_history = (double *)malloc(sizeof(double)*ITERATIONS_PER_RUN);
    Q = (double *)malloc(sizeof(double)*k);
    N = (int *)malloc(sizeof(int)*k);
    for(i = 0; i < ITERATIONS_PER_RUN;i++) {
        reward_history[i] = 0;
    }
    for(i = 0; i < RUNS; i++) {
        for(m = 0; m < k; m++) {
            Q[m] = 0;
            N[m] = 0;
        }
        max_actions = malloc(sizeof(int));
        for(j = 0; j < ITERATIONS_PER_RUN; j++) {
            if (RandInRage(0, 100) <= (100-epsilon)){
                max_estimate = maxQ();
                psbl_act_cnt = 0;
                for(m = 0; m < k; m++) {
                    if (epsilonEquivalent(Q[m], max_estimate, 0.00000000001)) {
                        psbl_act_cnt = psbl_act_cnt + 1;
                        max_actions = (int *)realloc(max_actions, sizeof(int)*psbl_act_cnt);
                        max_actions[psbl_act_cnt-1] = m;
                    }
                }
                action = rand()%psbl_act_cnt;
                action = max_actions[action];
            }
            else {
                action = rand()%k;
            }
            reward = bandit(action);
            N[action] = N[action] + 1;
            Q[action] = Q[action] + (reward-Q[action])/N[action];
            reward_history[j] = ( reward_history[j] * i  + reward ) / ( i + 1 );
        }
        free(max_actions);
    }
    
    // fp = fopen ("STKABC.txt","ab+");
    // for(i = 0; i < ITERATIONS_PER_RUN;i++) {
    //     fprintf (fp, "%lf,", reward_history[i]/RUNS);
    // }
    // fclose (fp);
}
