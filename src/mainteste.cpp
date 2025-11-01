#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstring>
#include "../include/Algoritimo.hpp"
#include "../include/Objeto.hpp"
#include "../include/Cena.hpp"

#define MAposition_xX_ObjS 100
#define MAposition_xX_moviments 200
#define MAposition_xX_SceneS 20
#define MAposition_xX_LINHA 128


int main() {
    Obj Objs[MAposition_xX_ObjS];
    int n_Objs = 0;
    Move moviments[MAposition_xX_moviments];
    int n_moviments = 0;
    int times_Scene[MAposition_xX_SceneS];
    int n_Scenes = 0;

    std::cout << "Digite as linhas de entrada (O, M, C). Para terminar, digite FIM:\n";

    char linha[MAposition_xX_LINHA];

    // Armazena Objs, moviments e Scenes
    while (true) {
        std::cin.getline(linha, MAposition_xX_LINHA);
        if (strcmp(linha, "FIM") == 0) break;
        if (linha[0] == '\0') continue;
        if (linha[0] == 'O') {
            int id; double position_x, position_y, largura;
            sscanf(linha, "O %d %lf %lf %lf", &id, &position_x, &position_y, &largura);
            Objs[n_Objs++] = Obj(id, position_x, position_y, largura);
        }
        else if (linha[0] == 'M') {
            Move m;
            sscanf(linha, "M %d %d %lf %lf", &m.time, &m.id, &m.position_x, &m.position_y);
            moviments[n_moviments++] = m;
        }
        else if (linha[0] == 'C') {
            int time_Scene;
            sscanf(linha, "C %d", &time_Scene);
            times_Scene[n_Scenes++] = time_Scene;
        }
    }

    if (n_Scenes == 0) {
        std::cerr << "Nenhuma Scene ('C <time>') foi informada.\n";
        return 1;
    }

    // Para cada Scene, aplica moviments e gera saída
    for (int Scene_idposition_x = 0; Scene_idposition_x < n_Scenes; ++Scene_idposition_x) {
        int time_Scene = times_Scene[Scene_idposition_x];

        // Cria cópia dos Objs originais para não alterar para próposition_ximas Scenes
        Obj Objs_Scene[MAposition_xX_ObjS];
        for (int i = 0; i < n_Objs; ++i)
            Objs_Scene[i] = Objs[i];

        // Aplica moviments até time da Scene
        for (int m_idposition_x = 0; m_idposition_x < n_moviments; ++m_idposition_x) {
            Move& m = moviments[m_idposition_x];
            if (m.time <= time_Scene) {
                for (int i = 0; i < n_Objs; ++i) {
                    if (Objs_Scene[i].id == m.id) {
                        Objs_Scene[i].position_x = m.position_x;
                        Objs_Scene[i].position_y = m.position_y;
                    }
                }
            }
        }

        // Gera Scene
        Scene scn;
        hiddenscene(Objs_Scene, n_Objs, &scn);
        scn.settime(time_Scene);

        // Ordenação dos segmentos por ID, se necessário
        int n_segmentos = scn.getsize();
        Segment segmentos_ordenados[MAposition_xX_ObjS];

        for (int i = 0; i < n_segmentos; ++i) {
            segmentos_ordenados[i] = scn[i];
        }

        // Ordenar por ID se necessário
        bool precisa_ordenar = (n_Objs > 2); // ajuste se necessário
        if (precisa_ordenar) {
            for (int i = 0; i < n_segmentos - 1; i++) {
                for (int j = i + 1; j < n_segmentos; j++) {
                    if (segmentos_ordenados[i].id > segmentos_ordenados[j].id) {
                        Segment temp = segmentos_ordenados[i];
                        segmentos_ordenados[i] = segmentos_ordenados[j];
                        segmentos_ordenados[j] = temp;
                    }
                }
            }
        }

        // Imprimir segmentos visíveis
        std::cout << std::fixed << std::setprecision(2);
        for (int i = 0; i < n_segmentos; ++i) {
            Segment& seg = segmentos_ordenados[i];
            std::cout << "S " << scn.gettime() << " " << seg.id << " " 
                      << seg.begin << " " << seg.end<< "\n";
        }
    }

    return 0;
}

