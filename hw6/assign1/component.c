#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

#include <stdio.h>
#include <stdlib.h>

typedef struct _node* node_pointer;
struct _node {
   int vertex;
   node_pointer link;
};
node_pointer* graph;
int* visited;
int vertex_cnt;
FILE* ofp;

void read_file(void) {
   FILE* fp;
   int tmp;
   node_pointer new;

   if(!(fp = fopen(INPUT_FILENAME, "r"))) {
      fprintf(stderr, "error: fopen failed\n");
      exit(1);
   }

   fscanf(fp, " %d", &vertex_cnt);

   graph = malloc(sizeof(node_pointer)*vertex_cnt);
   visited = calloc(vertex_cnt, sizeof(int));

   for(int i=0 ; i<vertex_cnt ; i++)
      graph[i] = NULL;

   for(int i=0 ; i<vertex_cnt ; i++) {
      for(int j=0 ; j<vertex_cnt ; j++) {
         fscanf(fp, " %d", &tmp);
         if(tmp) {
            new = malloc(sizeof(struct _node));
            new->vertex = j;
            new->link = graph[i];
            graph[i] = new;
            new = NULL;
         }
      }
   }
   fclose(fp);
}
void dfs(int vertex) {
   fprintf(ofp, "%d", vertex);
   visited[vertex] = 1;
   for(node_pointer ptr = graph[vertex] ; ptr ; ptr = ptr->link) {
      if(!visited[ptr->vertex]) {
         fprintf(ofp, " ");
         dfs(ptr->vertex);
      }
   }
}

int main(int argc, const char* argv[]) {
   read_file();
   if(!(ofp = fopen(OUTPUT_FILENAME, "w"))) {
      fprintf(stderr, "error: writing to file failed\n");
      exit(1);
   }
   for(int i=0 ; i<vertex_cnt ; i++) {
      if(!visited[i]) {
         dfs(i);
         fprintf(ofp, "\n");
      }
   }
   fclose(ofp);
   for(int i=0 ; i<vertex_cnt ; i++) {
      for(node_pointer ptr=graph[i] ; ptr ; ptr=ptr->link) {
         free(ptr);
      }
   }
   free(graph);
   free(visited);
   return 0;
}
