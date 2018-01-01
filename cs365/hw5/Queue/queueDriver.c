#include <stdio.h>
#include <string.h>
#include "queue.h"

int main() {
  void *myQueue = queue_new(20);
  void *defaultQueue = queue_new(100);
  char cmd[20], value[100];
  char *result;

  while (scanf("%s", cmd) != EOF) {
    if (strcmp(cmd,"enqueue") == 0) {
      scanf("%s", value);
      queue_enqueue(myQueue, strdup(value));
    }
    else if (strcmp(cmd,"dequeue") == 0) {
      result = (char *)queue_dequeue(myQueue);
      queue_enqueue(defaultQueue, result);
      printf("dequeued value = %s\n", result);
    }
    else 
      printf("bad command: %s\n", cmd);
  }
	 
  // print the contents of the two stacks
  printf("*** contents of myQueue ***\n");
  while (!queue_isEmpty(myQueue)) 
    printf("%s\n", (char *)queue_dequeue(myQueue));

  printf("*** contents of defaultQueue ***\n");
  while (!queue_isEmpty(defaultQueue))
     printf("%s\n", (char *)queue_dequeue(defaultQueue));
}
