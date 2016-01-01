/*
 * Copyright (C) 2015 HyunJong Joseph Lee, Korvo, CERCS, Georgia Tech
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* include */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

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
// #include <bluetooth/bluetooth.h>
// #include <bluetooth/rfcomm.h>

#include "joseph_common.h"

// type of packets
#define JNET_UDP 		        0x1
#define JNET_TCP		        0x2
#define JNET_BL2E		        0x3

// role of program
#define JNET_UNKNOWN	0x0
#define JNET_SERVER 	0x1
#define JNET_CLIENT 	0x2

#define JNET_ERR(x) \
 { \
 	JLE("JNet_Err(%s): %s\n", __FUNCTION__, strerror(errno)); \
 	if (x != NULL) \
 	 	free(x); \
 	return -1; \
 }//

struct Jsocket {
	struct sockaddr_in si;
	size_t si_len;
	// struct sockaddr_rc sr;
	union {
		int socket;
		int client;
	};
	int port;
	int type;
	int role;
} Jsocket;

#ifdef __cplusplus
extern "C" {
#endif
	int libj_net_init(struct Jsocket **, int type);
	int libj_net_prep(struct Jsocket **, int role, int *port, char *addr);
	int libj_net_done(struct Jsocket **);
	int libj_net_send(struct Jsocket **, char **msg);
	int libj_net_recv(struct Jsocket **, char **buf, size_t len);
#ifdef __cplusplus
}
#endif

