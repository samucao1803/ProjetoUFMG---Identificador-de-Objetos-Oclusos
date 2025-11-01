#ifndef ALGORITMO_OCLUSAO_HPP
#define ALGORITMO_OCLUSAO_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include "Objeto.hpp"
#include "Cena.hpp"

// Representação dos intervalos de cena
struct interval {
    //inicio e fim dos intervalos
    double ini, end;
    //contrutores 
    interval() : ini(0), end(0) {}
    interval(double i, double f) : ini(i), end(f) {}
}; 

//Representação das movimentações
struct Move {
    //momento das movimentações
    int time;
    //Id do objeto movimentado
    int id;
    //posição movimentada
    double position_x, position_y;
};

//Arvore de pesquisa binaria
int bisearch(interval arr[], int n, double valor);

// Insere (merge) um novo interval no arraposition_y de coverd, mantendo ordenado e sem sobreposição
void addinterval(interval coverd[], int& n_coverd, double ini, double end);

// Função auxiliar para trocar intervalos 
void swapIntervals(interval& a, interval& b);

// Função de partição do Quick Sort
int partitionIntervals(interval arr[], int baixo, int alto);

// Funçao Quick Sort para os intervalos
void quickSortIntervals(interval arr[], int baixo, int alto);

// Obtém trechos não coverd no interval [ini, end)
int getvisible(interval coverd[], int n_coverd, double ini, double end, interval visiveis[], int& n_visiveis);

// Função para trocar dois obj
void swap(Obj& a, Obj& b);

// Insertion Sort
void InsertionSort(Obj* arr, int l, int r);

// Função para a mediana de 3
int medianaDe3(Obj* arr, int l, int r);

// Quicksort com mediana de 3 e insertion sort
void QuickSort(Obj* arr, int l, int r) ;

//Função recursiva de processamento
void processrecur(Obj* Objs, int num_Objs, Scene* Scene, double seg_ini, double seg_fim, int nivel);

// Gera a Cena no tempo especificado, aplicando o algoritmo de oclusão
void hiddenscene(Obj* objs, int num_objs, Scene* Scene);

// Função para imprimir segmentos
void imprimirSegmentos(Scene& cena, Segment segmentos[], int n);

// Função auxiliar para trocar dois Segmentos de lugar.
void swap_segments(Segment& a, Segment& b);
//partição do quick sort de segmentos
int partition_segments(Segment arr[], int low, int high);
//quick sort de segmentos
void quicksort_segments(Segment arr[], int low, int high);



#endif // ALGORITMO_OCLUSAO_HPP
