
#include <iostream>
#include <fstream>
#include "metrics.h"
#include "config.h"

void SetUpPerformanceMetrics(PerformanceMetrics *pm)
{
    pm->n_comp = 0;
    pm->n_mov = 0;
    pm->time = 0.0;
}

void PerformanceMetricsPrint(string method, PerformanceMetrics *pm, int reportLog)
{
    string dir = SORTMETHOD + to_string(reportLog) + "sort_results.txt";
    fstream report;
    report.open(dir, ios::out | ios::app );    
    report << " ---------------------------------------------------------------------------------- " << endl;
    report << " METODO DE ORDENACAO " << method << endl;
    report << " Tempo de execução: " << pm->time << " segundos" << endl;
    report << " Comparacoes: " << pm->n_comp << endl;
    report << " Movimentacoes: " << pm->n_mov << endl;
    report << " ---------------------------------------------------------------------------------- " << endl;
    report << endl;
}

void PerformanceMetricsCPUTime(PerformanceMetrics *pm, double time)
{
    pm->time = time;
}