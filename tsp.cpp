/* ALUNOS */
/* GUSTAVO HENRIQUE ZENI - RA: 1985370 */
/* IANCA POLIZELO - RA: 1985388 */
/* VITOR GABRIEL ANDRADE TEIXEIRA - RA: 1655655 */

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct vertice
{
    double x, y;
    bool visitado;
    double custo;
    vertice *prox;
};

//Função que calcula a distância eucliana entre dois pontos
double calcular_distancia(vertice* u, vertice* v)
{
    double d;
    d = sqrt(pow((u->x - v->x),2)+pow((u->y - v->y),2));
    return(d);
}

class Lista
{

public:
    vertice* topo;
    vertice* fim;
    void RemoveInicio();
    void RemoveFim();
    AdicionaFim(vertice* novo)
    {
        vertice* v = new vertice;
        v->x = novo->x;
        v->y = novo->y;
        v->visitado = novo->visitado;
        v->custo = novo->custo;
        v->prox = nullptr; //inicializada

        if (topo == nullptr)
        {
            // v->ant = nullptr;
            topo = v;
            fim = v;
        }
        else
        {
            fim->prox = v;
            fim = v;
            v->custo = calcular_distancia(topo, novo);
        }
    }
    Lista () //Construtora
    {
        topo = nullptr;
        fim = topo;
    }
    Lista(vertice* v) // Construtora c parâmetro
    {
        // CHECAR
        topo = v;
        fim = topo;
    }
    ~Lista() {};

};

copiar_vertice(vertice* v, vertice* u)
{
    u->x = v->x,
    u->y = v->y;
    u->visitado = v->visitado;
    u->custo = v->custo;
    u->prox = v->prox;
}



int main () {
/*
int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erro ao ler o arquivo\n");
        return 0;
    }
*/

    /*
    //Start no tempo de execução
    clock_t start_tsp, end_tsp;
    float cpu_time_clo;

    //Inicia o tempo de execução
    start_tsp = clock();
    */

    //Abrir o arquivo
    //FILE *in=fopen(argv[1],"r");

    /* PARA DEBUG */
    FILE *in=fopen("input.txt","r");

    int num_pontos = 0;

    fscanf(in, "%d", &num_pontos);

    vector<Lista> G;

    for (int i = 0; i < num_pontos; i++)
    {
        vertice *v = new vertice;
        double x, y;
        fscanf(in, "%lf %lf", &x, &y);
        //cout << "x: " << x << " y: " << y << endl;
        v->x = x;
        v->y = y;
        v->custo = 0;
        v->visitado = false;
        v->prox = nullptr;
        Lista lista(v);
        G.push_back(lista);
    }

    //Fechar o arquivo
    fclose(in);

    for (int i = 0; i < G.size(); i++)
    {
        //cout << (G[i].topo)->x << ' ' << (G[i].topo)->y << endl;
    }


    // Preencher as listas de G calculando o custo de G[i] até cada um
    // Criar o grafo completo
    for (int i = 0; i < G.size(); i++)
    {
        for (int j = 0; j < G.size(); j++)
        {
            if (i != j) {
                G[i].AdicionaFim(G[j].topo);
            }
        }
    }

    // imprimir
    /*
    for (int i = 0; i < G.size(); i++)
    {
        vertice* v = G[i].topo;
        for (int j = 0; j < G.size(); j++)
        {
            //cout << "x: " << v->x << " y: " << v->y << " custo: " << v->custo << endl;
            v = v->prox;
        }
        //cout << endl;
    }
    */

    // gerar T
    vector<Lista> T;

    G[0].topo->visitado = true;
    T.push_back(G[0]);

    int visitados = 0;

    // enquanto todos não forem visitados e adicionados à matriz de visitados
    while (visitados < num_pontos)
    {
        double menor_custo = 9999999999999999999;
        vertice* v = new vertice; // vértice a ser guardado
        vertice* aux = new vertice; // vértice "identador"
        aux = G[0].topo;

        // verificar todas as arestas disponíveis
        for (int i = 0; i < num_pontos; i++)
        {
            cout << G[i].topo->x << " " << G[i].topo->y << " " << G[i].topo->visitado << endl;
            aux = G[i].topo; // sempre começar do primeiro
            for (int j = 0; j < num_pontos; j++)
            {
                if (!aux->visitado)
                {
                    if (aux->custo != 0)
                    {
                        if (aux->custo < menor_custo)
                        {
                            menor_custo = aux->custo;
                            v = aux;
                        }
                    }
                }
                if (aux->prox != nullptr) {
                    aux = aux->prox;
                }
            }
        }
        v->visitado = true;
        vertice* u = new vertice;
        copiar_vertice(v, u);
        Lista lista(u);
        T.push_back(lista);
        visitados++;
    }



    // imprimir
    for (int i = 0; i < T.size(); i++)
    {
        cout << "[" << i << "] " << "x: " << T[i].topo->x << " y: " << T[i].topo->y << " custo: " << T[i].topo->custo << endl;
    }



    /* -------------------------------------------------------------------- */

    //Parar tempo de execução
    /*
    end_tsp = clock();
    cpu_time_clo = ((float) (end_tsp - start_tsp)) / CLOCKS_PER_SEC;
    */

    return 0;
}
