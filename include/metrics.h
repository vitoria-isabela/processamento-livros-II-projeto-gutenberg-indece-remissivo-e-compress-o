#ifndef METRICS_H
#define METRICS_H

#include <chrono>
using namespace std;

//#include "config.h"

typedef chrono::high_resolution_clock Clock;

typedef struct {
    unsigned int n_comp;
    unsigned int n_mov;
    double time;
} PerformanceMetrics;

void SetUpPerformanceMetrics(PerformanceMetrics* pm);

void PerformanceMetricsCPUTime(PerformanceMetrics* pm, double time);

void PerformanceMetricsPrint(string method, PerformanceMetrics* pm, int reportLog);

#endif /* METRICS_H */
