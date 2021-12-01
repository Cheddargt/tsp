/* ALUNOS */
/* GUSTAVO HENRIQUE ZENI - RA: 1985370 */
/* IANCA POLIZELO - RA: 1985388 */
/* VITOR GABRIEL ANDRADE TEIXEIRA - RA: 1655655 */

/*
    |Este código irá calcular uma aproximação para o problema do caixeiro viajante, em que temos que passar por todos os vértices em um grafo, sem repetí-los, e voltar para o vértice inicial pelo menor caminho possível.
    |Chegar a um custo exato é inviável computacionalmente falando, então se faz necessário abrir mão da exatidão para ganhar em performance.
    |
    |Inicialmente recebemos um conjunto de pontos, que serão os vértices, e devemos realizar 3 passos:
    |1) Computar um grafo completo, ou seja, todos os vértices tem arestas para todos os outros vértices.
    |2) Construir a árvore geradora mínima para este grafo através do algoritmo de Prim.
    |3) Fazer uma busca em profundidade, começando do mesmo vértice iniciado no algoritmo Prim.
    |Por último, então, calculamos os custos de um vértice para outro seguindo a ordem encontrada na busca em profundidade.
    |
    |Para que o nosso código ficasse ainda mais eficiente, eliminação a criação do grafo completo explicito, pois, como sabemos que um vértice tem aresta para todos os demais, podemos começar direto do Prim já com isso em mente.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <time.h>

using namespace std;


/*Aqui é a estrutura utilizada para representar noss vértice:
    |x, y: coordenadas do ponto
    |*/

struct vertice
{
    double x, y;
    bool visitado;
    double custo;
    int ant;
    vector <int> adjs;
    vector <vertice> conexoes;
};

//Funções que calcula a distância eucliana entre dois pontos
double calcular_distancia(vertice u, vertice v)
{
    double d;
    d = sqrt(pow((u.x - v.x),2)+pow((u.y - v.y),2));
    return(d);
}

int main () {

/*int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erro ao ler o arquivo\n");
        return 0;
    }*/


    //Start no tempo de execução
    clock_t start_tsp, end_tsp;
    float cpu_time_clo;

    //Inicia o tempo de execução
    start_tsp = clock();


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
        //cout << G[u].x << " " << G[u].y << " visitado. ultimo u: " << G[u].ant << endl;
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

    FILE *tree = fopen("tree.txt", "w");
    for (int i = num_pontos-1; i >= 0; i--)
    {
        if (T[i].ant != -1)
        {
            (T[T[i].ant].adjs).push_back(i);
            fprintf(tree, "%.0lf %.0lf\n", T[T[i].ant].x, T[T[i].ant].y);
            (T[i].adjs).push_back(T[i].ant);
            fprintf(tree, "%.0lf %.0lf\n", T[i].x, T[i].y);
            //TO-DO: APAGAR ESTA LINHA \/
            fprintf(tree, "\n");
        }

    }

    /*FILE *tree = fopen("tree.txt", "w");
    for(int i=0; i<num_pontos;i++)
    {
        for(int j=0; j<T[j].adjs.size(); j++)
        {
            fprintf(tree, "adjs: %d\n", T[j].adjs.size());
            fprintf(tree, "%.0lf %.0lf\n", T[i].x, T[i].y);
            fprintf(tree, "%.0lf %.0lf\n", T[T[i].adjs[j]].x, T[T[i].adjs[j]].y);
        }
    }
    fclose(tree);*/

    vector<vertice> V;
    // busca em profundidade
    //FILE *tree = fopen("tree.txt", "w");

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
                //if(i != 0)
                //{
                 //   fprintf(tree, "%.0lf %.0lf\n", T[T[j].ant].x, T[T[j].ant].y);
                //    fprintf(tree, "%.0lf %.0lf\n", T[j].x, T[j].y);
               // }

            }
        }
    }
    //fclose(tree);

    // imprimir

    /*
    for (int i = 0; i < T.size(); i++)
    {
        cout << "[" << i << "] " << "x: " << T[i].x << " y: " << T[i].y << " custo: " << T[i].custo << " ant: "<< T[i].ant << endl;
        cout << "adjs: ";

        for (int j = 0; j < T[i].adjs.size(); j++)
        {
            cout << T[i].adjs[j] << " ";
        }

        cout << endl;
    }*/

    // imprimir

    /*
    for (int i = 0; i < V.size(); i++)
    {
        cout << "[" << i << "] " << "x: " << V[i].x << " y: " << V[i].y << " custo: " << V[i].custo << " ant: "<< V[i].ant << endl;
    }
    */


    double custo_ciclo = 0;
    //Agora vamos calcular o custo do ciclo
    for(int i = 0; i < num_pontos-1; i++)
    {
        custo_ciclo = custo_ciclo + calcular_distancia(V[i], V[i+1]);
    }
    custo_ciclo = custo_ciclo + calcular_distancia(V[num_pontos-1], V[0]);

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

    end_tsp = clock();
    cpu_time_clo = ((float) (end_tsp - start_tsp)) / CLOCKS_PER_SEC;

    cout << cpu_time_clo << " " << custo_ciclo << endl;

    //Agora temos que salvar a AGM chamada
    /*FILE *tree = fopen("tree.txt", "w");
    for(int i=0; i<num_pontos;i++)
    {
        for(int j=0; j<T[j].adjs.size(); j++)
        {
            fprintf(tree, "adjs: %d\n", T[j].adjs.size());
            fprintf(tree, "%.0lf %.0lf\n", T[i].x, T[i].y);
            fprintf(tree, "%.0lf %.0lf\n", T[T[i].adjs[j]].x, T[T[i].adjs[j]].y);
        }
    }

    fclose(tree);*/

    //Agora salva o ciclo
    FILE *cycle = fopen("cycle.txt", "w");
    for(int i = 0; i < num_pontos; i++)
    {
        fprintf(cycle, "%.0lf %.0lf\n", V[i].x, V[i].y);
    }
    fprintf(cycle, "%.0lf %.0lf\n", V[0].x, V[0].y);

    fclose(cycle);

    return 0;
}
