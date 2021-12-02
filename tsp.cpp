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
    |visitado: uma flag que sabermos se já passamos por ess vértice
    |custo: distância entre o vértice e o adjacente dele
    |ant: guarda o adjacente que foi visitado antes dele
    |adjs: é um vetor com todos os vértices adjacentes ao vértice em questão

    Essa struct será usada em vetores para montar o grafo
*/
struct vertice
{
    double x, y;
    bool visitado;
    double custo;
    int ant;
    vector <int> adjs;
};
/*
Função para calcular a distância eucliana entre dois pontos, que será o custo
 |Entradas: dois vértices para o cálculo
 |Saída: retorna a distância entre os dois pontos
*/
double calcular_distancia(vertice u, vertice v)
{
    double d;
    d = sqrt(pow((u.x - v.x),2)+pow((u.y - v.y),2));
    return(d);
}


int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erro ao ler o arquivo\n");
        return 0;
    }


    //Start no tempo de execução
    clock_t start_tsp, end_tsp;
    float cpu_time_clo;
    start_tsp = clock();


    //Abrir o arquivo
    FILE *in=fopen(argv[1],"r");

    /* PARA DEBUG */
    //FILE *in=fopen("input.txt","r");

    //Aqui iremos ler o arquivo em txt e gravar em um vector de vértices
    // Iniciamos os custos com infinito, pois no algoritmo de Prim devemos selecionar o melhor em comparações aos depois
    int num_pontos = 0;

    fscanf(in, "%d", &num_pontos);

    vector<vertice> G; //O vetor G é o nosso grafo

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



    //ALGORITMO DO PRIM:

    /*O primeiro passo é fazer a nossa escolha gulosa de vértice para começar
      |Escolha gulosa: primeiro vértice no vetor de vértices, ou seja, vértice com índice 0
      | iniciamos o custo dele como zero, pois será o que irá comparar com os demais
      |
      |T: Árvore Geradora Mínima
      |Visitados: será nosso iterador do while do Prim, pois quando todos já tiverem sido visitados, então acabou os vértices
      |menor_custo: guarda a aresta com melhor custo daquele vértice.
      |u: guarda o índice em que o vértice de menor custo foi achado no vetor G(grafo)
    */
    vector<vertice> T;
    G[0].custo = 0;
    int visitados = 0;

    while (visitados < num_pontos)
    {
        double menor_custo = INT_MAX;
        int u;

        /*
        |Aqui, iremos comparar o custo do vértice i com todos os demais e pegar o menor.
        |Importante: Como já sabemos que grafo tem que ser completo, então a verificação
        |das distâncias do vértice i deve ser feita com todos os demais.
        |isso é uma característica do problema do caxeiro viajante. Se
        |fosse outro problema, não é garantido o fato de ser um grafo completo,
        |então a comparação deveria ser feita apenas com os adjacentes.
        */
        for(int i=0; i<num_pontos;i++)
        {
            if(G[i].custo < menor_custo && G[i].visitado == false)
            {
                u = i;
                menor_custo = G[i].custo;
            }
        }

        //Então, quando achamos o menor custo, adicionamos esse vértice na árvore T e marcamos o vértice como visitado.
        G[u].visitado = true;
        T.push_back(G[u]);


        // Atualizamos os custos dos vértices adjacentes ao vértice que foi adicionado na árvore T
        //Também salvamos aqui o vértice anteriormente visitado.
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
                }

            }
        }

        visitados++;
    }

    /*
    | Durante o algoritmo do Prim, fomos apenas salvando o vértice anterior, logo, do modo como a estrutura está, não conseguiremos fazer a busca em profundidade
    | Então, percorremos a árvore T de trás para frente, verificamos qual é o anterior do vértice i e adicionamos o vértice i no vetor de adjacentes do vértice anterior ao i.
    | Assim, conseguimos montar a árvore com suas aresta devidamente guardadas.
    |
    | Aproveitamos esse momento também para gravar a AGM em um arquivo tree.txt que é uma dos requisitos do trabalho
    */

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
            //fprintf(tree, "\n");
        }

    }


    //Agora iniciaremos a Busca em Profundidade
    /*
    | V: vetor que irá conter a ordem da busca em profundidade.
    |
    | Devemos começar a busca em profundidade do mesmo vértice que fizemos a escolha gulosa no algoritmo do Prim.
    | Então, começamos salvando o primeiro vértice da árvore.
    | Como já havíamos percorrido os vértices uma vez para a árvore, marcamos quando um vértice era visita. Agora, devemos visitar novamente,
    | porém a flag visitado já está ativada, então, consideramos true como sendo false e false como sendo true.
    |
    | Depois percorremos todos os adjacentes possíveis do vértice que foi adicionado anteriormente em V. Antes chegar ao final, voltamos uma posição
    | e percorremos os adjacentes deste novo vértice.
    |
    | Importante colocar que o rótulo que devemos gravar nos vértices será o índice do vetor V, ou seja, o vetor está ordenado através do rótulo.
    */
    vector<vertice> V;

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


    //Agora vamos calcular o custo do ciclo

    /*
    | Para calcular o custo total do ciclo, devemos calcular a distância entre os vértices seguindo a ordem
    | estabelecida através da busca em profundidade. E ao final, também é necessário calcular a distância entre
    | o último vértice e o primeiro, assim fechando o ciclo.
    */
    double custo_ciclo = 0;

    for(int i = 0; i < num_pontos-1; i++)
    {
        custo_ciclo = custo_ciclo + calcular_distancia(V[i], V[i+1]);
    }
    custo_ciclo = custo_ciclo + calcular_distancia(V[num_pontos-1], V[0]);



    /* -------------------------------------------------------------------- */

    //Parar tempo de execução

    end_tsp = clock();
    cpu_time_clo = ((float) (end_tsp - start_tsp)) / CLOCKS_PER_SEC;

    //Saída no terminal
    printf("%.6lf %.6lf\n", cpu_time_clo, custo_ciclo);


    //Agora salvamos o arquivo cycle.txt com a ordem dos vértices que formam o ciclo final
    FILE *cycle = fopen("cycle.txt", "w");
    for(int i = 0; i < num_pontos; i++)
    {
        fprintf(cycle, "%.0lf %.0lf\n", V[i].x, V[i].y);
    }
    fprintf(cycle, "%.0lf %.0lf\n", V[0].x, V[0].y);

    fclose(cycle);

    return 0;
}
