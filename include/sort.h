#ifndef SORT_H
#define SORT_H

#include <chrono>
#include <iostream>
#include <vector>
using namespace std;

#include "metrics.h"

// Use essa função para movimentar dados
template <typename T>
void troca(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}
/*
template <typename T>
void shellsort_internal(T *array, int size, bool (*compare)(T &, T &), PerformanceMetrics *p) // Passa como parametro o vetor e o tamanho
{
    int i, j, h;
    T *aux;

    for (h = 1; h < size; h = 3 * h + 1)
        ; // calcula o h inicial.

    while (h > 0)
    {
        h = (h - 1) / 3; // atualiza o valor de h.
        for (i = h; i < size; i++)
        {
            aux = array[i];
            j = i;
            // efetua comparações entre elementos com distância h:
            while (compare(array[j - h].chave > aux.chave)
            {
                p->n_comp++;
                array[j] = array[j - h];
                p->n_mov++;
                j -= h;
                if (j < h)
                    break;
            }
            array[j] = aux;
            p->n_mov++;
        }
    }
} */

template <typename T>
void shellsort_internal(T *arr, int size, bool (*compare)(T &, T &), PerformanceMetrics *p)
{
    int gap, j, k;
    for (gap = size / 2; gap > 0; gap = gap / 2)
    {
        // inicialmente gap = n/2 diminuindo por gap /2
        for (j = gap; j < size; j++)
        {
            for (k = j - gap; k >= 0; k -= gap)
            {
                p->n_comp++;
                if (compare(arr[k + gap], arr[k]))
                {
                    troca(arr[k + gap], arr[k]);
                    p->n_mov++;
                }
                else
                    break;
            }
        }
    }
}

template <typename T>
void merge(T *array, int start, int end, bool (*compare)(T &, T &), PerformanceMetrics *p)
{
    int mid = (start + end) / 2;

    int StarMid = mid - start + 1;
    int MidP1End = end - mid;

    // Criar arrays temporários
    T *arrayEsq = new T[StarMid];
    T *arrayDir = new T[MidP1End];

    // Copiar dados do vetor para os temporários
    for (int i = 0; i < StarMid; i++)
    {
        arrayEsq[i] = array[start + i];
        p->n_mov++;
    }

    for (int j = 0; j < MidP1End; j++)
    {
        arrayDir[j] = array[mid + 1 + j];
        p->n_mov++;
    }

    int indexOfArrayEsq = 0, // Índice inicial do primeiro subarray

        indexOfArrayDir = 0;        // Índice inicial do segundo subarray
    int indexOfMergedArray = start; // Índice inicial do array mesclado

    // Mesclar arrays temporarios de volta ao principal esquerda->direita
    while (indexOfArrayEsq < StarMid && indexOfArrayDir < MidP1End)
    {
        p->n_comp++;
        if (compare(arrayEsq[indexOfArrayEsq], arrayDir[indexOfArrayDir]))
        {
            p->n_mov++;
            array[indexOfMergedArray] = arrayEsq[indexOfArrayEsq];
            indexOfArrayEsq++;
        }
        else
        {
            p->n_mov++;
            array[indexOfMergedArray] = arrayDir[indexOfArrayDir];
            indexOfArrayDir++;
        }
        indexOfMergedArray++;
    }

    // Copia os elementos restantes de
    // arrayEsq[], se houver algum
    while (indexOfArrayEsq < StarMid)
    {
        p->n_mov++;
        array[indexOfMergedArray] = arrayEsq[indexOfArrayEsq];
        indexOfArrayEsq++;
        indexOfMergedArray++;
    }

    // Copia os elementos restantes de
    // arrayDir[], se houver algum
    while (indexOfArrayDir < MidP1End)
    {
        p->n_mov++;
        array[indexOfMergedArray] = arrayDir[indexOfArrayDir];
        indexOfArrayDir++;
        indexOfMergedArray++;
    }
}

// função de template para realizar merge sort em array, arr
template <typename T>
void mergesort_internal(T *array, int start, int end, bool (*compare)(T &, T &), PerformanceMetrics *p)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;
    mergesort_internal(array, start, mid, compare, p);   // merge classifica os elementos no intervalo [start, mid]
    mergesort_internal(array, mid + 1, end, compare, p); // merge classifica os elementos no intervalo [mid+1, end]
    merge(array, start, end, compare, p);                // mescla os 2 componentes acima
}

template <typename T>
void quicksort_internal(T *array, int low, int high, bool (*compare)(T &, T &), PerformanceMetrics *p)
{

    if (low < high)
    {
        int pi = partition(array, low, high, compare, p);

        quicksort_internal(array, low, pi - 1, compare, p);
        quicksort_internal(array, pi + 1, high, compare, p);
    }
}

template <typename T>
int partition(T *arr, int start, int end, bool (*compare)(T &, T &), PerformanceMetrics *p)
{
    T pivot = arr[end];
    int i = (start - 1);
    for (int j = start; j <= end - 1; j++)
    {
        if (compare(arr[j], pivot)) // arr[j] < pivot
        {
            i++;
            T t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            p->n_mov += 1;
            p->n_comp += 1;
        }
        else
        {
            p->n_comp += 1;
        }
    }
    T t = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = t;
    p->n_mov += 3;
    return (i + 1);
}

template <typename T>
void shell_sort(T *array, int size, bool (*compare)(T &, T &), int reportLog)
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    shellsort_internal<T>(array, size - 1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Shell Sort:" << endl;
    PerformanceMetricsPrint("Shell Sort:",&p,reportLog);
}

template <typename T>
void shell_sort(T *array, int size, bool (*compare)(T &, T &))
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    shellsort_internal<T>(array, size - 1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Shell Sort:" << endl;
    
}



template <typename T>
void merge_sort(T *array, int size, bool (*compare)(T &, T &), int reportLog)
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    mergesort_internal(array, 0, size - 1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Merge Sort:" << endl;
    PerformanceMetricsPrint("Merge Sort:",&p,reportLog);
}

template <typename T>
void merge_sort(T *array, int size, bool (*compare)(T &, T &))
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    mergesort_internal(array, 0, size - 1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Merge Sort:" << endl;
    
}

template <typename T>
void quick_sort(T *array, int size, bool (*compare)(T &, T &), int reportLog)
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    quicksort_internal(array, 0, size - 1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Quick Sort:" << endl;
    PerformanceMetricsPrint("Quick Sort",&p,reportLog);
}

template <typename T>
void quick_sort(T *array, int size, bool (*compare)(T &, T &))
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    quicksort_internal(array, 0, size - 1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Quick Sort:" << endl;    
}


#endif /* SORT_H */