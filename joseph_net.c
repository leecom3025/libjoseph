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

#include "joseph_net.h"

/* 
 * 
 */
int jnet_init(struct jsocket **sck, int type) {
	struct jsocket *ptr = malloc(sizeof(jsocket));
	int socket_type = 0;
	if ((type == JNET_TCP))
		socket_type = SOCK_STREAM;
	else if ((type == JNET_UDP))
		socket_type = SOCK_DGRAM;

	if (((ptr->socket) = socket(AF_INET, socket_type, 0)) == -1) 
		JNET_ERR(ptr);

	memset(&(ptr->si), 0, sizeof(ptr->si));
	(ptr->si).sin_family = AF_INET;

	*sck = ptr;
	return 0;
}


int jnet_prep(struct jsocket **sck, int role, int *port, char *addr) {
	struct jsocket *ptr;
	ptr = *sck;

	JFD("port assigning");
	JLD("%d", ptr->socket);
	JLD("%d", (ptr->si).sin_port);
	int _port = *port;
	JLD("%d", _port);

	(ptr->si).sin_port = htons(_port);
	if ((role & JNET_SERVER)) {
		(ptr->si).sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else if ((role & JNET_CLIENT)) {
		(ptr->si).sin_addr.s_addr = inet_addr(addr);
	}

	if ((role & JNET_SERVER)) {
		if (bind(ptr->socket, (struct sockaddr*)(&(ptr->si)), sizeof(ptr->si) < 0)) 
			JNET_ERR(ptr);
		if (listen(ptr->socket, 0xFF) < 0) 
			JNET_ERR(ptr);


    // if ( (client = accept(sck, (struct sockaddr*) &si_cli, &clilen)) < 0 ) {
    //     ALOGD("Accept error!");
    // }

	} else if ((role & JNET_CLIENT)) {
		if (connect(ptr->socket, (struct sockaddr*)(&(ptr->si)),sizeof(ptr->si)) < 0) 
			JNET_ERR(ptr);
	}

    
 //    if( listen(sck, 1024) < 0) {
 //        ALOGD("Listen error!");
 //    }

	return 0;
}