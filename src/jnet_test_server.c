#include "include/libjoseph.h"

int main (int argc, char* argv[]) {
  struct Jsocket *sck;
  int port = 30331;
  ssize_t len = 1073741824;
  len += sizeof(int);
  printf ("Get %zu\n", len);
  size_t buf = 150000;
  
  if (libj_net_init(&sck, JNET_TCP) < 0 )
    JLE("libj_net_init");
  if (libj_net_prep(&sck, JNET_SERVER, &port, NULL) < 0)
    JLE("libj_net_prep");
  char *msg;

  msg = (char*) malloc(len);

  size_t rcv = 0;
  int i = 0;
  while(1) {
    size_t ret = 0;
    while (rcv < len) {
      if ((ret = read(sck->socket, (char*)(msg+rcv), buf)) < 0)
        JLE("WOOOOOPs");
      rcv += ret;
      /* printf("rcvd-%d: %zu\n", i, rcv); */
    }

    ret = rcv = 0;
    /* while (rcv < len) { */
    /*   if ((ret = write(sck->socket, (char*)(msg+rcv), buf)) < 0) */
    /*     JLE("write errorrrr\n"); */
    /*   rcv += ret; */
    /*   printf("sent-%d: %zu\n", i, rcv); */
    /* } */
    printf("Done - %d\n", i);
    i++;
  }
  
  if (libj_net_done(&sck) < 0)
    JLE("libj_net_done");

  return 0;
}
