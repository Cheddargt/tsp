/* ALUNOS */
/* GUSTAVO HENRIQUE ZENI - RA: 1985370 */
/* IANCA POLIZELO - RA: 1985388 */
/* VITOR GABRIEL ANDRADE TEIXEIRA - RA: 1655655 */

#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;


struct vertice
{
    double x, y;
    bool visitado;
    double custo;
    int ant;
    vector <int> adjs;
    vector <vertice> conexoes;
};

//Fun��o que calcula a dist�ncia eucliana entre dois pontos
double calcular_distancia(vertice u, vertice v)
{
    double d;
    d = sqrt(pow((u.x - v.x),2)+pow((u.y - v.y),2));
    return(d);
}

/*
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
    Lista(vertice* v) // Construtora c par�metro
    {
        // CHECAR
        topo = v;
        fim = topo;
    }
    ~Lista() {};

};
*/

/*
void copiar_vertice(vertice* v, vertice* u)
{
    u->x = v->x,
    u->y = v->y;
    u->visitado = v->visitado;
    u->custo = v->custo;
    u->prox = v->prox;
}*/



int main () {
/*
int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erro ao ler o arquivo\n");
        return 0;
    }
*/

    /*
    //Start no tempo de execu��o
    clock_t start_tsp, end_tsp;
    float cpu_time_clo;

    //Inicia o tempo de execu��o
    start_tsp = clock();
    */

    //Abrir o arquivo
    //FILE *in=fopen(argv[1],"r");

    /* PARA DEBUG */
    FILE *in=fopen("input.txt","r");

    int num_pontos = 0;

    fscanf(in, "%d", &num_pontos);

    vector<vertice> G;

    // grava os pontos em G
    for (int i = 0; i < num_pontos; i++)
    {
        vertice v;
        double x, y;
        fscanf(in, "%lf %lf", &x, &y);
        //cout << "x: " << x << " y: " << y << endl;
        v.x = x;
        v.y = y;
        v.custo = INT_MAX;
        v.visitado = false;
        v.ant = -1;
        //v.adjs.push_back();
        G.push_back(v);
    }

    //Fechar o arquivo
    fclose(in);

    /*
    for (int i = 0; i < G.size(); i++)
    {
        cout << (G[i].topo)->x << ' ' << (G[i].topo)->y << endl;
    }
    */


    // Preencher as listas de G calculando o custo de G[i] at� cada um
    // Criar o grafo completo
    /*for (int i = 0; i < G.size(); i++)
    {
        for (int j = 0; j < G.size(); j++)
        {
            if (i != j) {
                G[i].AdicionaFim(G[j].topo);
            }
        }
    }*/

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

    //COME�O DO PRIM
    vector<vertice> T;
    G[0].custo = 0;
    int visitados = 0;

    while (visitados < num_pontos)
    {
        double menor_custo = INT_MAX;
        int closest_vertice = -1;
        int u;


        for(int i=0; i<num_pontos;i++)
        {
            if(G[i].custo < menor_custo && G[i].visitado == false)
            {
                u = i;
                menor_custo = G[i].custo;
            }
        }

        //if (G[u].custo > 0)
        //{
        //    G[u].ant = v;
        //}

        G[u].visitado = true;
        //if (u != 0)
        //{
        //    T[T[u].ant].adjs.push_back(u);

        //}
        cout << G[u].x << " " << G[u].y << " visitado. último u: " << G[u].ant << endl;
        T.push_back(G[u]);


        // atualiza as distâncias referente ao G[u] atual, apenas as menores
        for(int i=0; i<num_pontos; i++)
        {
            double dist = calcular_distancia(G[u], G[i]);
            if (dist < G[i].custo)
            {
                G[i].custo = dist;
                if (u == 0)
                {
                    G[i].ant = 0;
                } else
                {
                    G[i].ant = num_pontos - u;
                    //G[G[i].ant].adjs.push_back(i);
                }

            }
        }

        visitados++;
    }

    //A arvore do prim está sem as arestas ainda, tem que arrumar um jeito de fazer as aresta pra fazer a busca em profundidade

    for (int i = num_pontos-1; i >= 0; i--)
    {
        if (T[i].ant != -1)
        {
            (T[T[i].ant].adjs).push_back(i);
            (T[i].adjs).push_back(T[i].ant);
        }

    }

    vector<vertice> V;


    // busca em profundidade
    for (int i = 0; i < T.size(); i++)
    {
        if (i == 0)
        {
            T[i].visitado = false;
            V.push_back(T[i]);
            V[i].ant = -1;
        }

        for (int j = 0; j < T[i].adjs.size(); j++)
        {
            // fingir que true == false pra visitar os visitados, "desvisitando" eles
            if (T[T[i].adjs[j]].visitado == true) // visita
            {
                T[T[i].adjs[j]].visitado = false;
                V.push_back(T[T[i].adjs[j]]);
            }
        }
    }

    // imprimir

    for (int i = 0; i < T.size(); i++)
    {
        cout << "[" << i << "] " << "x: " << T[i].x << " y: " << T[i].y << " custo: " << T[i].custo << " ant: "<< T[i].ant << endl;
        cout << "adjs: ";

        for (int j = 0; j < T[i].adjs.size(); j++)
        {
            cout << T[i].adjs[j] << " ";
        }

        cout << endl;
    }

    // imprimir

    for (int i = 0; i < V.size(); i++)
    {
        cout << "[" << i << "] " << "x: " << V[i].x << " y: " << V[i].y << " custo: " << V[i].custo << " ant: "<< V[i].ant << endl;
    }





/*
    for (int i = num_pontos; i >= 0; i--)
    {
        cout << "" << endl;
        cout << T[i].x << " " << T[i].y << endl;
        if (i != 0){
        cout << T[T[i].ant].x << " " << T[T[i].ant].y << endl;
        }
        cout << endl;
    }

*/



    /* -------------------------------------------------------------------- */

    //Parar tempo de execu��o
    /*
    end_tsp = clock();
    cpu_time_clo = ((float) (end_tsp - start_tsp)) / CLOCKS_PER_SEC;
    */

    return 0;
}
