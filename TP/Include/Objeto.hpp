#ifndef OBJETO_HPP
#define OBJETO_HPP

// Essa aqui é a estrutura que representa um objeto
struct Obj {
    // Id do objeto
    int id;
    //posição no eixo x
    double position_x;  
    //posição no eixo y     
    double position_y;
    //Largura do objeto       
    double width;

    // construtores
    Obj();  
    Obj(int id, double positionx, double positiony, double width);
};

// Implementação da lista de Objetos
class Obj_List {
private:
    // Dados do obj
    Obj* data;
    // Capacidade da lista
    int capacity;
    //Tamanho da lista
    int size;

public:
    //contrutor e destrutor
    Obj_List(int capacity = 10);
    ~Obj_List();

    // função para adicionar o elemento (parametro: Obj a ser adicionado)
    bool add(const Obj& obj);
    // função para procurar ID do elemento (parametro: ID do obj)
    Obj* searchId(int id);
    // função para conseguir o tamanho da lsita 
    int getsize() const;
    // Operador para ajudar na construção
    Obj& operator[](int idposition_x);
    // função para limpar a Lista
    void clean();
};

#endif 