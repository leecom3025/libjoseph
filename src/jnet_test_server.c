#include "include/libjoseph.h"

int main (int argc, char* argv[]) {
  struct Jsocket *sck;
  int port = 30331;
  
  if (libj_net_init(&sck, JNET_TCP) < 0 )
    JLE("libj_net_init");
  if (libj_net_prep(&sck, JNET_SERVER, &port, NULL) < 0)
    JLE("libj_net_prep");
  char *msg;

  while (1) {
    if (libj_net_recv(&sck, &msg, 255) < 0)
      JLE("libj_net_recv");
    printf("%s\n", msg);
    if (libj_net_send(&sck, &msg) < 0)
      JLE("libj_net_send");
  }
  
  if (libj_net_done(&sck) < 0)
    JLE("libj_net_done");

  return 0;
}
