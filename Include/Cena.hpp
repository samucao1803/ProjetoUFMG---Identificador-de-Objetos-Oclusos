#ifndef CENA_HPP
#define CENA_HPP

// Representa a Cena visivel final
struct Segment {
    // id do obj
    int id;         
    // inicio do segmento
    double begin;  
    //fim do segmento
    double end;      

    //construtores
    Segment();
    Segment(int id_, double begin_, double end_);
};

// Representação da Cena
class Scene {
private:
    Segment* seg;
    // capacidade da cena
    int capacity;
    //tamanho da cena
    int size;
    //tempo de cena
    int time; 

public:
    //Construtores e destrutores 
    Scene(int capacity = 10);
    ~Scene();

    //modifica o tempo de cena
    void settime(int time_);
    // ve o tempo de cena
    int gettime() const;

    //adiciona Cena
    bool add(const Segment& seg);
    //pega o tamanho da cena
    int getsize() const;
    //Operador auxiliar
    Segment& operator[](int idposition_x);

    //limpa
    void clean();
};

#endif // CENA_HPP