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

#ifdef X86
  #include "../include/joseph_net.h"
  #include <linux/tcp.h>
#else
  #include "joseph_net.h"
#endif

#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif

/*
 * flow:
 *  struct Jsocket *sck;
 *  libj_net_init(&sck, JNET_[TCP or UDP])
 *  libj_net_prep(&sck, JNET_[SERVER or CLIENT], port, target addr)
 *  libj_net_send/recv
 *  //do more
 *  libj_net_done
 */ 

/* 
 *   
 */
int libj_net_init(struct Jsocket **sck, int type) {
	if (sck == NULL || type < 0)
		return -1;

  int socket_type;
  struct Jsocket *ptr;

  ptr = malloc(sizeof(Jsocket));
  ptr->type = type;

	if (ptr->type == JNET_TCP)
		socket_type = SOCK_STREAM;
	else if (ptr->type == JNET_UDP)
		socket_type = SOCK_DGRAM;

  if ((ptr->socket = socket(AF_INET, socket_type, 0)) == -1)
    JNET_ERR(ptr);

	setsockopt(ptr->socket, SOL_SOCKET, SO_REUSEADDR, &(ptr->socket), 
      sizeof(int));

  int bg = 1;
  setsockopt(ptr->socket, SOL_TCP, MPTCP_CMM_BG, &bg, sizeof(int));

  int big = 1;
  setsockopt(ptr->socket, SOL_TCP, MPTCP_CMM_SIZE, &big,
      sizeof(int));

	ptr->si_len = sizeof(struct sockaddr_in);
	memset((void*) &(ptr->si), 0, ptr->si_len);
	(ptr->si).sin_family = AF_INET;

	*sck = ptr;
	return 0;
}

/* 
 *	addr can be NULL for Server
 *  role: server or client
 *  port: desired port
 *  addr: binding addr (default is NULL for server and required for
 *  client)
 * 
 */ 
int libj_net_prep(struct Jsocket **sck, int role, int *port, 
    char *addr) {
	if (sck == NULL || role < 0 || port == NULL || *port < 0)
		return -1;

	struct Jsocket *ptr = *sck;
	ptr->role = role;
	(ptr->si).sin_port = htons(*port);

	if ((ptr->role & JNET_SERVER) && addr == NULL) {
		(ptr->si).sin_addr.s_addr = htonl(INADDR_ANY);
	} else {
		(ptr->si).sin_addr.s_addr = inet_addr(addr);
	}

	if ((role & JNET_SERVER)) {
		if (bind(ptr->socket, (struct sockaddr*)(&(ptr->si)), 
          ptr->si_len) < 0)
			JNET_ERR(ptr);
		if (ptr->type == JNET_TCP) {
			struct sockaddr _client;
			if (listen(ptr->socket, 0xF) < 0) /* it will accept only one client */
				JNET_ERR(ptr);
			if ( (ptr->client = accept(ptr->socket, &_client, 
					(socklen_t*)&(ptr->si_len))) < 0 )
				JNET_ERR(ptr);
		}
	} else if ((role & JNET_CLIENT)) {
		if (ptr->type == JNET_TCP) {
			if (connect(ptr->socket, (struct sockaddr*)(&(ptr->si)), 
				ptr->si_len) < 0) 
				JNET_ERR(ptr);
		}
	}

	return 0;
}

int libj_net_done(struct Jsocket **sck) {
	struct Jsocket *ptr = *sck;

	if (ptr->socket > 0) 
		close(ptr->socket);
	if (ptr->role == JNET_SERVER && ptr->client > 0)
		close(ptr->client);
	if (ptr != NULL)
		free(ptr);
	return 0;
}

int libj_net_send(struct Jsocket **sck, char **msg) {
	if (sck == NULL || msg == NULL)
		return -1;

	struct Jsocket *ptr = *sck;
	int socket = 0;
	if (ptr->role == JNET_CLIENT || ptr->type == JNET_UDP) {
		socket = ptr->socket;
	} else if (ptr->role == JNET_SERVER) {
		socket = ptr->client;
	} else {
		JNET_ERR(ptr);
	}

	struct sockaddr _client;
	size_t _len = strlen(*msg);
  printf(_len);
	switch (ptr->type) {
		case JNET_TCP:
			if (send(socket, *msg, _len, 0) < 0)
				JNET_ERR(ptr);
			break;
		case JNET_UDP:
			if (sendto(socket, *msg, _len, 0, 
            (struct sockaddr*)(&(ptr->si)), ptr->si_len) < 0)
				JNET_ERR(ptr);
			break;
		default:
			JNET_ERR(ptr);
	}

	return 0;
} 


int libj_net_recv(struct Jsocket **sck, char **buffer, size_t len) {
	if (sck == NULL || buffer == NULL || len == 0)
		return -1;

	struct Jsocket *ptr = *sck;
	int socket = 0;
	char *_buf;
	struct sockaddr _client;

	if (ptr->role == JNET_CLIENT || ptr->type == JNET_UDP) 
		socket = ptr->socket;
	else if (ptr->role == JNET_SERVER) 
		socket = ptr->client;
	else
		JNET_ERR(ptr);

	_buf = (char*) malloc(len);
	switch (ptr->type) {
		case JNET_TCP:
      if (recv(socket, _buf, len, 0) < 0)
				JNET_ERR(ptr);
			break;
		case JNET_UDP:
			if (recvfrom(socket, _buf, len, 0, &_client, 
            (socklen_t*)&(ptr->si_len)) < 0)
				JNET_ERR(ptr);
			break;
		default:
			JNET_ERR(ptr);
	}

	*buffer = _buf;
	return 0;
} 
