#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>     /* getenv */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <linux/tcp.h>
#include "include/joseph_perf.h"

#ifndef SOL_TCP // I know... this is not an elegant way to do
  #define SOL_TCP 6
#endif

#define EC2   "52.11.103.50"
#define UG    "143.215.131.33"

int main (int argc, char* argv[]) {
  /* char *msg = "TEST SUCCESS"; */
  char *addr, *msg, *msg_ptr;
	int i, sck = 0, port = 30331, period = 200000;
  ssize_t size = 0;
  FILE *pFile;
  struct stat st;
  struct sockaddr_in s_addr;

  addr = getenv("singleton15");
  if (addr == NULL) 
    addr = EC2;
  printf("EC2 addr: %s\n", addr);

  stat("test/data.dat", &st);
  size = st.st_size;
  printf("File size: %d\n", size);

  pFile = fopen("test/data.dat", "r");
  if (pFile == NULL) perror ("Wooooops");

  msg = (char*) malloc (size);
  if (!msg) perror("Woops msg");
  msg_ptr = (char*) malloc(size + sizeof (int32_t));
  if (!msg_ptr) perror("Woooops");

  if (fread(msg, 1, size, pFile) < 0) printf("failed to read");
  fclose(pFile);
  
  sck = socket(AF_INET, SOCK_STREAM, 0);
  if (!sck) perror("errrr");

  bzero((char*) &s_addr, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_addr.s_addr = inet_addr(addr);
  s_addr.sin_port = htons(port);

  // MPTCP modification part
  int bg = 1;
  setsockopt(sck, SOL_TCP, MPTCP_CMM_BG, &bg, sizeof(int));
  int big = 1;
  setsockopt(sck, SOL_TCP, MPTCP_CMM_SIZE, &big, sizeof(int));

  if (connect(sck, (struct sockaddr*)(&s_addr), sizeof(s_addr)) < 0)
    perror("connection failed");

  for (i=0; ; i++) {
    sprintf(msg_ptr, "%s - %d", msg, i);
    int ret = 0;
    size_t std = size;
    size_t sent = 0;
    int buf = 150000;
    
    libj_perf_start();
    while (sent < std) {
      if ( ( ret = write(sck, (char*)(msg_ptr+sent), buf)) < 0) 
        perror ("woops write error");
      sent += ret;
      /* printf("sent-%d: %d <? %zu\n",i, sent, std); */
    }
    libj_perf_stop();
    
    /* ret = sent = 0; */
    /* while (sent < std) { */ 
    /*   if ( (ret = read(sck, (char*)(msg_ptr+sent), buf)) < 0) */
    /*     perror ("woops read error"); */
    /*   sent += ret; */
    /*   printf("recv-%d: %d\n", i, sent); */
    /* } */
    printf("Done: %d [taken: %s]\n", i, libj_perf_time());
    usleep(period);
  }

  close(sck);
  free(msg_ptr);
  free(msg);

  return 0;
}
