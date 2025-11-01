#include "../Include/Algoritimo.hpp"
///////////////////////////////////////////PRIMEIRA FUNÇÕ PRINCIAL///////////////////////////////////

//Arvore de pesquisa binaria
int bisearch(interval arr[], int n, double valor) {
    int left = 0, right = n - 1;
    int pos = n; 
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].ini >= valor) {
            pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return pos;
}

// função que adiciona o intervalo de cenas
void addinterval(interval coverd[], int& n_coverd, double ini, double end) {
    // Validação da entrada
    if (ini >= end) {
        return; 
    }

    // Garante precisão dos limites do intervalo (tive que usar -12 pois os outros estavam dando errdo de arredondamento)
    double tolerance = 1e-12;
    ini = ceil(ini * 100000.0) / 100000.0;
    end = floor(end * 100000.0) / 100000.0;

    //Encontra a Posição de inserção com Busca Binária 
    int pos_insercao = bisearch(coverd, n_coverd, ini);

    // Desloca todos os elementos para a direita (com base na inserção anterior)
    for (int i = n_coverd; i > pos_insercao; --i) {
        coverd[i] = coverd[i - 1];
    }

    // Insere o novo intervalo na posição 
    coverd[pos_insercao] = interval(ini, end);
    n_coverd++; 

    // Merge 
    int pos_atual = pos_insercao;

    // Aqui tenta fundir com o vizinho da esquerda
    if (pos_atual > 0 && coverd[pos_atual - 1].end + tolerance >= coverd[pos_atual].ini) {
        // Expande o vizinho da esquerda 
        coverd[pos_atual - 1].end = fmax(coverd[pos_atual - 1].end, coverd[pos_atual].end);
        
        // Remove o intervalo na pos_atual que foi absorvido, deslocando os elementos da direita
        for (int i = pos_atual; i < n_coverd - 1; i++) {
            coverd[i] = coverd[i + 1];
        }
        n_coverd--;
        pos_atual--; 
    }

    // Tenta fundir com os vizinhos da DIREITA 
    while (pos_atual < n_coverd - 1 && coverd[pos_atual].end + tolerance >= coverd[pos_atual + 1].ini) {
        // Expande o intervalo 
        coverd[pos_atual].end = fmax(coverd[pos_atual].end, coverd[pos_atual + 1].end);
        
        // Remove o próximo intervalo que foi absorvido
        for (int i = pos_atual + 1; i < n_coverd - 1; i++) {
            coverd[i] = coverd[i + 1];
        }
        n_coverd--;
    }
}

//////////////////////////////////// SEGUNDA FUNÇÃO PRINCIAL ///////////////////


// Função auxiliar para trocar intervalos 
void swapIntervals(interval& a, interval& b) {
    interval temp = a;
    a = b;
    b = temp;
}

// Função de partição do Quick Sort
int partitionIntervals(interval arr[], int baixo, int alto) {
    double pivo = arr[alto].ini;
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j].ini < pivo) {
            i++;
            swapIntervals(arr[i], arr[j]);
        }
    }
    swapIntervals(arr[i + 1], arr[alto]);
    return (i + 1);
}

// Funçao Quick Sort para os intervalos
void quickSortIntervals(interval arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = partitionIntervals(arr, baixo, alto);
        quickSortIntervals(arr, baixo, pi - 1);
        quickSortIntervals(arr, pi + 1, alto);
    }
}



// Obtém trechos visiveis de objetos
int getvisible(interval coverd[], int n_coverd, double ini, double end, interval visiveis[], int& n_visiveis) {
    n_visiveis = 0;
    double tolerance = 1e-12;

    
    // Cria um array para guardar os intervalos que importam de vdd
    interval temp_cobertos[1000];
    int n_temp = 0;

    for (int i = 0; i < n_coverd; i++) {
        // Ignora intervalos que estão fora da janela 
        if (coverd[i].ini >= end || coverd[i].end <= ini) {
            continue;
        }

        // Proteção 
        if (n_temp >= 1000) {
            break; 
        }

        // Corta o intervalo
        temp_cobertos[n_temp] = coverd[i];
        temp_cobertos[n_temp].ini = fmax(ini, coverd[i].ini);
        temp_cobertos[n_temp].end = fmin(end, coverd[i].end);
        n_temp++;
    }

    if (n_temp == 0) {
        if (end - ini > tolerance) {
            visiveis[n_visiveis++] = interval(ini, end);
        }
        return n_visiveis;
    }

    //Quick sort para ordenar intervalos
    quickSortIntervals(temp_cobertos, 0, n_temp - 1);

    // Merge os intervalos usando pilha ---
    interval pilha[1000];
    int topo = -1;

    pilha[++topo] = temp_cobertos[0]; 

    for (int i = 1; i < n_temp; i++) {
        interval& topo_pilha = pilha[topo];
        interval& atual = temp_cobertos[i];

        if (atual.ini <= topo_pilha.end + tolerance) {
            // faz o merge expandindo o topo da pilha
            topo_pilha.end = fmax(topo_pilha.end, atual.end);
        } else {
            //  adiciona como um novo intervalo na pilha
            pilha[++topo] = atual;
        }
    }

    // Constroi os intervalos visíveis final 
    double ponteiro = ini;

    for (int i = 0; i <= topo; i++) {
        // Proteção
        if (pilha[i].ini - ponteiro > tolerance) {
            visiveis[n_visiveis++] = interval(ponteiro, pilha[i].ini);
        }
        // Avança o ponteiro para o fim do blocker 
        ponteiro = fmax(ponteiro, pilha[i].end);
    }

    // Verifica se há um último trecho visível 
    if (end - ponteiro > tolerance) {
        visiveis[n_visiveis++] = interval(ponteiro, end);
    }

    return n_visiveis;
}

//////////////////////////////////// TERCEIRA FUNÇÃO PRINCIPAL //////////////////////////////////

// Função para trocar dois obj
void swap(Obj& a, Obj& b) {
    Obj temp = a;
    a = b;
    b = temp;
}

// Insertion Sort
void InsertionSort(Obj* arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        Obj temp = arr[i];
        int j = i - 1;
        while (j >= l && arr[j].position_y > temp.position_y) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}



// Função para a mediana de 3
int medianaDe3(Obj* arr, int l, int r) {
    int m = (l + r) / 2;
    if (arr[l].position_y > arr[m].position_y) swap(arr[l], arr[m]);
    if (arr[l].position_y > arr[r].position_y) swap(arr[l], arr[r]);
    if (arr[m].position_y > arr[r].position_y) swap(arr[m], arr[r]);
    
    swap(arr[m], arr[r - 1]);
    return r - 1; 
}

// Quicksort com mediana de 3 e insertion sort
void QuickSort(Obj* arr, int l, int r) {
    if (r - l + 1 <= 10) {
        InsertionSort(arr, l, r);
        return;
    }
    int pivoIdx = medianaDe3(arr, l, r);
    double pivo = arr[pivoIdx].position_y;
    int i = l, j = r - 1;
    while (true) {
        while (arr[++i].position_y < pivo);
        while (arr[--j].position_y > pivo);
        if (i < j)
            swap(arr[i], arr[j]);
        else
            break;
    }
    swap(arr[i], arr[r - 1]); 
    QuickSort(arr, l, i - 1);
    QuickSort(arr, i + 1, r);
}
//Função recursiva de processamento
void processrecur(Obj* Objs, int num_Objs, Scene* Scene,
                                double seg_ini, double seg_fim, int nivel) {
    // Caso base 1: se o segmento for inválido 
    if (seg_fim - seg_ini < 1e-12) {
        return;
    }
    
    //caso base 2:se não tem objetos para considerar 
    if (num_Objs == 0) {
        return;
    }

    //acha o objeto mais próximo
    int obj_mais_proximo = -1;
    double menor_profundidade = 1e9;
    
    for (int i = 0; i < num_Objs; i++) {
        Obj& obj = Objs[i];
        double obj_ini = obj.position_x - obj.width / 2.0;
        double obj_fim = obj.position_x + obj.width / 2.0;
        
        // Verifica condição do objeto
        if (obj_fim > seg_ini && obj_ini < seg_fim) {
            if (obj.position_y < menor_profundidade) {
                menor_profundidade = obj.position_y;
                obj_mais_proximo = i;
            }
        }
    }
    
    //Caso base 3: Se não encontrou objeto 
    if (obj_mais_proximo == -1) {
        return;
    }
    
    // Processa o objeto mais próximo 
    Obj& divisor = Objs[obj_mais_proximo];
    double divisor_ini = divisor.position_x - divisor.width / 2.0;
    double divisor_fim = divisor.position_x + divisor.width / 2.0;

    // Calcula a parte visível 
    double visivel_ini = fmax(seg_ini, divisor_ini);
    double visivel_fim = fmin(seg_fim, divisor_fim);

    if (visivel_fim - visivel_ini > 1e-12) {
        Scene->add(Segment(divisor.id, visivel_ini, visivel_fim));
    }
    
    // prepara lista de objetos restantes
    Obj objetos_sem_atual[100]; 
    int novo_num_objs = 0;
    
    for (int i = 0; i < num_Objs; i++) {
        if (i != obj_mais_proximo) {
            objetos_sem_atual[novo_num_objs++] = Objs[i];
        }
    }
    
    // Resolve os segmentos à esquerda e direita
    if (seg_ini < divisor_ini) {
        processrecur(objetos_sem_atual, novo_num_objs, Scene, 
                                  seg_ini, divisor_ini, nivel + 1);
    }
      
    if (divisor_fim < seg_fim) {
        processrecur(objetos_sem_atual, novo_num_objs, Scene,
                                  divisor_fim, seg_fim, nivel + 1);
    }
}

// Função Principal que gera a cena final
void hiddenscene(Obj* Objs, int num_Objs, Scene* Scene) {
    if (num_Objs == 0) {
        return;
    }

    // Ordenar com quick sort
    QuickSort(Objs, 0, num_Objs - 1);

    //Encontrar extensão total 
    double x_min = Objs[0].position_x - Objs[0].width / 2.0;
    double x_max = Objs[0].position_x + Objs[0].width / 2.0;
    for (int i = 1; i < num_Objs; i++) {
        double obj_ini = Objs[i].position_x - Objs[i].width / 2.0;
        double obj_fim = Objs[i].position_x + Objs[i].width / 2.0;
        x_min = fmin(x_min, obj_ini);
        x_max = fmax(x_max, obj_fim);
    }
    
    // Inicia recursão
    processrecur(Objs, num_Objs, Scene, x_min, x_max, 0);
}