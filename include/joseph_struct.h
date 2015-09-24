#include <arpa/inet.h>

struct jcpu {
	int online;
	int id;
	int32_t temp;
	int32_t util;
	int32_t freq;
} jcpu;
/*
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
} Jsocket;*/
