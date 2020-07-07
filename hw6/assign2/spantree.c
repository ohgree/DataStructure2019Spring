#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

#include <stdio.h>
#include <stdlib.h>

struct edge {
   int from;
   int to;
   int weight;
};
typedef struct _node* node_pointer;
struct _node {
   int vertex;
   int weight;
   node_pointer link;
};
node_pointer* graph;
node_pointer* mst;

int vertex_cnt;
int edge_cnt;
int* visited;
FILE* ofp;

void readfile(void) {
   FILE* fp;
   node_pointer new;
   int weight;
   
   if(!(fp = fopen(INPUT_FILENAME, "r"))) {
      fprintf(stderr, "error: fopen failed to read\n");
      exit(1);
   }

   fscanf(fp, " %d", &vertex_cnt);

   graph = calloc(vertex_cnt, sizeof(node_pointer));
   visited = calloc(vertex_cnt, sizeof(int));

   //reading upper triangle only
   edge_cnt = 0;
   for(int i=0 ; i<vertex_cnt ; i++) {
      for(int j=0 ; j<vertex_cnt ; j++) {
         fscanf(fp, " %d", &weight);
         if(weight != -1) {
            if(i > j) continue;
            edge_cnt++;
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

void sort_edges(struct edge** edges, int n) {
   struct edge* tmp;
   for(int i=0 ; i<n-1 ; i++) {
      for(int j=i ; j<n ; j++) {
         if(edges[i]->weight > edges[j]->weight) {
            tmp = edges[j];
            edges[j] = edges[i];
            edges[i] = tmp;
         }
      }
   }
}
int sfind(int parent[], int i) {
   while(parent[i] >= 0)
      i=parent[i];
   return i;
}
void sunion(int parent[], int i, int j) {
   parent[i] = j;
}

int cost = 0;
void create_mst(void) {
   struct edge** edges;
   int x, y, edge_idx = 0;
   int* parent;
   edges = malloc(sizeof(struct edge*)*edge_cnt);
   for(int i=0 ; i<vertex_cnt ; i++) {
      for(node_pointer ptr = graph[i] ; ptr ; ptr = ptr->link) {
         edges[edge_idx] = malloc(sizeof(struct edge));
         edges[edge_idx]->from = i;
         edges[edge_idx]->to = ptr->vertex;
         edges[edge_idx]->weight = ptr->weight;
         edge_idx++;
      }
   }
   sort_edges(edges, edge_cnt);

   mst = calloc(vertex_cnt, sizeof(node_pointer*));
   parent = malloc(sizeof(int)*vertex_cnt);
   for(int i=0 ; i<vertex_cnt ; i++) {
      parent[i] = -1;
   }
   edge_idx = 0;
   while(edge_idx < edge_cnt) {
      struct edge* next = edges[edge_idx++];
      x = sfind(parent, next->from);
      y = sfind(parent, next->to);
      if(x != y) {
         node_pointer new;
         new = malloc(sizeof(struct _node));
         new->link = mst[next->from];
         new->vertex = next->to;
         new->weight = next->weight;
         mst[next->from] = new;
         //union(subsets, x, y);
         new = malloc(sizeof(struct _node));
         new->link = mst[next->to];
         new->vertex = next->from;
         new->weight = next->weight;
         mst[next->to] = new;
         sunion(parent, x, y);
         cost += next->weight;
      }
   }
   for(int i=0 ; i<edge_cnt ; i++) {
      free(edges[i]);
   }
   free(edges);
   free(parent);   
}
void dfs(int vertex) {
   fprintf(ofp, "%d", vertex);
   visited[vertex] = 1;
   for(node_pointer ptr = mst[vertex] ; ptr ; ptr = ptr->link) {
      if(!visited[ptr->vertex]) {
         fprintf(ofp, " ");
         dfs(ptr->vertex);
      }
   }
}

int main(int argc, const char* argv[]) {
   readfile();
   create_mst();
   
   if(!(ofp = fopen(OUTPUT_FILENAME, "w"))) {
      fprintf(stderr, "error: fopen cannot write to file\n");
      exit(1);
   }

   visited = calloc(vertex_cnt, sizeof(int));
   for(int i=0 ; i<vertex_cnt ; i++) {
      if(!visited[i]) {
         dfs(i);
         fprintf(ofp, "\n");
      }
   }
   fprintf(ofp, "%d\n", cost);
   fclose(ofp);

   for(int i=0 ; i<vertex_cnt ; i++) {
      free(graph[i]);
      free(mst[i]);
   }
   free(graph);
   free(mst);
   return 0;
}
