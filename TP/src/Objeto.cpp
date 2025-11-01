#include "../Include/Objeto.hpp"

// Implementação da Classe Obj

//implementação do contrutor padrão
Obj::Obj() : id(-1), position_x(0), position_y(0), width(0) {
    id = -1;
    position_x = 0; 
    position_y= 0;
    width = 0;
}
//implementação do contrutor por parâmetro
Obj::Obj(int new_id, double new_position_x, double new_position_y, double new_width){ 
    id = new_id;
    position_x = position_x; 
    position_y = new_position_y; 
    width = new_width; 
}

// Implementação da Classe Obj_List

//implementação do contrutor por parâmetro de capacidade inicial
Obj_List::Obj_List(int capacity_inicial){
    capacity= capacity_inicial;
    data = new Obj[capacity];
    size = 0;
}

// destrutor
Obj_List::~Obj_List() {
    delete[] data;
}

//classe de adicionar item
bool Obj_List::add(const Obj& obj) {
    //checa se a capacidade menor que o tamanho
    if (size >= capacity) {
        int new_capacity = capacity * 2;
        //aloca um vetor com capacidade dobrada
        Obj* novo_array = new Obj[new_capacity];
        //copia os dados do antigo vetor nele e set novos parametros
        for (int i = 0; i < size; ++i)
         novo_array[i] = data[i];
        delete[] data;
        data = novo_array;
        capacity = new_capacity;
    }
    data[size++] = obj;
    return true;
}

//função que procura o ID na lista
Obj* Obj_List::searchId(int id) {
    //percorre o vetor todo comparando elemento por elemento
    for (int i = 0; i < size; ++i) {
        if (data[i].id == id)
            return &data[i];
    }
    return nullptr;
}

//função get do tamanho
int Obj_List::getsize() const {
    return size;
}
//Operador auxiliar
Obj& Obj_List::operator[](int idposition_x) {
    
    return data[idposition_x];
}
//função de limpar o vetor
void Obj_List::clean() {
    size = 0;
}