#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include "../include/Objeto.hpp"
#include "../include/Cena.hpp"
#include "../include/Algoritimo.hpp"



int main() {
    //Inicia os OBJS e Moves com os maximos
    Obj Objs[200];
    int n_Objs = 0;
    Move movimentos[400];
    int n_movimentos = 0;
    int scene_arr[40];
    int n_cenas = 0;

    char linha[256];

    // Lê e armazena as entradas
    while (std::cin.getline(linha, 256)) {
        if (linha[0] == '\0') continue;
        if (linha[0] == 'O') {
            int id; double x, y, largura;
            sscanf(linha, "O %d %lf %lf %lf", &id, &x, &y, &largura);
            Objs[n_Objs++] = Obj(id, x, y, largura);
        }
        else if (linha[0] == 'M') {
            Move m;
            sscanf(linha, "M %d %d %lf %lf", &m.time, &m.id, &m.position_x, &m.position_y);
            movimentos[n_movimentos++] = m;
        }
        else if (linha[0] == 'C') {
            int scenet;
            sscanf(linha, "C %d", &scenet);
            scene_arr[n_cenas++] = scenet;
        }
    }

    if (n_cenas == 0) {
        return 1;
    }

    // Para cada cena aplica movimentos
    for (int x = 0; x < n_cenas; ++x) {
        int scenet = scene_arr[x];

        
        Obj Objs_cena[200];
        for (int i = 0; i < n_Objs; ++i)
            Objs_cena[i] = Objs[i];

        // Aplica movimentos até tempo da cena
        for (int idx = 0; idx < n_movimentos; ++idx) {
            Move& m = movimentos[idx];
            if (m.time <= scenet) {
                for (int i = 0; i < n_Objs; ++i) {
                    if (Objs_cena[i].id == m.id) {
                        Objs_cena[i].position_x = m.position_x;
                        Objs_cena[i].position_y = m.position_y;
                    }
                }
            }
        }

        // Gera cena
        Scene cena;
        hiddenscene(Objs_cena, n_Objs, &cena);
        cena.settime(scenet);

        // Ordena os segmentos por ID
        int n_segmentos = cena.getsize();
        Segment segmentos_ordenados[200];

        for (int i = 0; i < n_segmentos; ++i) {
            segmentos_ordenados[i] = cena[i];
        }

        bool precisa_ordenar = (n_Objs > 2);
        if (precisa_ordenar) {
            quicksort_segments(segmentos_ordenados, 0, n_segmentos - 1);
        }

        //Printa a saida final
        imprimirSegmentos(cena, segmentos_ordenados, n_segmentos);
    }

    return 0;
}