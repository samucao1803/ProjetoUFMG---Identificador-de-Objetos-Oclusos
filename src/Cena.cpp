#include "../include/Cena.hpp"

// Implementação do Segment

//implementação do contrutor padrão
Segment::Segment() {
    id = -1;
    begin = 0;
    end = 0;
}

//implementação do contrutor por parâmetro
Segment::Segment(int new_id, double new_begin, double new_end){
    id = new_id;
    begin = new_begin;
    end = new_end;
}

// Implementação da Scene

//implementação do contrutor com capacidade como parâmetro
Scene::Scene(int capacity_inicial){
    capacity = capacity_inicial;
    seg = new Segment[capacity];
    size = 0;
    time = 0;
}

//destrutor padrão
Scene::~Scene() {
    delete[] seg;
}

//função set do tempo
void Scene::settime(int time_) {
    time = time_;
}

//função get do tempo
int Scene::gettime() const {
    return time;
}

//classe de adicionar segmento
bool Scene::add(const Segment& segm) {
    //checa se a capacidade menor que o tamanho
    if (size == capacity) {
        //aloca um vetor com capacidade dobrada
        int nova_capacity = capacity * 2;
        Segment* new_array = new Segment[nova_capacity];
        //copia os dados do antigo vetor nele e set novos parametros
        for (int i = 0; i < size; ++i)
         new_array[i] = seg[i];
        delete[] seg;
        seg = new_array;
        capacity = nova_capacity;
    }
    seg[size++] = segm;
    return true;
}

//função get do tamanho
int Scene::getsize() const {
    return size;
}

//operador auxiliar
Segment& Scene::operator[](int idposition_x) {
    return seg[idposition_x];
}

//função de limpeza
void Scene::clean() {
    size = 0;
}


