#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

#include <stdio.h>
#include <stdlib.h>

struct edge {
   int from, to, weight;
   struct edge* link;
};
struct graph{
   int V, E;
   struct edge* edges;
};
struct edge* create_edge(int from, int to, int weight) {
   struct edge* new = malloc(sizeof(struct edge));
   new->from = from;
   new->to = to;
   new->weight = weight;
   new->link = NULL;
   return new;
}
struct graph* create_graph(int V, int E) {
   struct graph* new = malloc(sizeof(struct graph));
   new->E = E;
   new->V = V;
   new->edges = NULL;
   return new;
}
void readfile(void) {
   FILE* fp;
   struct edge* new;
   int weight, vertex_cnt;
   struct graph* G;
   
   if(!(fp = fopen(INPUT_FILENAME, "r"))) {
      fprintf(stderr, "error: fopen failed to read\n");
      exit(1);
   }

   fscanf(fp, " %d", &vertex_cnt);

   //visited = calloc(vertex_cnt, sizeof(int));
   G = create_graph(vertex_cnt, 0);

   for(int i=0 ; i<vertex_cnt ; i++)
      graph[i] = NULL;

   for(int i=0 ; i<vertex_cnt ; i++) {
      for(int j=0 ; j<vertex_cnt ; j++) {
         fscanf(fp, " %d", &weight);
         if(weight != -1) {
            new = malloc(sizeof(struct _node));
            new->vertex = j;
            new->weight = weight;
            new->link = graph[i];
            graph[i] = new;
            new = NULL;
         }
      }
   }
   fclose(fp);
}
