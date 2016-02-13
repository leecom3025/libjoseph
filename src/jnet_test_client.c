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
#define PORT 30332 //small
#define DATA  "test/8kb.dat"

void die(char *msg) {
  printf(msg);
  exit(1);
}

void help() {
  printf ("./program -s -b -l -f [file]\n");
  printf (" - s: if set, role server\n");
  printf (" - b: if set, background\n");
  printf (" - l: if set, big[large] file\n");
  printf (" - f: if arg passed, use file\n");
}

int server(int port, ssize_t len) {
  int ret;
  
  return ret;
}

int send_all(int sck, char* msg, ssize_t size) {
  size_t std = size;
  size_t sent = 0;
  int ret, buf = 150000;

  while (sent < std) {
    if ( (ret = write(sck, (char*)(msg+sent), buf)) < 0)
      perror ("write failed\n");
    sent += ret;
  }

  return sent > std ? 0 : -1;
}

int recv_all(int sck, char* msg, ssize_t size) {
  size_t std = size;
  size_t rcv = 0;
  int ret, buf = 150000;

  while (rcv < std) { 
    if ( (ret = read(sck, (char*)(msg+rcv), buf)) < 0)
      perror("read failed\n");
    rcv += ret;
  }
  
  return rcv > std ? 0 : -1;
}

int main (int argc, char **argv) {
  char *input;
  int c, role = 0; //client(0), server(1)

  char *addr, *msg, *msg_ptr, *file_name = NULL;
	int i, sck = 0, port = PORT, period = 200000;
  ssize_t size = 0;
  FILE *pFile;
  struct stat st;
  struct sockaddr_in s_addr;

  // MPTCP modification part
  int bg = 0; // foreground (0), background (1)
  int big = 0; // small (0), big(1)

  while ((c = getopt(argc, argv, "f:sblhv")) != -1 ) {
    switch(c) {
      case 's':
        role = 1;
        break;
      case 'b':
        bg = 1;
        port = 30331;
        break;
      case 'l':
        big = 1;
        break;
      case 'f':
        file_name = optarg;
        if( access( file_name, F_OK ) < 0) { 
          printf("file: %s does not exit", file_name);
          die("\n");
        } else 
          printf("file %s\n", file_name);
        break;
      default:
        help();
        exit(0);
    }
  }

  if (!role) 
    printf("Role: client\n");
  else
    printf("Role: server\n");

  if (!bg)
    printf("Traffic: foreground\n");
  else
    printf("Traffic: background\n");

  if (!big)
    printf("Size: small\n");
  else
    printf("Size: big\n");

  addr = getenv("singleton15");
  if (addr == NULL) 
    addr = EC2;
  printf("EC2 addr: %s:%d\n", addr, port);

  if (file_name == NULL) 
    file_name = DATA;
  stat(file_name, &st);
  size = st.st_size;
  printf("File size: %d\n", size);

  pFile = fopen(file_name, "r");
  if (pFile == NULL) die("Woooops");

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

  /* mptcp part */
  setsockopt(sck, SOL_TCP, MPTCP_CMM_BG, &bg, sizeof(int));
  setsockopt(sck, SOL_TCP, MPTCP_CMM_SIZE, &big, sizeof(int));

  if (connect(sck, (struct sockaddr*)(&s_addr), sizeof(s_addr)) < 0)
    perror("connection failed");

  int loop = 3000;
  unsigned long total = 0;
  for (i=0; i < loop; i++) {
    sprintf(msg_ptr, "%s - %d", msg, i);
    
    libj_perf_start();
    if (send_all(sck, msg_ptr, size) < 0)
      printf("Woops error\n");
    libj_perf_stop();

    total += libj_perf_time_raw();
    /* printf("Done: %d [taken: %s]\n", i, libj_perf_time()); */
    /* usleep(period); */
  }

  printf("Total: %lu ms per loop\n", total / (unsigned long)loop);

  close(sck);
  free(msg_ptr);
  free(msg);

  return 0;
}
